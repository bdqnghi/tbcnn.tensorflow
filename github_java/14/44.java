import java.util.ArrayList;
import java.util.Collections;

public class BTree{
    private ArrayList<String> keys;
    private BTree [] links;
    private int order = 8;
    BTree root;
    private int minimum = (order/2) - 1; //minimum number of keys in node

    public BTree(){
        keys = new ArrayList<String>(order - 1);
        links = new BTree[order];
    }
	
    public boolean Contains(String w){
        if(keys.contains(w)){
            return true;
        } else{
            return false;
        }

    }
	
	public String get( int i ) {
		return keys.get(i);
	}
	
	public boolean find(String s){
	boolean foundit = false;
	if(root.isLeaf()){
	   for(int i =0; i < root.keys.size(); i++){
             if(root.keys.get(i) == s){
				foundit = true;
				System.out.println("Found " + s);
                 break;
             } 
			 
         }
       } else{
           int i = 0;
           if(root.links[i] != null){
              root.links[i].find(s);
           } else{
               i++;
               root.links[i].find(s);
           }
       }
	   
	   if(foundit == false){
		System.out.println("Sorry word does not exist");
	   }
	   return foundit;
	}
	
	public int size(){
	 return keys.size();
	}
	
    private boolean isLeaf(){
        for(int i = 0; i < links.length; i++){
            if(links[i] == null){
                return true;
            }
            }
        return false;
        }


    private boolean isFull(){
        if(keys.size() == order - 1){
            return true;
        } else{
            return false;
        }
    }

    public int height(){
        return height(root);
    }

    private int height(BTree x){
        if(x == null){
            return 0;
        } else{
            int hleft;
            int hright;
            for(int i =0; i < links.length - 1; i++){
                 hleft = height(links[i]);
                 hright = height(links[i+1]);

            
            if(hleft > hright){
                    return hleft + 1;
                } else{
                    return hright + 1;
                }
            }
           
        }
        return height(x);
    }

    private boolean isRoot(){
        if (height() == 1){
            return true;
        } else{
            return false;
        }
    }

    //sorts values stored in arraylist
    private void sort(){
        Collections.sort(keys);

    }

    //return middle index of a node
    private int getMiddleIndex(){
        return keys.size()/ 2;
    }

    // returns index of child of node n that contains string k
    private int getchildindex(BTree n, String k){
        int i = 0;
        while(i < n.links.length){
            if(n.links[i].keys.contains(k)){
                break;
            } else{
                i++;
            }
        }
        return i;
            
        
        
    }

    //copy half of links from n into r
    private void copylinks(BTree n, BTree r){
        for(int i = n.getMiddleIndex() + 1; i <n.links.length; i++){
            int j = 0;
            r.links[j] = n.links[i];
            j++;
        }
    }

    //clear half of links in n
    private void clearlinks(BTree n){
        for(int i = n.getMiddleIndex(); i < n.links.length; i++){
            n.links[i] = null;
        }
    }

    //copy half of keys from n to r
    private void copyhalf(BTree n, BTree r){
        for(int i = (n.keys.size()/2) + 1; i < n.keys.size(); i++){
            r.keys.add(n.keys.get(i));
        }

    }

    //clear half of keys in n
    private void clearhalf(BTree n){
        for(int i = (n.keys.size()/2); i < n.keys.size() ; i++){
            n.keys.remove(i);
       }
    }

    //shift links to the right by 1
    private void shiftlinks(){
        System.arraycopy(root.links, 0, root.links, 1, root.links.length - 1);
    }

    //find child of node
    private BTree findchild(BTree n, String w){
        int i = 0;
        while(i < n.links.length){
            if(n.links[i].keys.get(0).compareTo(w) < 0 && n.links[i].keys.get(n.keys.size()).compareTo(w) > 0){
                break;
            } else{
                i++;
            }
        }
        return n.links[i];
    }


    /**
     *
     * @param n is new parent node
     * @param p is node that will be split
     * new node s will be created
     * half of keys in p will be stored in s along with links
     * p becomes left child of n and s becomes right child of n
     */
     private void SplitNode(BTree n, BTree p){
          BTree s = new BTree();
          if(p.isLeaf()){
              s.isLeaf();
          }
          int c = p.getMiddleIndex();
          String m = p.keys.get(c);
          n.keys.add(m);
          n.sort();
          copyhalf(p, s);
          clearhalf(p);
          if(!s.isLeaf()){
          copylinks(p,s);
          clearlinks(p);
         }
          int h = n.keys.indexOf(m);
          if(n.links[h] == null){
              n.links[h] = p;
          } else{
              n.links[h] = n.links[h - 1];
          }
          if(n.links[h + 1] == null){
             n.links[h+1] = s;
            } else{
              n.shiftlinks();
              n.links[h + 1] = s;
        }
          
    }

    /**
     *
     * @param w is the string that will be added to node n
     * @param n is the node that the string w will be added to
     * @return node n
     */
    private BTree add(String w, BTree n){
//        if(n == null){
//            n = new BTree();
//            n.keys.add(w);
//        }
//        else{
//            if(n.isLeaf()){
//                if(!n.isFull()){
//                    n.keys.add(w);
//                    n.sort();
//
//                } else{
//                    SplitNode(n,p);
//                    int i = 0;
//                if(p.keys.get(i).compareTo(w) > 0){
//                    add(w, p.links[i], n);
//                    p.links[i].sort();
//                } else{
//                    add(w, p.links[i+1], n);
//                    p.links[i+1].sort();
//                }
//                }
//            } else{
//                if(!n.isFull()){
//                    n.keys.add(w);
//                    n.sort();
//
//                } else{
//                    SplitNode(n,p);
//                    int i = 0;
//                if(p.keys.get(i).compareTo(w) > 0){
//                    add(w, p.links[i], n);
//                    p.links[i].sort();
//                } else{
//                    add(w, p.links[i], n);
//                    p.links[i+1].sort();
//                }
//                }
//            }
//        }
//        return n;
    if(n == null){
        n = new BTree();
        n.keys.add(w);
    } else if(n.isRoot()){
        if(n.isFull()){
        BTree s = new BTree();
        SplitNode(s,n);
        insert(s, w);
        }
    } else {
            insert(n, w);
    }

    return n;

    }
   
    //insert key into nonfull node
    private BTree insert(BTree n , String k){
        if(n.isLeaf()){
            n.keys.add(k);
            n.sort();
         } else{
            BTree child = findchild(n, k);
            if(child.isFull()){
                SplitNode(n, child);
                int i = getchildindex(n, k);
                insert(child, k);
            }
        }
        return n;
    }



    // public method that adds string w to tree
    public void add(String w){
        root = add(w, root);
    }

    //find predecessor to node n
   private BTree FindPredecessor(BTree n, String w){
       BTree currentnode = n.links[n.keys.indexOf(w)];
       while(!currentnode.isLeaf()){
           currentnode = currentnode.links[currentnode.keys.size() + 1];
       }
       return currentnode;
   }

   //Find successor to node n
   private BTree FindSuccessor(BTree n, String w){
       BTree currentnode = n.links[n.keys.indexOf(w) + 1];
       while(!currentnode.isLeaf()){
           currentnode = currentnode.links[0];
       }
       return currentnode;
   }

   //Combine keys in node n and node h
   private BTree Merge(BTree n, BTree h){
       int i = 0;
       while (i < h.keys.size()){
           n.keys.add(h.keys.get(i));
           i++;
       }
       return n;
   }

   //Public method that removes string w from tree
   public void remove(String w){
       remove(w, root);
   }

   //String w is removed from node n
   //Tree is then re-organized
    private BTree remove(String w, BTree n){
        if(n.isLeaf()){
           if(n.keys.contains(w)){
               n.keys.remove(w);
           } else{
               return null;
           }
        } else{
            if(n.keys.contains(w)){
                BTree y = n.links[n.keys.indexOf(w)];
                if(y.keys.size() >= minimum){
                    BTree m = FindPredecessor(n, w);
                    String s = m.keys.get(m.keys.size());
                    remove(s, m);
                    n.keys.set(n.keys.indexOf(w), s);
                    } else{
                    BTree z = n.links[n.keys.indexOf(w) + 1];
                    if(z.keys.size() >= minimum){
                         BTree x = FindSuccessor(n, w);
                         String t = x.keys.get(0);
                         remove(t, x);
                         n.keys.set(n.keys.indexOf(w), t);
                    } else{
                        Merge(y, z);
                        remove(w, y);
                    }
                    }
            } else{
                BTree c = null;
                BTree cleft = null;
                BTree cright = null;
                int i = 0;
                while(!n.links[i].keys.contains(w)){
                    if(n.links[i].keys.contains(w)){
                        c = n.links[i];
                        cleft = n.links[i-1];
                        cright = n.links[i + 1];
                        break;
                    } else{
                        i++;
                    }
                }

                if(c.keys.size() == minimum){
                    if(cleft != null && cleft.keys.size() > minimum){
                        c.keys.add(n.keys.get(0));
                        c.sort();
                        n.keys.add(cleft.keys.get(cleft.keys.size()));
                        n.sort();
                        c.links[0] = cleft.links[cleft.keys.size() + 1];
                        remove(cleft.keys.get(cleft.keys.size()), cleft);

                    } else if(cright != null && cright.keys.size() > minimum){
                        c.keys.add(n.keys.get(0));
                        c.sort();
                        n.keys.add(cright.keys.get(0));
                        n.sort();
                        c.links[c.keys.size() + 1] = cright.links[0];
                        remove(cright.keys.get(0), cright);
                    }
                }
                remove(w, c);
            }
        } return n;
    }

    //print values in tree using inorder traversal
    public void print(){
       if(root.isLeaf()){
	   
         for(int i =0; i < root.keys.size(); i++){
             if(root.keys.get(i) != null){
                 System.out.print(root.keys.get(i) + ", " );
             }
         }
       } else{
           int i = 0;
           if(root.links[i] != null){
              root.links[i].print();
           } else{
               i++;
               root.links[i].print();
           }
       }
 }

  
   
}


