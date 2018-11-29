/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package newpackage;

/**
 *
 * @author Alina
 */
public class bTree
{
    //variables
    private bTreeNode root;
    private bTreeNode temp;
    
    //set root to null
    public bTree()
    {
        root=null;
    }
    
    //empty tree
    public boolean isEmpty()
    { 
        return (root == null); 
    } 
    
    //add string to tree with RecAddNode
    public void Add(String NodeData)
    {
        if (NodeData.compareTo("") != 0)
        {
            temp = new bTreeNode();
            temp.setData(NodeData);
            
            if(root == null)
            {
                root = temp;
            }

             else
            {
               RecAddNode(root);
            }
        }
    }
    
    //recursively add to tree
    private void RecAddNode(bTreeNode CurrentNode)
    {
        //sort nodes as they are added
        int order = CurrentNode.getData().compareTo(temp.data);
        if(order<0)
        {
            if(CurrentNode.leftnode == null)
            {
                CurrentNode.leftnode = temp;
            }
            else
            {
                RecAddNode(CurrentNode.leftnode);
            }
       }
        else if(order>0)
        {
            if(CurrentNode.rightnode == null)
            {
                CurrentNode.rightnode = temp;
                
            }   
            else
            {
                RecAddNode(CurrentNode.rightnode);
                    
            }
        }
        //increase count for duplicates
        else
        {
            CurrentNode.counter ++;
        }
    }
    
    //print for recPrint
    public String Print()
    {
        return recPrint(root);
    }

    //print string with count
    private String recPrint(bTreeNode Current)
    {
        String tempString = "";    
            if(Current.rightnode!=null)
                tempString = recPrint(Current.rightnode);

            tempString += " " + Current.getData() + " : " + Current.counter + "  ; ";

            if(Current.leftnode!=null)
                tempString += " " + recPrint(Current.leftnode);
            
        
                   return tempString;
    }
    
}
