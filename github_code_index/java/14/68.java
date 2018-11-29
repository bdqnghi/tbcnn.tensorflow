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
public class bTreeNode
{

    //create left & right nodes to sort
    public String data;
    int counter;
    bTreeNode leftnode;
    bTreeNode rightnode;

    //get
    public String getData() {
        return data;
    }
    
    public void setData(String data) {
        this.data = data;
        counter = 1;
    }
}
