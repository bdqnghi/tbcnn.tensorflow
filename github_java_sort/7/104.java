package chap7;

public class ShellSort {
    private int[] theArray;
    private int size;
    private int index;

    public ShellSort(int _size) {
        size = _size;
        theArray = new int[size];
        index = 0;
    }
    
    public void insert(int number){
        theArray[index++] = number;
    }
    
    public void shellSort(){
        int inner, outer;
        int temp;
        
        int h=1;
        while(h <= size/3)
            h = h*3 + 1;    
        
        
        
        while(h>0){
            for(outer = h; outer < size; outer++){
                temp = theArray[outer]; 
                
                inner = outer;
                while(inner >= h && theArray[inner-h] >= temp){
                    theArray[inner] = theArray[inner-h];
                    inner -= h;
                }
                theArray[inner] = temp;
            }
            h = (h-1)/3;
        }
    }
    
    public void display(){
        for (int i : theArray) {
            System.out.print(i + " ");
        }
    }
    
    public static void main(String[] args) {
        ShellSort shellSort = new ShellSort(9);
        shellSort.insert(45);
        
        shellSort.insert(9);
        shellSort.insert(5);
        shellSort.insert(4);
        shellSort.insert(8);
        shellSort.insert(7);

        
        shellSort.insert(3);
        shellSort.insert(2);
        shellSort.insert(10);
        
        shellSort.shellSort();
        
        shellSort.display();
    }
}