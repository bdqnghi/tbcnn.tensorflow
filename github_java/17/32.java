
/**
 * Main function. 
 * This function is only test function to test an algorithm of
 * pseudo online finding K smallest elements.
 * Simulates receiving an online data and finding K smallest elements in that data.
 * K smallest element retrieved in sorted order(growing up sequence) by In-Order traversal over Red-Black-Tree.
 * Arrays of input are created by standart random function.
 * This function uses class of RedBlackTree.
 * 
 * In order to find K smallest elements first of all need to create empty Red Black Tree and to run function kSmallest.
 * Function kSmallest retrieve as parameters, empty Red-Black Tree, the array of inputs and the number of K elements to found.
 * This function creates a data structure of K smallest elements and print K smallest elements 3 times accordingly to test points 
 * which are 1\4, 1\2 ,3\4 and 1\1 of size of input array, followed with input array as reference.
 * And only after it you can use printKMin function in order to print only K smallest elements. 
 * 
 * @param args the command-line arguments
 * @author Michael Bochkovsky 
 * @version 1.2 (30/7/2017)
 */
public class Main
{
    public static void main(String[] args) { 
        //test arrays declaration
        int [] A= new int [200];
        int [] B= new int [400];
        int [] C= new int [800];
      
        //initiating array A with random numbers between 1 to 1024
        randomGenerator(A,1,1024);
        //initiating array B with random numbers between 1 to 1024
        randomGenerator(B,1,1024);
        //initiating array C with random numbers between 1 to 1024
        randomGenerator(C,1,1024);
        
      /**
       *Testing A array of size 200
       *K's values are 10/50/100 
       */
        
        RedBlackTree RbTree1 = new RedBlackTree();                              //initiate empty RB-Tree
        RbTree1.kSmallest(RbTree1,10,A);                                        //K's value is 10
              
        RedBlackTree RbTree2 = new RedBlackTree();                              //initiate empty RB-Tree
        RbTree2.kSmallest(RbTree2,50,A);                                        //K's value is 50
        
        RedBlackTree RbTree3 = new RedBlackTree();                              //initiate empty RB-Tree
        RbTree3.kSmallest(RbTree3,100,A);                                       //K's value is 100
        
        
      /**
       *Testing B array of size 400
       *K's values are 10/50/100 
       */
        RedBlackTree RbTree4 = new RedBlackTree();                              //initiate empty RB-Tree
        RbTree4.kSmallest(RbTree4,10,B);                                        //K's value is 10
        
        RedBlackTree RbTree5 = new RedBlackTree();                              //initiate empty RB-Tree
        RbTree5.kSmallest(RbTree5,50,B);                                        //K's value is 50 
        
        RedBlackTree RbTree6 = new RedBlackTree();                              //initiate empty RB-Tree
        RbTree6.kSmallest(RbTree6,100,B);                                       //K's value is 100
      
      
      /**
       *Testing C array of size 800
       *K's values are 10/50/100 
       */
        RedBlackTree RbTree7 = new RedBlackTree();                              //initiate empty RB-Tree
        RbTree7.kSmallest(RbTree7,10,C);                                        //K's value is 10
        
        RedBlackTree RbTree8 = new RedBlackTree();                              //initiate empty RB-Tree
        RbTree8.kSmallest(RbTree8,50,C);                                        //K's value is 50
        
        RedBlackTree RbTree9 = new RedBlackTree();                              //initiate empty RB-Tree
        RbTree9.kSmallest(RbTree9,100,C);                                       //K's value is 100
      }
      
    /**
     * Function for initiation of arrays with random numbers between given range 
     * @param Array array to be initiated
     * @param lower lower bound of random generated numbers
     * @param upper upper bound of generated numbers
     */
    public static void randomGenerator(int[]Array,int lower, int upper){
        for (int i=0;i<Array.length;i++){
           Array[i]=lower+(int)(Math.random()*upper);
        }
    }
}

