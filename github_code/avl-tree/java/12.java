
package avltree;

public class AvlTree {
    
    public long data;
    public AvlTree left;
    public AvlTree right;
    int height = 0;
    
    int height(AvlTree p){
        if ( p == null){
            return -1;
        }
        else{
            return p.height;
        }
    }
    
    public AvlTree insert(AvlTree p, int x){
        if ( p == null ){
            p = new AvlTree();
            p.data = x;
        }
        else{
            if(x < p.data ){
                p.left = insert(p.left, x);
                if( height(p.left) - height(p.right) == 2)
                    if( x < p.left.data)
                        p = singlerotateright(p);
                else
                        p = doublerotateright(p);
            }
            else if ( x > p.data){
                p.right = insert(p.right, x);
                if( height(p.left) - height(p.right) == -2)
                    if (x > p.right.data)
                        p = singlerotateleft(p);
                else
                        p = doublerotateleft(p);
            }
            p.height = max(height(p.left), height(p.right)) +1; 
        }
        return p;
    }
         int max ( int a, int b){
        if( a > b){
            return a;
        }
        else {
            return b;
        }
    }
         
      AvlTree singlerotateleft(AvlTree p){
        AvlTree lc = p.left;
        lc.right = p;
        p.height = max(height(p.left), height(p.right)) +1;
        lc.height = max(height(lc.left), lc.height) +1;
        return lc;
    }
      
      AvlTree doublerotateright(AvlTree p){
        p.left = singlerotateleft(p.left);
        return singlerotateright(p);
    }
      
      AvlTree singlerotateright(AvlTree p){
        AvlTree rc = p.right;
        p.right = rc.left;
        rc.left = p;
        p.height = max(height(p.left), height(p.right))+1;
        rc.height = max (height(rc.right), rc.height) +1;
        return rc;
    }
      
      AvlTree doublerotateleft(AvlTree p){
        p.right = singlerotateright(p.right);
        return singlerotateleft(p);
    }
   

    public static void main(String[] args) {
        // TODO code application logic here
    }
    
}
