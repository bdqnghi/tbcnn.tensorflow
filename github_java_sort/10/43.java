

package org.apache.hadoop.hive.ql.optimizer.physical;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.Map;
import java.util.Stack;

import org.apache.hadoop.hive.ql.exec.ColumnInfo;
import org.apache.hadoop.hive.ql.exec.FileSinkOperator;
import org.apache.hadoop.hive.ql.exec.ForwardOperator;
import org.apache.hadoop.hive.ql.exec.GroupByOperator;
import org.apache.hadoop.hive.ql.exec.JoinOperator;
import org.apache.hadoop.hive.ql.exec.Operator;
import org.apache.hadoop.hive.ql.exec.ReduceSinkOperator;
import org.apache.hadoop.hive.ql.exec.SelectOperator;
import org.apache.hadoop.hive.ql.lib.Node;
import org.apache.hadoop.hive.ql.lib.NodeProcessor;
import org.apache.hadoop.hive.ql.lib.NodeProcessorCtx;
import org.apache.hadoop.hive.ql.lib.Utils;
import org.apache.hadoop.hive.ql.optimizer.physical.BucketingSortingCtx.BucketCol;
import org.apache.hadoop.hive.ql.optimizer.physical.BucketingSortingCtx.BucketSortCol;
import org.apache.hadoop.hive.ql.optimizer.physical.BucketingSortingCtx.SortCol;
import org.apache.hadoop.hive.ql.parse.SemanticException;
import org.apache.hadoop.hive.ql.plan.ExprNodeColumnDesc;
import org.apache.hadoop.hive.ql.plan.ExprNodeDesc;
import org.apache.hadoop.hive.ql.plan.ExprNodeDescUtils;
import org.apache.hadoop.hive.ql.plan.GroupByDesc;
import org.apache.hadoop.hive.ql.plan.JoinDesc;
import org.apache.hadoop.hive.ql.plan.OperatorDesc;
import org.apache.hadoop.hive.ql.plan.ReduceSinkDesc;
import org.apache.hadoop.hive.ql.plan.SelectDesc;


public class BucketingSortingOpProcFactory {

  public static class DefaultInferrer implements NodeProcessor {

    @Override
    public Object process(Node nd, Stack<Node> stack, NodeProcessorCtx procCtx,
        Object... nodeOutputs) throws SemanticException {

      return null;
    }

  }

  
  private static void processForward(Operator<? extends OperatorDesc> op, BucketingSortingCtx bctx,
      Operator<? extends OperatorDesc> parent) throws SemanticException {

    List<BucketCol> bucketCols = bctx.getBucketedCols(parent);
    List<SortCol> sortCols = bctx.getSortedCols(parent);
    List<ColumnInfo> colInfos = op.getSchema().getSignature();

    if (bucketCols == null && sortCols == null) {
      return;
    }

    List<BucketCol> newBucketCols;
    List<SortCol> newSortCols;

    if (bucketCols == null) {
      newBucketCols = null;
    } else {
      newBucketCols = getNewBucketCols(bucketCols, colInfos);
    }

    if (sortCols == null) {
      newSortCols = null;
    } else {
      newSortCols = getNewSortCols(sortCols, colInfos);
    }

    bctx.setBucketedCols(op, newBucketCols);
    bctx.setSortedCols(op, newSortCols);
  }

  
  @SuppressWarnings("unchecked")
  protected static Operator<? extends OperatorDesc> getParent(Stack<Node> stack) {
    return (Operator<? extends OperatorDesc>)Utils.getNthAncestor(stack, 1);
  }

  
  public static class JoinInferrer extends DefaultInferrer implements NodeProcessor {
    @Override
    public Object process(Node nd, Stack<Node> stack, NodeProcessorCtx procCtx,
        Object... nodeOutputs) throws SemanticException {

      BucketingSortingCtx bctx = (BucketingSortingCtx)procCtx;
      JoinOperator jop = (JoinOperator)nd;
      JoinDesc joinDesc = jop.getConf();

      Byte[] order = joinDesc.getTagOrder();
      Map<Byte, List<ExprNodeDesc>> expressions = joinDesc.getExprs();
      List<String> outputValNames = joinDesc.getOutputColumnNames();

      BucketCol[] newBucketCols = null;
      SortCol[] newSortCols = null;

      for (int i = 0; i < jop.getParentOperators().size(); i++) {

        Operator<? extends OperatorDesc> parent = jop.getParentOperators().get(i);

        
        assert(parent instanceof ReduceSinkOperator);

        ReduceSinkOperator rop = (ReduceSinkOperator)jop.getParentOperators().get(i);
        ReduceSinkDesc rsDesc = rop.getConf();

        byte tag = (byte) rsDesc.getTag();
        List<ExprNodeDesc> joinValues = expressions.get(tag);

        
        
        int offset = 0;
        for (byte orderIndex = 0; orderIndex < order.length; orderIndex++) {
          if (order[orderIndex] < order[tag]) {
            offset += expressions.get(orderIndex).size();
          }
        }

        String sortOrder = rsDesc.getOrder();
        List<ExprNodeDesc> keyCols = rsDesc.getKeyCols();
        List<ExprNodeDesc> valCols = ExprNodeDescUtils.backtrack(joinValues, jop, parent);

        if (newBucketCols == null) {
          newBucketCols = new BucketCol[keyCols.size()];
          newSortCols = new SortCol[keyCols.size()];
        }

        
        for (int keyIndex = 0 ; keyIndex < keyCols.size(); keyIndex++) {
          ExprNodeDesc key = keyCols.get(keyIndex);
          int index = ExprNodeDescUtils.indexOf(key, valCols);
          if (index >= 0) {
            int vindex = offset + index;
            String vname = outputValNames.get(vindex);
            if (newBucketCols[keyIndex] != null) {
              newBucketCols[keyIndex].addAlias(vname, vindex);
              newSortCols[keyIndex].addAlias(vname, vindex);
            } else {
              newBucketCols[keyIndex] = new BucketCol(vname, vindex);
              newSortCols[keyIndex] = new SortCol(vname, vindex, sortOrder.charAt(keyIndex));
            }
          }
        }
      }

      List<BucketCol> bucketCols = Arrays.asList(newBucketCols);
      if (!bucketCols.contains(null)) {
        bctx.setBucketedCols(jop, bucketCols);
      }
      List<SortCol> sortCols = Arrays.asList(newSortCols);
      if (!sortCols.contains(null)) {
        bctx.setSortedCols(jop, sortCols);
      }

      return null;
    }

  }

  
  private static void setBucketingColsIfComplete(BucketingSortingCtx bctx,
      Operator<? extends OperatorDesc> op, BucketCol[] newBucketCols) {

    if (newBucketCols != null) {
      List<BucketCol> newBucketColList = Arrays.asList(newBucketCols);
      
      
      
      if (!newBucketColList.contains(null)) {
        bctx.setBucketedCols(op, newBucketColList);
      }
    }
  }

  
  private static void setSortingColsIfComplete(BucketingSortingCtx bctx,
      Operator<? extends OperatorDesc> op, SortCol[] newSortCols) {

    if (newSortCols != null) {
      List<SortCol> newSortColList = Arrays.asList(newSortCols);
      
      
      
      if (!newSortColList.contains(null)) {
        bctx.setSortedCols(op, newSortColList);
      }
    }
  }

  private static void findBucketingSortingColumns(List<ExprNodeDesc> exprs,
      List<ColumnInfo> colInfos, List<BucketCol> bucketCols, List<SortCol> sortCols,
      BucketCol[] newBucketCols, SortCol[] newSortCols) {
    findBucketingSortingColumns(exprs, colInfos, bucketCols, sortCols, newBucketCols,
        newSortCols, 0);
  }

  
  private static void findBucketingSortingColumns(List<ExprNodeDesc> exprs,
      List<ColumnInfo> colInfos, List<BucketCol> bucketCols, List<SortCol> sortCols,
      BucketCol[] newBucketCols, SortCol[] newSortCols, int colInfosOffset) {
    for(int cnt = 0; cnt < exprs.size(); cnt++) {
      ExprNodeDesc expr = exprs.get(cnt);

      
      
      if (!(expr instanceof ExprNodeColumnDesc)) {
        continue;
      }

      ExprNodeColumnDesc columnExpr = (ExprNodeColumnDesc)expr;

      int colInfosIndex = cnt + colInfosOffset;

      if (newBucketCols != null) {
        int bucketIndex = indexOfColName(bucketCols, columnExpr.getColumn());
        if (bucketIndex != -1) {
          if (newBucketCols[bucketIndex] == null) {
            newBucketCols[bucketIndex] = new BucketCol();
          }
          newBucketCols[bucketIndex].addAlias(
              colInfos.get(colInfosIndex).getInternalName(), colInfosIndex);
        }
      }

      if (newSortCols != null) {
        int sortIndex = indexOfColName(sortCols, columnExpr.getColumn());
        if (sortIndex != -1) {
          if (newSortCols[sortIndex] == null) {
            newSortCols[sortIndex] = new SortCol(sortCols.get(sortIndex).getSortOrder());
          }
          newSortCols[sortIndex].addAlias(
              colInfos.get(colInfosIndex).getInternalName(), colInfosIndex);
        }
      }
    }
  }

  
  public static class SelectInferrer extends DefaultInferrer implements NodeProcessor {
    @Override
    public Object process(Node nd, Stack<Node> stack, NodeProcessorCtx procCtx,
        Object... nodeOutputs) throws SemanticException {

      BucketingSortingCtx bctx = (BucketingSortingCtx)procCtx;
      SelectOperator sop = (SelectOperator)nd;

      if (sop.getNumParent() == 1 &&
          sop.getParentOperators().get(0) instanceof ReduceSinkOperator) {
        ReduceSinkOperator rs = (ReduceSinkOperator) sop.getParentOperators().get(0);
        extractTraits(bctx, rs, sop);
        return null;
      }
      Operator<? extends OperatorDesc> parent = getParent(stack);

      
      
      
      if (sop.getConf().isSelStarNoCompute()) {
        processForward(sop, bctx, parent);
        return null;
      }

      List<BucketCol> bucketCols = bctx.getBucketedCols(parent);
      List<SortCol> sortCols = bctx.getSortedCols(parent);
      List<ColumnInfo> colInfos = sop.getSchema().getSignature();

      if (bucketCols == null && sortCols == null) {
        return null;
      }

      BucketCol[] newBucketCols = null;
      SortCol[] newSortCols = null;
      if (bucketCols != null) {
       newBucketCols = new BucketCol[bucketCols.size()];
      }
      if (sortCols != null) {
       newSortCols = new SortCol[sortCols.size()];
      }

      findBucketingSortingColumns(sop.getConf().getColList(), colInfos, bucketCols, sortCols,
          newBucketCols, newSortCols);

      setBucketingColsIfComplete(bctx, sop, newBucketCols);

      setSortingColsIfComplete(bctx, sop, newSortCols);

      return null;
    }

  }

  
  private static int indexOfColName(List<? extends BucketSortCol> bucketSortCols, String colName) {
    for (int index = 0; index < bucketSortCols.size(); index++) {
      BucketSortCol bucketSortCol = bucketSortCols.get(index);
      if (bucketSortCol.getNames().indexOf(colName) != -1) {
        return index;
      }
    }

    return -1;
  }

  
  private static List<BucketCol> getNewBucketCols(List<BucketCol> bucketCols,
      List<ColumnInfo> colInfos) {

    List<BucketCol> newBucketCols = new ArrayList<BucketCol>(bucketCols.size());
    for (int i = 0; i < bucketCols.size(); i++) {
      BucketCol bucketCol = new BucketCol();
      for (Integer index : bucketCols.get(i).getIndexes()) {
        
        
        
        
        
        
        
        if (index < colInfos.size()) {
          bucketCol.addAlias(colInfos.get(index).getInternalName(), index);
        } else {
          return null;
        }
      }
      newBucketCols.add(bucketCol);
    }
    return newBucketCols;
  }

  
  private static List<SortCol> getNewSortCols(List<SortCol> sortCols, List<ColumnInfo> colInfos) {
    List<SortCol> newSortCols = new ArrayList<SortCol>(sortCols.size());
    for (int i = 0; i < sortCols.size(); i++) {
      SortCol sortCol = new SortCol(sortCols.get(i).getSortOrder());
      for (Integer index : sortCols.get(i).getIndexes()) {
        
        if (index < colInfos.size()) {
          sortCol.addAlias(colInfos.get(index).getInternalName(), index);
        } else {
          return null;
        }
      }
      newSortCols.add(sortCol);
    }
    return newSortCols;
  }

  
  public static class FileSinkInferrer extends DefaultInferrer implements NodeProcessor {
    @Override
    public Object process(Node nd, Stack<Node> stack, NodeProcessorCtx procCtx,
        Object... nodeOutputs) throws SemanticException {

      BucketingSortingCtx bctx = (BucketingSortingCtx)procCtx;
      FileSinkOperator fop = (FileSinkOperator)nd;

      Operator<? extends OperatorDesc> parent = getParent(stack);
      List<BucketCol> bucketCols = bctx.getBucketedCols(parent);
      List<ColumnInfo> colInfos = fop.getSchema().getSignature();

      
      if (bucketCols != null) {
        List<BucketCol> newBucketCols = getNewBucketCols(bucketCols, colInfos);
        bctx.getBucketedColsByDirectory().put(fop.getConf().getDirName().toString(), newBucketCols);
        bctx.setBucketedCols(fop, newBucketCols);
      }

      List<SortCol> sortCols = bctx.getSortedCols(parent);

      
      if (sortCols != null) {
        List<SortCol> newSortCols = getNewSortCols(sortCols, colInfos);
        bctx.getSortedColsByDirectory().put(fop.getConf().getDirName().toString(), newSortCols);
        bctx.setSortedCols(fop, newSortCols);
      }

      return null;
    }

  }

  static void extractTraits(BucketingSortingCtx bctx, ReduceSinkOperator rop, Operator<?> childop)
      throws SemanticException {

    List<ExprNodeDesc> outputValues = Collections.emptyList();
    if (childop instanceof SelectOperator) {
      SelectDesc select = ((SelectOperator)childop).getConf();
      outputValues = ExprNodeDescUtils.backtrack(select.getColList(), childop, rop);
    }
    if (outputValues.isEmpty()) {
      return;
    }

    
    
    List<BucketCol> bucketCols = extractBucketCols(rop, outputValues);

    
    
    List<SortCol> sortCols = extractSortCols(rop, outputValues);

    List<ColumnInfo> colInfos = childop.getSchema().getSignature();

    if (!bucketCols.isEmpty()) {
      List<BucketCol> newBucketCols = getNewBucketCols(bucketCols, colInfos);
      bctx.setBucketedCols(childop, newBucketCols);
    }

    if (!sortCols.isEmpty()) {
      List<SortCol> newSortCols = getNewSortCols(sortCols, colInfos);
      bctx.setSortedCols(childop, newSortCols);
    }
  }

  static List<BucketCol> extractBucketCols(ReduceSinkOperator rop, List<ExprNodeDesc> outputValues) {
    List<BucketCol> bucketCols = new ArrayList<BucketCol>();
    for (ExprNodeDesc partitionCol : rop.getConf().getPartitionCols()) {
      if (!(partitionCol instanceof ExprNodeColumnDesc)) {
        return Collections.emptyList();
      }
      int index = ExprNodeDescUtils.indexOf(partitionCol, outputValues);
      if (index < 0) {
        return Collections.emptyList();
      }
      bucketCols.add(new BucketCol(((ExprNodeColumnDesc) partitionCol).getColumn(), index));
    }
    
    return bucketCols;
  }

  static List<SortCol> extractSortCols(ReduceSinkOperator rop, List<ExprNodeDesc> outputValues) {
    String sortOrder = rop.getConf().getOrder();
    List<SortCol> sortCols = new ArrayList<SortCol>();
    ArrayList<ExprNodeDesc> keyCols = rop.getConf().getKeyCols();
    for (int i = 0; i < keyCols.size(); i++) {
      ExprNodeDesc keyCol = keyCols.get(i);
      if (!(keyCol instanceof ExprNodeColumnDesc)) {
        break;
      }
      int index = ExprNodeDescUtils.indexOf(keyCol, outputValues);
      if (index < 0) {
        break;
      }
      sortCols.add(new SortCol(((ExprNodeColumnDesc) keyCol).getColumn(), index,
              sortOrder.charAt(i)));
    }
    
    
    return sortCols;
  }

  

  public static class MultiGroupByInferrer extends GroupByInferrer implements NodeProcessor {
    @Override
    public Object process(Node nd, Stack<Node> stack, NodeProcessorCtx procCtx,
        Object... nodeOutputs) throws SemanticException {
      BucketingSortingCtx bctx = (BucketingSortingCtx)procCtx;
      GroupByOperator gop = (GroupByOperator)nd;

      if (gop.getParentOperators().size() != 1) {
        return null;
      }

      Operator<? extends OperatorDesc> fop =  gop.getParentOperators().get(0);

      
      assert(fop instanceof ForwardOperator);

      if (fop.getParentOperators().size() != 1) {
        return null;
      }

      Operator<? extends OperatorDesc> rop = fop.getParentOperators().get(0);

      
      assert(rop instanceof ReduceSinkOperator);

      processGroupByReduceSink((ReduceSinkOperator) rop, gop, bctx);

      processForward(fop, bctx, rop);

      return processGroupBy(fop, gop, bctx);
    }
  }

  
  public static class GroupByInferrer extends DefaultInferrer implements NodeProcessor {
    @Override
    public Object process(Node nd, Stack<Node> stack, NodeProcessorCtx procCtx,
        Object... nodeOutputs) throws SemanticException {

      BucketingSortingCtx bctx = (BucketingSortingCtx)procCtx;
      GroupByOperator gop = (GroupByOperator)nd;

      
      
      if (gop.getParentOperators().size() != 1) {
        return null;
      }

      Operator<? extends OperatorDesc> rop = gop.getParentOperators().get(0);

      
      assert(rop instanceof ReduceSinkOperator);

      processGroupByReduceSink((ReduceSinkOperator) rop, gop, bctx);

      return processGroupBy(rop , gop, bctx);
    }

    
    protected void processGroupByReduceSink(ReduceSinkOperator rop, GroupByOperator gop,
        BucketingSortingCtx bctx){

      GroupByDesc groupByDesc = gop.getConf();
      String sortOrder = rop.getConf().getOrder();
      List<BucketCol> bucketCols = new ArrayList<BucketCol>();
      List<SortCol> sortCols = new ArrayList<SortCol>();
      assert rop.getConf().getKeyCols().size() <= rop.getSchema().getSignature().size();
      
      for (int i = 0; i < rop.getConf().getKeyCols().size(); i++) {
        if (groupByDesc.pruneGroupingSetId() && groupByDesc.getGroupingSetPosition() == i) {
          continue;
        }
        String colName = rop.getSchema().getSignature().get(i).getInternalName();
        bucketCols.add(new BucketCol(colName, i));
        sortCols.add(new SortCol(colName, i, sortOrder.charAt(i)));
      }
      bctx.setBucketedCols(rop, bucketCols);
      bctx.setSortedCols(rop, sortCols);
    }

    
    protected Object processGroupBy(Operator<? extends OperatorDesc> parent, GroupByOperator gop,
        BucketingSortingCtx bctx) {
      List<BucketCol> bucketCols = bctx.getBucketedCols(parent);
      List<SortCol> sortCols = bctx.getSortedCols(parent);
      List<ColumnInfo> colInfos = gop.getSchema().getSignature();

      if (bucketCols == null) {
        assert sortCols == null;
        return null;
      }

      if (bucketCols.isEmpty()) {
        assert sortCols.isEmpty();
        return null;
      }

      BucketCol[] newBucketCols = new BucketCol[bucketCols.size()];
      SortCol[] newSortCols = new SortCol[sortCols.size()];

      findBucketingSortingColumns(gop.getConf().getKeys(), colInfos, bucketCols, sortCols,
          newBucketCols, newSortCols);

      setBucketingColsIfComplete(bctx, gop, newBucketCols);

      setSortingColsIfComplete(bctx, gop, newSortCols);

      return null;
    }
  }

  
  public static class ForwardingInferrer extends DefaultInferrer implements NodeProcessor {
    @SuppressWarnings("unchecked")
    @Override
    public Object process(Node nd, Stack<Node> stack, NodeProcessorCtx procCtx,
        Object... nodeOutputs) throws SemanticException {

      processForward((Operator<? extends OperatorDesc>)nd, (BucketingSortingCtx)procCtx,
          getParent(stack));

      return null;
    }
  }

  public static NodeProcessor getDefaultProc() {
    return new DefaultInferrer();
  }

  public static NodeProcessor getJoinProc() {
    return new JoinInferrer();
  }

  public static NodeProcessor getSelProc() {
    return new SelectInferrer();
  }

  public static NodeProcessor getGroupByProc() {
    return new GroupByInferrer();
  }

  public static NodeProcessor getFileSinkProc() {
    return new FileSinkInferrer();
  }

  public static NodeProcessor getFilterProc() {
    return new ForwardingInferrer();
  }

  public static NodeProcessor getLimitProc() {
    return new ForwardingInferrer();
  }

  public static NodeProcessor getLateralViewForwardProc() {
    return new ForwardingInferrer();
  }

  public static NodeProcessor getLateralViewJoinProc() {
    return new ForwardingInferrer();
  }

  public static NodeProcessor getForwardProc() {
    return new ForwardingInferrer();
  }

  public static NodeProcessor getMultiGroupByProc() {
    return new MultiGroupByInferrer();
  }
}
