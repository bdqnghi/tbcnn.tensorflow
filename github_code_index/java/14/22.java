import ncst.pgdst.*;
class Node
{
  int no; Node left,right;
  Node(int no) {this.no = no; left = null;right = null;}
}
public class Btree
{
  Node root;
  Btree(SimpleInput sin) throws IOException
  {
    int val = 0;
    while(val != -1) {val = sin.readInt(); if(val != -1) insert(val,root);}
  }
  void insert(int val,Node tmp)
  {
   if(root == null) { root = new Node(val);}
   else
      {
        if(val < tmp.no)
        { if(tmp.left != null) insert(val,tmp.left);
          else { tmp.left = new Node(val); System.out.println("left of" + tmp.no);}
        }
        if(val > tmp.no)
        { if(tmp.right != null) insert(val,tmp.right);
          else { tmp.right = new Node(val); System.out.println("right of" + tmp.no);}
        }
      }
  }
  static boolean check(Node tmp1,Node tmp2)
  {
    boolean flag = true;
    if((tmp1 != null && tmp2 == null)||(tmp1 == null && tmp2 != null)) flag = false;
    else
      {
     if(tmp1 != null && tmp2 != null)
      {
        if(tmp1.left != null || tmp2.right != null)  flag = check(tmp1.left,tmp2.right);
        if(flag)
        if(tmp1.right != null || tmp2.left != null) flag = check(tmp1.right, tmp2.left);
      }
      if(tmp1 == null && tmp2 == null) flag = true;
      }
    return flag;
  }
  public static void main(String [] args) throws IOException
  {
    SimpleInput sin = new SimpleInput();
    Btree B = new Btree(sin);
    if(check(B.root.left,B.root.right))  System.out.println("YES");
    else System.out.println("NO");
  }
}
