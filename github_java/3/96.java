import java.lang.reflect.Array;

class Tower{
    Stack<Integer> disks;

    Tower(int ndisks){
        disks = new Stack<>(ndisks);
    }
}

class TOH{ 
    int n;
    Tower[] towers;
    
    TOH(int disks, int sourceTower){ 
        n = disks;
        towers = (Tower[])Array.newInstance(Tower.class, 3);
        for(int i=0;i<towers.length;++i)towers[i] = new Tower(n);
        for(int i=disks;i>=1;--i)towers[sourceTower].disks.push(i);
    }
    
    void move(int disks, Tower source, Tower destination, Tower buffer){
        if(disks==1)destination.disks.push(source.disks.pop());
        else{
            move(disks-1, source, buffer, destination); 
            destination.disks.push(source.disks.pop());
            move(disks-1, buffer, destination, source);
        }
    }
    
    void move(int source, int buffer, int destination){
        if(towers[source].disks.isEmpty())System.out.println("Tower is empty!");
        else move(n, towers[source], towers[destination], towers[buffer]);
    }
}

public class Code{
    public static void main(String[] args){
        TOH toh = new TOH(4, 0);
        toh.move(0, 1, 2);
        while(!toh.towers[2].disks.isEmpty()){
            System.out.println(toh.towers[2].disks.pop());
        }
    }
}

Stack Class

public class Stack <T>{
    int top = -1; 
    T[] elements;
    
    public Stack(int size){  
        elements = (T[])new Object[size];  
    }
    
    public int size(){ 
        return top+1;
    }
    
    public void push(T element){ 
        if(top+1 == elements.length){
            System.out.println("Overflow.");
            return;
        }
        elements[++top] = element;
    }
    
    public T pop(){
        if(top<0){
            System.out.println("Underflow.");
            return null;
        }
        return elements[top--];
    }
        
    public T peek(){
        if(top < 0){
            System.out.println("Stack is empty!");
            return null;
        }
        return elements[top];
    }
    
    public boolean isEmpty(){
        return top==-1;
    } 
}
