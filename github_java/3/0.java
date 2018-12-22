package objects;
import java.util.Stack;
/**
 * File Name: TowerOfHanoi.java
 * TowerOfHanoi.java
 * 
 * @author Chandra Rathina
 * @year 2014
 */

public class TowerOfHanoi {

   // Disk object to hold the attributes
  private  class disk{
        int n;
        int s;
        int a;
        int d;
        int where;
      disk(int n, int s, int a, int d, int where){
          this.n = n; this.s = s; this.a = a; this.d = d;
          this.where = where;
      }
    }
  private int w = 0 ;
  public void resetKount() {w = 0; }
  public void incKount() {++w ; }
  
  public void P() {
    System.out.println("Num move = " + w);
  }

  TowerOfHanoi(int n, boolean recursive) {
    resetKount();
    if (recursive) {
      th_r(n,1,2,3);
    }else {
      th(n,1,2,3);
    }
  }
  
  private void th_r(int n, int src, int aux, int dst) {
    //CANNOT CHANGE BELOW
    if (n > 0) { //at least one disk
      th_r(n-1,src,dst,aux) ; //Move n-1 from 'src' to 'aux'(using dst)
      incKount();
      System.out.println(src + "->"+ dst);
      th_r(n-1,aux,src,dst) ; //move n-1 from 'aux' to 'dst'(using src)
    }
  }

    private void move(int src, int dst) {
        System.out.print("Move top disk from " + src);
        System.out.println(" to " + dst);
    }

    private void th(int n, int src, int aux, int dst) {
    //WRITE CODE BELOW
    //CANNOT USE DIRECT OR INDIRECT RECURSION

      Stack<disk> stack = new Stack<disk>();
        disk diskobj, d1;

        diskobj = new disk(n, src,aux, dst,1);
        stack.push(diskobj);

      while(!stack.isEmpty()) {
          diskobj = stack.pop();
          if (diskobj.n > 0) {
              if (diskobj.where == 1) { // where stores return address, when disk is popped with 1,
                  diskobj.where = 2;  //it should be pushed again with 2, when 2 it should be moved
                  stack.push(diskobj);
                  d1 = new disk(diskobj.n-1,diskobj.s,diskobj.d,diskobj.a,1);
                  stack.push(d1);

              } else if (diskobj.where == 2) {
                    move(diskobj.s, diskobj.d);
                    incKount();
                    d1 = new disk(diskobj.n-1, diskobj.a, diskobj.s, diskobj.d,1);
                    stack.push(d1);
              }
          }
      }

  }
  
  private static void testBench() {
    //CANNOT CHANGE BELOW
    for (int i = 1; i < 8; ++i) {
      System.out.println("-------- " + i + "---------------" );
      {
        TowerOfHanoi t = new TowerOfHanoi(i,true);
        t.P();
      }
      {
        TowerOfHanoi t = new TowerOfHanoi(i,false);
        t.P();
      } 
    }
  }
  
  public static void main(String[] args) {
    System.out.println("TowerOfHanoi.java");
    testBench();
    System.out.println("TowerOfHanoi.java DONE");
  }
}