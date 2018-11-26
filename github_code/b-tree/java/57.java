package blender.makesdna.sdna;

import java.nio.ByteBuffer;
import java.io.DataOutput;
import java.io.IOException;
import java.util.Arrays;

public class bNodeTree extends ID implements DNA, Cloneable { // #310
  public bNodeTree[] myarray;
  public ID id = (ID)this;
  public AnimData adt; // ptr 96
  public bGPdata gpd; // ptr 104
  public ListBase nodes = new ListBase(); // 16
  public ListBase links = new ListBase(); // 16
  public bNodeStack stack; // ptr 40
  public ListBase threadstack; // ptr 16
  public int type; // 4
  public int init; // 4
  public int stacksize; // 4
  public int cur_index; // 4
  public int flag; // 4
  public int pad; // 4
  public ListBase alltypes = new ListBase(); // 16
  public ListBase inputs = new ListBase(); // 16
  public ListBase outputs = new ListBase(); // 16
  public int[] pad2 = new int[2]; // 4
  public Object progress; // func ptr 0
  public Object stats_draw; // func ptr 0
  public Object test_break; // func ptr 4
  public Object tbh; // ptr 0
  public Object prh; // ptr 0
  public Object sdh; // ptr 0

  public void read(ByteBuffer buffer) {
    super.read(buffer);
    adt = DNATools.link(DNATools.ptr(buffer), AnimData.class); // get ptr
    gpd = DNATools.link(DNATools.ptr(buffer), bGPdata.class); // get ptr
    nodes.read(buffer);
    links.read(buffer);
    stack = DNATools.link(DNATools.ptr(buffer), bNodeStack.class); // get ptr
    threadstack = DNATools.link(DNATools.ptr(buffer), ListBase.class); // get ptr
    type = buffer.getInt();
    init = buffer.getInt();
    stacksize = buffer.getInt();
    cur_index = buffer.getInt();
    flag = buffer.getInt();
    pad = buffer.getInt();
    alltypes.read(buffer);
    inputs.read(buffer);
    outputs.read(buffer);
    for(int i=0;i<pad2.length;i++) pad2[i]=buffer.getInt();
    progress = DNATools.ptr(buffer); // get ptr
    stats_draw = DNATools.ptr(buffer); // get ptr
    test_break = DNATools.ptr(buffer); // get ptr
    tbh = DNATools.ptr(buffer); // get ptr
    prh = DNATools.ptr(buffer); // get ptr
    sdh = DNATools.ptr(buffer); // get ptr
  }
  public void write(DataOutput buffer) throws IOException {
    super.write(buffer);
    buffer.writeInt(adt!=null?adt.hashCode():0);
    buffer.writeInt(gpd!=null?gpd.hashCode():0);
    nodes.write(buffer);
    links.write(buffer);
    buffer.writeInt(stack!=null?stack.hashCode():0);
    buffer.writeInt(threadstack!=null?threadstack.hashCode():0);
    buffer.writeInt(type);
    buffer.writeInt(init);
    buffer.writeInt(stacksize);
    buffer.writeInt(cur_index);
    buffer.writeInt(flag);
    buffer.writeInt(pad);
    alltypes.write(buffer);
    inputs.write(buffer);
    outputs.write(buffer);
    for(int i=0;i<pad2.length;i++) buffer.writeInt(pad2[i]);
    buffer.writeInt(progress!=null?progress.hashCode():0);
    buffer.writeInt(stats_draw!=null?stats_draw.hashCode():0);
    buffer.writeInt(test_break!=null?test_break.hashCode():0);
    buffer.writeInt(tbh!=null?tbh.hashCode():0);
    buffer.writeInt(prh!=null?prh.hashCode():0);
    buffer.writeInt(sdh!=null?sdh.hashCode():0);
  }
  public Object setmyarray(Object array) {
    myarray = (bNodeTree[])array;
    return this;
  }
  public Object getmyarray() {
    return myarray;
  }
  public String toString() {
    StringBuilder sb = new StringBuilder("bNodeTree:\n");
    sb.append(super.toString());
    sb.append("  adt: ").append(adt).append("\n");
    sb.append("  gpd: ").append(gpd).append("\n");
    sb.append("  nodes: ").append(nodes).append("\n");
    sb.append("  links: ").append(links).append("\n");
    sb.append("  stack: ").append(stack).append("\n");
    sb.append("  threadstack: ").append(threadstack).append("\n");
    sb.append("  type: ").append(type).append("\n");
    sb.append("  init: ").append(init).append("\n");
    sb.append("  stacksize: ").append(stacksize).append("\n");
    sb.append("  cur_index: ").append(cur_index).append("\n");
    sb.append("  flag: ").append(flag).append("\n");
    sb.append("  pad: ").append(pad).append("\n");
    sb.append("  alltypes: ").append(alltypes).append("\n");
    sb.append("  inputs: ").append(inputs).append("\n");
    sb.append("  outputs: ").append(outputs).append("\n");
    sb.append("  pad2: ").append(Arrays.toString(pad2)).append("\n");
    sb.append("  progress: ").append(progress).append("\n");
    sb.append("  stats_draw: ").append(stats_draw).append("\n");
    sb.append("  test_break: ").append(test_break).append("\n");
    sb.append("  tbh: ").append(tbh).append("\n");
    sb.append("  prh: ").append(prh).append("\n");
    sb.append("  sdh: ").append(sdh).append("\n");
    return sb.toString();
  }
  public bNodeTree copy() { try {return (bNodeTree)super.clone();} catch(CloneNotSupportedException ex) {return null;} }
}
