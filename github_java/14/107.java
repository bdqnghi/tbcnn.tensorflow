/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package TDAS;

import TDAS.B_Node;

/**
 *
 * @author Isaias Mendez
 */
public class B_Tree {

    protected String name;
    protected B_Node root;

    public B_Tree() {
    }

    public B_Node getRoot() {
        return root;
    }

    public void setRoot(B_Node root) {
        this.root = root;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    @Override
    public String toString() {
        return name;
    }

}
