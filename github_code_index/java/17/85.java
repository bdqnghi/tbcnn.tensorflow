
import java.awt.*;
import javax.swing.*;

public class RedBlackTree extends Entrada implements Icon{

	public void limpiar(){
		if(root!=null){
			root.limpiar();
		}
	}
    private Node root;
    final private Node EMPTY = new Empty();

    public RedBlackTree() {
        root = EMPTY;
    }
    public Node buscarNodo(int value){
    	if(root!=null){return root.getNode(value);}return null;
    }
    public void add(int value) {
        root = root.add(value);
        root.color = Color.BLACK;
    }

    private class Node {
    	int recorrido=0;
        public int  value;
        
        public Color  color;
        public Node   left;
        public Node   right;
        
        public void limpiar(){
        	this.recorrido=0;
        	if(left!=null){
        		left.limpiar();
        	}
        	if(right!=null){
        		right.limpiar();
        	}
        }

        protected Node() {
            assert EMPTY == null;
        }

        public Node(int v) {
         
            value = v;
            color = Color.RED;
            left  = EMPTY;
            right = EMPTY; 
        }
 
        private boolean isRed() {
            return color == Color.RED;
        }

        public int Comparar(int v){
            if(v<this.value) return -1; else if(v>this.value) return 1; else return 0;
          }
        
        public Node add(int v) {
        	
            switch (Comparar(v)) {
            case -1:
                left = left.add(v);
                break;

            case 1:
                right = right.add(v);
                break;

            case 0:
                value = v;
                return this;  
            }

            if (left.isRed() && left.left.isRed()) {

                return balance(left.left, left, this,left.left.right, left.right);       

            } else if (left.isRed() && left.right.isRed()) {

                return balance(left, left.right, this,left.right.left, left.right.right); 
                
            } else if (right.isRed() && right.left.isRed()) {

                return balance(this, right.left, right,right.left.left, right.left.right); 
                
            } else if (right.isRed() && right.right.isRed()) {

                return balance(this, right, right.right,right.left, right.right.left);    
            }

            return this;
        }
        
        public Node getNode(int v) {

            switch (Comparar(v)) {
            case -1:
            	recorrido =-1;
                return left.getNode(v);

            case 1:
            	recorrido = 1;
                return right.getNode(v);

            default:
            	recorrido = 0;
                return this;
            }
        }
        public void paint(Graphics g, int x, int y, int separation) {
            final int R = 20;
            
            if (left != null) {
                int xx = x - separation;
                int yy = y + R * 3;
                g.setColor(java.awt.Color.BLACK);
                if(recorrido==-1){
                	g.setColor(java.awt.Color.CYAN);
                	
                }
               g.drawLine(x, y, xx, yy);
                left.paint(g, xx, yy, separation / 2);
            }

            if (right != null) {
                int xx = x + separation;
                int yy = y + R * 3;
                g.setColor(java.awt.Color.BLACK);
                if(recorrido==1){
                	g.setColor(java.awt.Color.CYAN);
                
                }
                g.drawLine(x, y, xx, yy);
                right.paint(g, xx, yy, separation / 2);
            }

            if (color == Color.RED) {
                g.setColor(java.awt.Color.RED);
            } else {
                g.setColor(java.awt.Color.BLACK);
            }
            g.fillOval(x - R, y - R, 2 * R, 2 * R);
            
            g.setColor(java.awt.Color.WHITE);
            drawCenteredString(g,String.valueOf(value), x, y);
        }
    }

    private class Empty extends Node {

        public Empty() {
            color = Color.BLACK;
            assert EMPTY == null : "Error en Nodo";
        }

        public Node add(int v) {
            return new Node(v);
        }

        public Node getNode(int value) {
            return null;
        }
    }

    private Node balance(Node x, Node y, Node z, Node B, Node C) {
        
        x.right = B;
        y.left  = x;
        y.right = z;
        z.left  = C;
        x.color = Color.BLACK;
        y.color = Color.RED;
        z.color = Color.BLACK;
        return y;
    }

    public int getIconWidth() {
        return 800;
    }
    
    public int getIconHeight() {
        return 450;
    }
    
    public void paintIcon(Component c, Graphics g, int x, int y) {
        g.translate(x, y);
        
        Rectangle r = c.getBounds();
        if (root != null) {
            root.paint(g, r.width / 2, 40, r.width / 5);
        }
        
        g.translate(-x, -y);
    }

    private  void drawCenteredString(Graphics g, String s, int x, int y) {
        FontMetrics m = g.getFontMetrics();

        java.awt.geom.Rectangle2D bounds = m.getStringBounds(s, g);
        if(s.equals("0"))
        
        g.drawString("null", (int)(x - bounds.getWidth() / 2)-6, (int)(y - bounds.getMinY() - bounds.getHeight() / 2));
        
        else{
        	 g.drawString(s, (int)(x - bounds.getWidth() / 2), (int)(y - bounds.getMinY() - bounds.getHeight() / 2));
        }
    }
}