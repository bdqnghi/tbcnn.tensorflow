/*
 * Created on May 18, 2006 Copyright (C) 2001-5, Anthony Harrison anh23@pitt.edu
 * (jactr.org) This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2.1 of the License,
 * or (at your option) any later version. This library is distributed in the
 * hope that it will be useful, but WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See
 * the GNU Lesser General Public License for more details. You should have
 * received a copy of the GNU Lesser General Public License along with this
 * library; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 330, Boston, MA 02111-1307 USA
 */
package org.jactr.io.antlr3.misc;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.HashMap;
import java.util.Map;

import javolution.util.FastList;

import org.antlr.runtime.tree.CommonTree;
import org.antlr.runtime.tree.CommonTreeAdaptor;
import org.antlr.runtime.tree.Tree;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.jactr.core.slot.IConditionalSlot;
import org.jactr.core.slot.ILogicalSlot;
import org.jactr.core.utils.parameter.IParameterized;
import org.jactr.io.antlr3.builder.JACTRBuilder;

/**
 * create the tree components used to describe various elements of the model
 * Tree modelTree = support.createModelTree();
 * support.setName(modelTree,"modelName"); support.addParameter(modelTree,
 * parameterName, parameterValueString); Tree chunkType =
 * support.createChunkTypeTree(); support.setName(chunkType,"chunkTypeName");
 * modelTree
 * .getFirstChildWithType(JACTRBuilder.DECLARATIVE_MEMORY).addChild(chunkType);
 * 
 * @author developer
 */
public class ASTSupport
{
  /**
   * logger definition
   */
  static public final Log LOGGER = LogFactory.getLog(ASTSupport.class);

  CommonTreeAdaptor       _treeAdaptor;

  public ASTSupport()
  {
    _treeAdaptor = new DetailedCommonTreeAdaptor();
  }

  public void setTreeAdaptor(CommonTreeAdaptor adaptor)
  {
    _treeAdaptor = adaptor;
  }

  /**
   * construct an empty tree that describes a model ^(MODEL NAME BUFFERS LIBRARY
   * PARAMETERS)
   * 
   * @return
   */
  public CommonTree createModelTree(String modelName)
  {
    CommonTree modelTree = create(JACTRBuilder.MODEL, "model");
    _treeAdaptor.addChild(modelTree, create(JACTRBuilder.NAME, modelName));
    _treeAdaptor.addChild(modelTree,
        createTree(JACTRBuilder.MODULES, "modules"));
    _treeAdaptor.addChild(modelTree,
        createTree(JACTRBuilder.EXTENSIONS, "extensions"));
    _treeAdaptor.addChild(modelTree,
        createTree(JACTRBuilder.BUFFERS, "buffers"));
    _treeAdaptor.addChild(modelTree, createLibraryTree());
    _treeAdaptor.addChild(modelTree, createParametersTree());
    return modelTree;
  }

  public CommonTree createExtensionTree(String className)
  {
    CommonTree ext = create(JACTRBuilder.EXTENSION, "extension");
    _treeAdaptor.addChild(ext, create(JACTRBuilder.CLASS_SPEC, className));
    _treeAdaptor.addChild(ext, createParametersTree());
    return ext;
  }

  public CommonTree createModuleTree(String className)
  {
    CommonTree ext = create(JACTRBuilder.MODULE, "module");
    _treeAdaptor.addChild(ext, create(JACTRBuilder.CLASS_SPEC, className));
    _treeAdaptor.addChild(ext, createParametersTree());
    return ext;
  }

  /**
   * ^(LIBRARY DECLARATIVE_MEMORY PROCEDURAL_MEMORY)
   * 
   * @return
   */
  protected CommonTree createLibraryTree()
  {
    CommonTree libraryTree = create(JACTRBuilder.LIBRARY, "library");
    _treeAdaptor.addChild(libraryTree,
        create(JACTRBuilder.DECLARATIVE_MEMORY, "declarative-memory"));
    _treeAdaptor.addChild(libraryTree,
        create(JACTRBuilder.PROCEDURAL_MEMORY, "procedural-memory"));
    return libraryTree;
  }

  /**
   * ^(BUFFER NAME CHUNKS PARAMETERS)
   * 
   * @return
   */
  public CommonTree createBufferTree(String bufferName)
  {
    CommonTree bufferTree = create(JACTRBuilder.BUFFER, "buffer");
    _treeAdaptor.addChild(bufferTree, create(JACTRBuilder.NAME, bufferName));
    _treeAdaptor.addChild(bufferTree, create(JACTRBuilder.CHUNKS, "chunks"));
    _treeAdaptor.addChild(bufferTree, createParametersTree());
    return bufferTree;
  }

  /**
   * ^(CHUNK_TYTPE NAME PARENTS SLOTS CHUNKS PARAMETERS)
   * 
   * @return
   */
  public CommonTree createChunkTypeTree(String chunkTypeName,
      Collection<String> parentChunkTypeNames)
  {
    CommonTree chunkTypeTree = create(JACTRBuilder.CHUNK_TYPE, "chunktype");
    _treeAdaptor.addChild(chunkTypeTree,
        create(JACTRBuilder.NAME, chunkTypeName));
    CommonTree parentsTree = createParentsTree();
    _treeAdaptor.addChild(chunkTypeTree, parentsTree);
    if(parentChunkTypeNames.size() > 0) for(String parent : parentChunkTypeNames)
    	_treeAdaptor.addChild(parentsTree,
    		create(JACTRBuilder.PARENT, parent));
    
    // the parent node is optional and should not be included if the chunktype
    // has no parent
    _treeAdaptor.addChild(chunkTypeTree, createSlotsTree());
    _treeAdaptor.addChild(chunkTypeTree,
        createTree(JACTRBuilder.CHUNKS, "chunks"));
    _treeAdaptor.addChild(chunkTypeTree, createParametersTree());
    return chunkTypeTree;
  }

  /**
   * ^(CHUNK NAME PARENT SLOTS PARAMETERS)
   * 
   * @return
   */
  public CommonTree createChunkTree(String chunkName, String chunkTypeName)
  {
	 CommonTree chunkTree = create(JACTRBuilder.CHUNK, "chunk");
    _treeAdaptor.addChild(chunkTree, create(JACTRBuilder.NAME, chunkName));
    _treeAdaptor
        .addChild(chunkTree, create(JACTRBuilder.PARENT, chunkTypeName));
    _treeAdaptor.addChild(chunkTree, createSlotsTree());
    _treeAdaptor.addChild(chunkTree, createParametersTree());
    return chunkTree;
  }

  /**
   * creates a symbolic copy (i.e., no parameters) of the specified chunk. To
   * correctly add it to the model AST, the returned tree must: <br/>
   * 1) have its name changed to a unique identifier <br/>
   * 2) be added as a child of the chunktype AST's CHUNKS subtree. <br/>
   * If this is to be inserted into a buffer, it must also be added to that
   * buffer's CHUNKS subtree.
   * 
   * @param chunk
   * @return
   */
  public CommonTree copyChunkTree(CommonTree chunk)
  {
    CommonTree copy = createChunkTree(getName(chunk), getParent(chunk));

    /*
     * for the slots, we need the copy's SLOTS node, and the map of all the
     * slots of the source
     */
    CommonTree copySlots = getFirstDescendantWithType(copy, JACTRBuilder.SLOTS);
    Collection<CommonTree> slots = getAllDescendantsWithType(chunk,
        JACTRBuilder.SLOT);

    for (CommonTree slot : slots)
      copySlots.addChild(slot.dupNode());

    return copy;
  }

  /**
   * ^(PRODUCTION NAME CONDITIONS ACTIONS PARAMETERS)
   * 
   * @return
   */
  public CommonTree createProductionTree(String productionName)
  {
    CommonTree productionTree = create(JACTRBuilder.PRODUCTION, "production");
    _treeAdaptor.addChild(productionTree,
        create(JACTRBuilder.NAME, productionName));
    _treeAdaptor.addChild(productionTree,
        create(JACTRBuilder.CONDITIONS, "conditions"));
    _treeAdaptor.addChild(productionTree,
        create(JACTRBuilder.ACTIONS, "actions"));
    _treeAdaptor.addChild(productionTree, createParametersTree());
    return productionTree;
  }

  /**
   * Creates a tree describing a pattern match condition this tree must have
   * either ientifier or a variable supplied ^(MATCH_CONDITON NAME
   * (IDENTIFIER|VARIBALE) SLOTS)
   * 
   * @throws illegal
   *           arugment if content is null or not IDENTIFIER or VARIABLE
   * @return
   */
  public CommonTree createMatchTree(String bufferName, CommonTree content)
  {
    if (content != null)
      if (content.getType() != JACTRBuilder.CHUNK_IDENTIFIER
          && content.getType() != JACTRBuilder.CHUNK_TYPE_IDENTIFIER
          && content.getType() != JACTRBuilder.VARIABLE)
        throw new IllegalArgumentException(
            "content must be CHUNK_IDENTIFIER, CHUNK_TYPE_IDENTIFIER or VARIABLE");

    CommonTree match = create(JACTRBuilder.MATCH_CONDITION, "match");
    _treeAdaptor.addChild(match, create(JACTRBuilder.NAME, bufferName));
    if (content != null)
    {
      _treeAdaptor.addChild(match, content);
      _treeAdaptor.addChild(match, createSlotsTree());
    }
    return match;
  }

  /**
   * ^(QUERY NAME SLOTS)
   * 
   * @return
   */
  public CommonTree createQueryTree(String bufferName)
  {
    CommonTree match = create(JACTRBuilder.QUERY_CONDITION, "query");
    _treeAdaptor.addChild(match, create(JACTRBuilder.NAME, bufferName));
    _treeAdaptor.addChild(match, createSlotsTree());
    return match;
  }

  public CommonTree createScriptableConditionTree(String language, String script)
  {
    CommonTree scriptTree = create(JACTRBuilder.SCRIPTABLE_CONDITION,
        "scriptableCondition");
    _treeAdaptor.addChild(scriptTree, create(JACTRBuilder.LANG, language));
    _treeAdaptor.addChild(scriptTree, create(JACTRBuilder.SCRIPT, script));
    return scriptTree;
  }

  public CommonTree createProxyConditionTree(String className)
  {
    CommonTree proxyTree = create(JACTRBuilder.PROXY_CONDITION,
        "proxyCondition");
    _treeAdaptor
        .addChild(proxyTree, create(JACTRBuilder.CLASS_SPEC, className));
    _treeAdaptor.addChild(proxyTree, createSlotsTree());
    return proxyTree;
  }

  /**
   * @param bufferName
   * @param content
   *          must not be null
   * @throws illegal
   *           argument exception if content is null
   * @return
   */
  public CommonTree createAddTree(String bufferName, CommonTree content)
  {
    if (content == null)
      throw new IllegalArgumentException("content cannot be null");
    if (content.getType() != JACTRBuilder.CHUNK_IDENTIFIER
        && content.getType() != JACTRBuilder.CHUNK_TYPE_IDENTIFIER
        && content.getType() != JACTRBuilder.VARIABLE)
      throw new IllegalArgumentException(
          "content must be CHUNK_IDENTIFIER, CHUNK_TYPE_IDENTIFIER or VARIABLE");

    CommonTree addTree = create(JACTRBuilder.ADD_ACTION, "addAction");
    _treeAdaptor.addChild(addTree, create(JACTRBuilder.NAME, bufferName));
    _treeAdaptor.addChild(addTree, content);
    _treeAdaptor.addChild(addTree, createSlotsTree());
    return addTree;
  }

  public CommonTree createSetTree(String bufferName, CommonTree content)
  {
    if (content == null)
      throw new IllegalArgumentException("content cannot be null");
    if (content.getType() != JACTRBuilder.CHUNK_IDENTIFIER
        && content.getType() != JACTRBuilder.VARIABLE)
      throw new IllegalArgumentException(
          "content must be CHUNK_IDENTIFIER or VARIABLE");

    CommonTree addTree = create(JACTRBuilder.SET_ACTION, "setAction");
    _treeAdaptor.addChild(addTree, create(JACTRBuilder.NAME, bufferName));
    _treeAdaptor.addChild(addTree, content);
    _treeAdaptor.addChild(addTree, createSlotsTree());
    return addTree;
  }

  /**
   * @param bufferName
   * @param content
   *          can be null
   * @return
   */
  public CommonTree createRemoveTree(String bufferName, CommonTree content)
  {
    if (content != null && content.getType() != JACTRBuilder.IDENTIFIER
        && content.getType() != JACTRBuilder.VARIABLE)
      throw new IllegalArgumentException(
          "content must be IDENTIFIER or VARIABLE");

    CommonTree addTree = create(JACTRBuilder.REMOVE_ACTION, "removeAction");
    _treeAdaptor.addChild(addTree, create(JACTRBuilder.NAME, bufferName));
    if (content != null) _treeAdaptor.addChild(addTree, content);
    _treeAdaptor.addChild(addTree, createSlotsTree());
    return addTree;
  }

  /**
   * ^(MODIFY_ACTION NAME SLOTS)
   * 
   * @return
   */
  public CommonTree createModifyTree(String bufferName)
  {
    CommonTree match = create(JACTRBuilder.MODIFY_ACTION, "modifyAction");
    _treeAdaptor.addChild(match, create(JACTRBuilder.NAME, bufferName));
    _treeAdaptor.addChild(match, createSlotsTree());
    return match;
  }

  public CommonTree createScriptableActionTree(String language, String script)
  {
    CommonTree scriptTree = create(JACTRBuilder.SCRIPTABLE_ACTION,
        "scriptableAction");
    _treeAdaptor.addChild(scriptTree, create(JACTRBuilder.LANG, language));
    _treeAdaptor.addChild(scriptTree, create(JACTRBuilder.SCRIPT, script));
    return scriptTree;
  }

  public CommonTree createProxyActionTree(String className)
  {
    CommonTree proxyTree = create(JACTRBuilder.PROXY_ACTION, "proxyAction");
    _treeAdaptor
        .addChild(proxyTree, create(JACTRBuilder.CLASS_SPEC, className));
    _treeAdaptor.addChild(proxyTree, createSlotsTree());
    return proxyTree;
  }

  public CommonTree createOutputAction(String output)
  {
    CommonTree outputTree = create(JACTRBuilder.OUTPUT_ACTION, "outputAction");
    _treeAdaptor.addChild(outputTree, string(output));
    return outputTree;
  }

  /**
   * create a node with type and teext
   * 
   * @param type
   * @param text
   * @return
   */
  public CommonTree create(int type, String text)
  {
    return (CommonTree) _treeAdaptor.create(type, text);
  }

  public CommonTree create(int type)
  {
    return create(type, "");
  }

  public CommonTree createTree(int type, String text)
  {
    CommonTree root_1 = (CommonTree) _treeAdaptor.nil();
    root_1 = (CommonTree) _treeAdaptor.becomeRoot(create(type, text), root_1);
    return root_1;
  }

  /**
   * return an IDENTIFIER wrapping the object
   * 
   * @param obj
   * @return
   */
  public CommonTree identifier(Object obj)
  {
    if (obj == null) obj = "null";
    return (CommonTree) _treeAdaptor.create(JACTRBuilder.IDENTIFIER,
        obj.toString());
  }

  /**
   * return a STRING wrapping the object
   * 
   * @param obj
   * @return
   */
  public CommonTree string(Object obj)
  {
    if (obj == null) obj = "null";
    return create(JACTRBuilder.STRING, obj.toString());
  }

  /**
   * return a NUMBER wrapping this one ^(NUMBER)
   * 
   * @param num
   * @return
   */
  public CommonTree number(Number num)
  {
    if (num == null) num = Double.NaN;
    return create(JACTRBuilder.NUMBER, num.toString());
  }

  public CommonTree createParentsTree()
  {
    return create(JACTRBuilder.PARENTS, "parents");
  }

  public CommonTree createParametersTree()
  {
    return create(JACTRBuilder.PARAMETERS, "parameters");
  }

  public CommonTree createSlotsTree()
  {
    return create(JACTRBuilder.SLOTS, "slots");
  }

  public CommonTree createLogicalSlot(int operator) {
	  CommonTree logicalNode = create(JACTRBuilder.LOGIC, "logic");
	  switch(operator) {
	  case ILogicalSlot.AND:
		  logicalNode.addChild(create(JACTRBuilder.AND, "and"));
		  break;
	  case ILogicalSlot.OR:
		  logicalNode.addChild(create(JACTRBuilder.OR, "or"));
		  break;
	  case ILogicalSlot.NOT:
		  logicalNode.addChild(create(JACTRBuilder.NOT, "not"));
		  break;
	  }
	  return logicalNode;
  }
  
  public CommonTree createSlot(String slotName, int condition,
      CommonTree content)
  {
    CommonTree conditionNode = null;

    switch (condition)
    {
      case IConditionalSlot.GREATER_THAN:
        conditionNode = create(JACTRBuilder.GT, ">");
        break;
      case IConditionalSlot.GREATER_THAN_EQUALS:
        conditionNode = create(JACTRBuilder.GTE, ">=");
        break;
      case IConditionalSlot.LESS_THAN:
        conditionNode = create(JACTRBuilder.LT, "<");
        break;
      case IConditionalSlot.LESS_THAN_EQUALS:
        conditionNode = create(JACTRBuilder.LTE, "<=");
        break;
      case IConditionalSlot.NOT_EQUALS:
        conditionNode = create(JACTRBuilder.NOT, "!=");
        break;
    }

    if (conditionNode == null)
      conditionNode = create(JACTRBuilder.EQUALS, "=");

    return createSlot(slotName, conditionNode, content);
  }

  public CommonTree createSlot(CommonTree slotName, CommonTree content)
  {
    return createSlot(slotName, create(JACTRBuilder.EQUALS, "="), content);
  }

  public CommonTree createSlot(CommonTree slotName, CommonTree condition,
      CommonTree content)
  {
    CommonTree slot = create(JACTRBuilder.SLOT, "slot");
    slot.addChild(slotName);
    slot.addChild(condition);
    slot.addChild(content);
    return slot;
  }

  public CommonTree createSlot(String slotName, CommonTree condition,
      CommonTree content)
  {
    CommonTree slot = create(JACTRBuilder.SLOT, "slot");
    slot.addChild(create(JACTRBuilder.NAME, slotName));
    return createSlot(create(JACTRBuilder.NAME, slotName), condition, content);
  }

  public CommonTree createSlot(String slotName, CommonTree content)
  {
    return createSlot(slotName, create(JACTRBuilder.EQUALS, "="), content);
  }

  public CommonTree createSlot(String slotName)
  {
    return createSlot(slotName, create(JACTRBuilder.IDENTIFIER, "null"));
  }

  /**
   * set the name node of this tree element
   * 
   * @param tree
   * @param name
   * @throws illegalargumentexception
   *           if tree doesn't have a name node
   */
  public void setName(CommonTree tree, String name)
  {
    for (int i = 0; i < tree.getChildCount(); i++)
    {
      CommonTree child = (CommonTree) tree.getChild(i);
      if (child.getType() == JACTRBuilder.NAME)
      {
        // replace
        child = create(JACTRBuilder.NAME, name);
        tree.setChild(i, child);
        return;
      }
    }
    throw new IllegalArgumentException(tree
        + " does not have a NAME child node");
  }

  /**
   * add a parameter node to the parameters child of this tree
   * 
   * @param tree
   * @param parameterName
   * @param parameterValue
   * @throws illegalarugmentexception
   *           if tree does not have a PARAMETERS node
   */
  public CommonTree createParameter(String parameterName, String parameterValue)
  {
    CommonTree parameterNode = create(JACTRBuilder.PARAMETER);
    _treeAdaptor.addChild(parameterNode,
        create(JACTRBuilder.NAME, parameterName));
    _treeAdaptor.addChild(parameterNode, string(parameterValue));

    return parameterNode;
  }

  /**
   * create a slot and add it to the slots node
   * 
   * @param tree
   * @param slotName
   * @param condition
   * @param content
   */
  public void addSlot(CommonTree tree, String slotName, int condition,
      CommonTree content)
  {
    if (condition >= IConditionalSlot.EQUALS
        && condition <= IConditionalSlot.NOT_EQUALS)
      throw new IllegalArgumentException("Condition is invalid");
    if (content == null)
      throw new IllegalArgumentException("content must not be null");
    if (content.getType() != JACTRBuilder.IDENTIFIER
        && content.getType() != JACTRBuilder.VARIABLE
        && content.getType() != JACTRBuilder.STRING
        && content.getType() != JACTRBuilder.NUMBER)
      throw new IllegalArgumentException(
          "content must be IDENTIFIER, VARIABLE, STRING, or NUMBER");

    CommonTree cond = null;
    switch (condition)
    {
      case IConditionalSlot.GREATER_THAN:
        cond = create(JACTRBuilder.GT, ">");
        break;
      case IConditionalSlot.GREATER_THAN_EQUALS:
        cond = create(JACTRBuilder.GTE, ">=");
        break;
      case IConditionalSlot.LESS_THAN:
        cond = create(JACTRBuilder.LT, "<");
        break;
      case IConditionalSlot.LESS_THAN_EQUALS:
        cond = create(JACTRBuilder.LTE, "<=");
        break;
      case IConditionalSlot.WITHIN:
        cond = create(JACTRBuilder.WITHIN, "<>");
        break;
      case IConditionalSlot.NOT_EQUALS:
        cond = create(JACTRBuilder.NOT, "!=");
        break;
      default:
        cond = create(JACTRBuilder.EQUALS, "=");
        break;
    }

    CommonTree slot = create(JACTRBuilder.SLOT, "slot");
    _treeAdaptor.addChild(slot, create(JACTRBuilder.NAME, slotName));
    _treeAdaptor.addChild(slot, cond);
    _treeAdaptor.addChild(slot, content);

    CommonTree slots = getFirstDescendantWithType(tree, JACTRBuilder.SLOTS);
    if (slots == null)
      throw new IllegalArgumentException(tree
          + " does not have SLOTS child node");
    _treeAdaptor.addChild(slots, slot);
  }

  public void addSlot(CommonTree tree, String slotName, CommonTree content)
  {
    addSlot(tree, slotName, IConditionalSlot.EQUALS, content);
  }

  public void setParameters(IParameterized parameterized,
      CommonTree parameterizedContainer)
  {

    for (String parameterName : parameterized.getSetableParameters())
    {
      Object parameterValue = parameterized.getParameter(parameterName);
      if (parameterValue == null) parameterValue = "null";
      setParameter(parameterizedContainer, parameterName,
          parameterValue.toString(), false);
    }
  }

  /**
   * copy the parameter nodes from src to dest, overwriting those that already
   * exist
   * 
   * @param srcParametersContainer
   * @param destParametersContainer
   */
  static public void setParameters(CommonTree srcParametersContainer,
      CommonTree destParametersContainer)
  {
    Map<String, CommonTree> srcParams = getMapOfTrees(srcParametersContainer,
        JACTRBuilder.PARAMETER);
    Map<String, CommonTree> destParams = getMapOfTrees(destParametersContainer,
        JACTRBuilder.PARAMETER);

    for (Map.Entry<String, CommonTree> param : srcParams.entrySet())
      /*
       * we need to overwrite
       */
      if (destParams.containsKey(param.getKey()))
        destParams.get(param.getKey())
            .setChild(1, param.getValue().getChild(1));
      else
        destParametersContainer.addChild(param.getValue());
  }

  // /**
  // * import any AST info that the moduleClass might need to be properly
  // compiled
  // * and built. unfortunately, we need to instantiate the module from a zero
  // arg
  // * constructor. with it, we snag default parameter values as well as
  // * IASTInjector
  // */
  // public void importModuleTrees(CommonTree modelTree,
  // Class< ? extends IModule> moduleClass, boolean importContents)
  // throws RuntimeException
  // {
  // try
  // {
  //
  // CommonTree moduleNode = createModuleTree(moduleClass.getName());
  // CommonTree modules = ASTSupport.getFirstDescendantWithType(modelTree,
  // JACTRBuilderTreeParser.MODULES);
  //
  // modules.addChild(moduleNode);
  //
  // IASTParticipant participant = ASTParticipantRegistry
  // .getParticipant(moduleClass);
  //
  // if (importContents && participant != null)
  // {
  // IASTInjector injector = participant.getInjector();
  // if (injector != null) injector.inject(modelTree);
  // }
  // }
  // catch (Exception e)
  // {
  // LOGGER.error(
  // "Failed to import for module " + moduleClass.getSimpleName(), e);
  // throw new RuntimeException("Failed to import for module "
  // + moduleClass.getSimpleName(), e);
  // }
  // }

  static public String getName(CommonTree node)
  {
    return getFirstDescendantWithType(node, JACTRBuilder.NAME).getText();
  }

  static public String getParent(CommonTree node)
  {
    return getFirstDescendantWithType(node, JACTRBuilder.PARENT).getText();
  }
  
  static public Collection<String> getParents(CommonTree node)
  {
	  Collection<String> parents = new FastList<String>();
	  for(CommonTree parent : getAllDescendantsWithType(node, JACTRBuilder.PARENT))
		  parents.add(parent.getText());
    //return getFirstDescendantWithType(node, JACTRBuilder.PARENT).getText();
	  return parents;
  }

  static public CommonTree getFirstDescendantWithType(CommonTree root, int type)
  {
    CommonTree node = (CommonTree) root.getFirstChildWithType(type);
    if (node != null) return node;

    // dig deeper
    for (int i = 0; i < root.getChildCount(); i++)
    {
    	//LOGGER.error("already eliminated child with type " + root.getChild(i).getType());
      node = getFirstDescendantWithType((CommonTree) root.getChild(i), type);
      if (node != null) return node;
    }
    //LOGGER.error("Can't find descendent of type " + type);
    return null;
  }

  static public Collection<CommonTree> getAllDescendantsWithType(
      CommonTree root, int type)
  {
    if (root == null) return Collections.EMPTY_LIST;
    Collection<CommonTree> rtn = new ArrayList<CommonTree>();
    if (root.getType() == type) rtn.add(root);
    for (int i = 0; i < root.getChildCount(); i++)
      rtn.addAll(getAllDescendantsWithType((CommonTree) root.getChild(i), type));
    return rtn;
  }

  static public CommonTree getLastDescendant(CommonTree root)
  {
    if (root.getChildCount() == 0) return root;
    return getLastDescendant((CommonTree) root
        .getChild(root.getChildCount() - 1));
  }

  /**
   * scan through root recursively, looking for all nodes of type treeType that
   * also have a name subchild. Take that name, store the node under the lower
   * cased name.
   * 
   * @param root
   * @param treeType
   * @return
   */
  static public Map<String, CommonTree> getMapOfTrees(CommonTree root,
      int treeType)
  {
    return getMapOfTrees(root, treeType, new HashMap<String, CommonTree>());
  }

  static public Map<String, CommonTree> getMapOfTrees(CommonTree root,
      int treeType, Map<String, CommonTree> container)
  {
    container.clear();
    for (int i = 0; i < root.getChildCount(); i++)
    {
      CommonTree node = (CommonTree) root.getChild(i);
      if (treeType == node.getType())
      {
        CommonTree nameNode = getFirstDescendantWithType(node,
            JACTRBuilder.NAME);
        if (nameNode != null)
          container.put(nameNode.getText().toLowerCase(), node);
      }
      else
        // dig down
        container.putAll(getMapOfTrees(node, treeType));
    }
    return container;
  }

  static public Collection<CommonTree> getTrees(CommonTree root, int treeType)
  {
    Collection<CommonTree> rtn = new ArrayList<CommonTree>();
    for (int i = 0; i < root.getChildCount(); i++)
    {
      CommonTree node = (CommonTree) root.getChild(i);
      if (treeType == node.getType())
        rtn.add(node);
      else
        // dig down
        rtn.addAll(getTrees(node, treeType));
    }
    return rtn;
  }

  /**
   * @param tree
   * @param parameterName
   * @param parameterValue
   * @param overwrite
   *          should we overwrite parameters if they already exist?
   */
  public void setParameter(CommonTree tree, String parameterName,
      String parameterValue, boolean overwrite)
  {
    CommonTree parametersNode = (CommonTree) tree
        .getFirstChildWithType(JACTRBuilder.PARAMETERS);
    if (parametersNode == null)
      throw new RuntimeException(tree.toStringTree()
          + " does not have a parameters node");

    // see if we can find the parameterName
    Map<String, CommonTree> parameters = getMapOfTrees(parametersNode,
        JACTRBuilder.PARAMETER);
    CommonTree parameterNode = parameters.get(parameterName.toLowerCase());
    if (parameterNode == null)
    {
      // we need to create the node
      parameterNode = createParameter(parameterName, parameterValue);
      parametersNode.addChild(parameterNode);
      if (LOGGER.isDebugEnabled())
        LOGGER.debug("Added parameter " + parameterNode.toStringTree());
    }
    else if (overwrite)
    {
      // remove the previous value node
      parameterNode.setChild(1, string(parameterValue));
      if (LOGGER.isDebugEnabled())
        LOGGER.debug("Overwrote parameter to " + parameterNode.toStringTree());
    }
  }

  static public void addChunkType(CommonTree modelTree, CommonTree chunkTypeTree)
  {
    CommonTree declarativeNode = getFirstDescendantWithType(modelTree,
        JACTRBuilder.DECLARATIVE_MEMORY);
    declarativeNode.addChild(chunkTypeTree);

  }

  static public void addProduction(CommonTree modelTree,
      CommonTree productionTree)
  {
    CommonTree proceduralNode = getFirstDescendantWithType(modelTree,
        JACTRBuilder.PROCEDURAL_MEMORY);
    proceduralNode.addChild(productionTree);
  }

  static public String outputTree(Tree tree)
  {
    return outputTree(tree, 0);
  }

  static public String outputTree(Tree tree, int level)
  {
    StringBuilder sb = new StringBuilder();
    for (int i = 0; i < level; i++)
      sb.append(" ");
    int type = tree.getType();
    sb.append("<").append(JACTRBuilder.tokenNames[type]).append("(")
        .append(type).append(")");
    sb.append("  text=\"").append(tree.toString()).append("\"");
    if (tree.getChildCount() == 0)
      sb.append("/>");
    else
    {
      sb.append(">");
      for (int i = 0; i < tree.getChildCount(); i++)
        sb.append("\n").append(outputTree(tree.getChild(i), level + 2));
      sb.append("\n");
      for (int i = 0; i < level; i++)
        sb.append(" ");
      sb.append("</").append(JACTRBuilder.tokenNames[type]).append("(")
          .append(type).append(")").append("  text=\"").append(tree.toString())
          .append("\">");
    }

    return sb.toString();
  }

  /**
   * steal the location information
   * 
   * @param source
   * @param dest
   */
  static public void stealLocation(CommonTree source, CommonTree dest)
  {

  }
}
