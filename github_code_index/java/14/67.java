package com.neusoft.hp.runtime.util;

import java.util.ArrayList;
import java.util.List;

import org.apache.commons.lang3.StringUtils;

import com.alibaba.fastjson.JSON;
import com.neusoft.hp.runtime.dyn.bean.TreeDTO;

@Deprecated
public class TreeBuilderUtil {

    List<TreeDTO> TreeDTOs = new ArrayList<TreeDTO>();

    public TreeBuilderUtil(List<TreeDTO> TreeDTOs){
        super();
        this.TreeDTOs = TreeDTOs;
    }

    /**
     * 构建JSON树形结构
     * 
     * @return
     */
    public String buildJSONTree() {
        List<TreeDTO> nodeTree = buildTree();
        return JSON.toJSONString(nodeTree);
    }

    public List<TreeDTO> buildListTree() {
        List<TreeDTO> nodeTree = buildTree();
        return nodeTree;
    }

    /**
     * 构建树形结构
     * 
     * @return
     */
    public List<TreeDTO> buildTree() {
        List<TreeDTO> treeTreeDTOs = new ArrayList<TreeDTO>();
        List<TreeDTO> rootTreeDTOs = getRootTreeDTOs();
        for (TreeDTO rootTreeDTO : rootTreeDTOs) {
            buildChildTreeDTOs(rootTreeDTO);
            treeTreeDTOs.add(rootTreeDTO);
        }
        return treeTreeDTOs;
    }

    /**
     * 递归子节点
     * 
     * @param TreeDTO
     */
    public void buildChildTreeDTOs(TreeDTO TreeDTO) {
        List<TreeDTO> children = getChildTreeDTOs(TreeDTO);
        if (!children.isEmpty()) {
            for (TreeDTO child : children) {
                buildChildTreeDTOs(child);
            }
            TreeDTO.setChilds(children);
        }
    }

    /**
     * 获取父节点下所有的子节点
     * 
     * @param TreeDTOs
     * @param pTreeDTO
     * @return
     */
    public List<TreeDTO> getChildTreeDTOs(TreeDTO pTreeDTO) {
        List<TreeDTO> childTreeDTOs = new ArrayList<TreeDTO>();
        for (TreeDTO n : TreeDTOs) {
            if (pTreeDTO.getId().equals(n.getPid())) {
                childTreeDTOs.add(n);
            }
        }
        return childTreeDTOs;
    }

    /**
     * 判断是否为根节点
     * 
     * @param TreeDTOs
     * @param inTreeDTO
     * @return
     */
    public boolean rootTreeDTO(TreeDTO TreeDTO) {
        boolean isRootTreeDTO = true;
        if (StringUtils.isNotBlank(TreeDTO.getPid())) {
            for (TreeDTO n : TreeDTOs) {
                if (TreeDTO.getPid().equals(n.getId())) {
                    isRootTreeDTO = false;
                    break;
                }
            }
        }

        return isRootTreeDTO;
    }

    /**
     * 获取集合中所有的根节点
     * 
     * @param TreeDTOs
     * @return
     */
    public List<TreeDTO> getRootTreeDTOs() {
        List<TreeDTO> rootTreeDTOs = new ArrayList<TreeDTO>();
        for (TreeDTO n : TreeDTOs) {
            if (rootTreeDTO(n)) {
                rootTreeDTOs.add(n);
            }
        }
        return rootTreeDTOs;
    }

    public static void main(String[] args) {

        List<TreeDTO> TreeDTOs = new ArrayList<TreeDTO>();
        TreeDTO p1 = new TreeDTO("01", "", "01", "");
        TreeDTO p6 = new TreeDTO("02", "", "02", "");
        TreeDTO p7 = new TreeDTO("0201", "02", "0201", "");
        TreeDTO p2 = new TreeDTO("0101", "01", "0101", "");
        TreeDTO p3 = new TreeDTO("0102", "01", "0102", "");
        TreeDTO p4 = new TreeDTO("010101", "0101", "010101", "");
        TreeDTO p5 = new TreeDTO("010102", "0101", "010102", "");
        TreeDTO p8 = new TreeDTO("010102101", "010102", "010102101", "");

        TreeDTOs.add(p1);
        TreeDTOs.add(p2);
        TreeDTOs.add(p3);
        TreeDTOs.add(p4);
        TreeDTOs.add(p5);
        TreeDTOs.add(p6);
        TreeDTOs.add(p7);
        TreeDTOs.add(p8);
        TreeBuilderUtil treeBuilder = new TreeBuilderUtil(TreeDTOs);
        System.out.println(treeBuilder.buildJSONTree());
    }

}
