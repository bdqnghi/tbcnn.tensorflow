import javax.swing.*;
import java.awt.*;
import java.util.Stack;
import java.util.Scanner;
import java.util.*;
public class Towerofhanoi extends JFrame
{
    private class DrawCanvas extends JPanel
    {
    
    Stack<Block> stack;
    
    public DrawCanvas(Color colour, Stack<Block> stack) 
    
    {
        setBackground(colour.CYAN);
        this.stack = stack;
    }
    
    
    public void paintComponent(Graphics g)
    {
        super.paintComponent(g);
        g.setColor(new Color(100, 130, 106));
        g.fillRect(90, 25, 10, 295);
        // 3 pegs
        if (stack.empty())
        return;
        
        int x = 100;
        int y = 320 - 30*stack.size();
        int width;
        
        Stack<Block> temp =(Stack<Block>)stack.clone();
        while (!temp.empty())
        {
        width = ((Block)(temp.pop())).getSize();
        g.setColor(Color.black);
        g.drawRect(x - width/2, y, width, 30);
        g.setColor(new Color(150, 150, 150));
        //rectangular plate
        g.fillRect(x-width/2+1, y+1, width-1, 29);
        y=y+30;
        }

    }
    }

    private  DrawCanvas peg1, peg2, peg3;
    public Stack<Block> source, destination, auxillary;
    public Stack<String> sr,des,aux;
    public final static int DELAY = 2000;
    public static int n;


    public Towerofhanoi()
    {
    source = new Stack<Block>();
    destination = new Stack<Block>();
    auxillary = new Stack<Block>();
    sr= new Stack <String>();
    des=new Stack<String>();
    aux=new Stack<String>();
   // int n;
   Scanner sc= new Scanner(System.in);
    System.out.println("Enter number of disk on A peg");
     n=sc.nextInt();

    
    for (int i = 0; i<n; i++)
       source.push(new Block(158 - 11*i));
    //
    setSize(1050, 350);
    //width
    setTitle("Restricted Tower of Hanoi ");
    setResizable(true);
    setDefaultCloseOperation(EXIT_ON_CLOSE);
    setLayout(new GridLayout(1, 3));
    peg1 = new DrawCanvas(new Color(239, 216, 137), source);
    //Graphics g = canvas1.getGraphics();
    //g.setColor(new Color(255, 0, 0));
    //g.drawString("Hello", 200, 200); 
    //TextField t1=new TextField("source"); 
    //t1.setBounds(150,200, 300,30);   
    //add(t1);
    peg3 = new DrawCanvas(new Color(239, 216, 137), destination);
    //TextField t2=new TextField("source"); 
    //t2.setBounds(150,200, 300,30);   
    //add(t2);
    peg2 = new DrawCanvas(new Color(239, 216, 137), auxillary);
    //TextField t3=new TextField("destination"); 
    //t3.setBounds(150,200, 300,30);   
    //add(t3);

    add(peg1);
    add(peg2);
    add(peg3);
    //JButton b=new JButton("Click Here");  
    //b.setBounds(1050,1000,95,30);  
    //add(b);  

    setVisible(true);
    }

    public void paintAll()
    {
    	peg1.repaint();
    	peg2.repaint();
    	peg3.repaint();
    }

    public void towerhanoi(int n, Stack<Block> A, Stack<Block> C, Stack<Block> B)
    {

	    
	    if(n==0)
	    {
	     	return;
	     }
	     else
	     {
		    towerhanoi(n-1,A,C,B);	
		    B.push(A.pop());
		    paintAll();
		    Wait.manySec(DELAY);
		    towerhanoi(n-1,C,A,B);
		    C.push(B.pop());
		    paintAll();
		    Wait.manySec(DELAY);
		    towerhanoi(n-1,A,C,B);
	    }
    
}
public void hanoi1(int n,Stack<String> source,Stack<String> destination,Stack<String> auxillary )
{
    	if(n==0)
    
        return;
    
	    hanoi1(n-1,source,destination,auxillary);
	    
	     
	    System.out.println(n +"  disk from  peg A "+" to peg B" );
	    hanoi1(n-1,destination,source,auxillary);
	    
	    System.out.println(n +"  disk from  peg B "+" to peg C" );
	    hanoi1(n-1,source,destination,auxillary);
    
}

    public static void main(String[] args)
    {
        //int n ;
        //Scanner sc= new Scanner(System.in);
        //System.out.println("Enter number of disk");
        //int n=sc.nextInt();
        Stack<String> source = new Stack<String>();
        Stack<String> auxillary = new Stack<String>();
        Stack<String> destination = new Stack<String>();
	        
	    Towerofhanoi solver = new Towerofhanoi();
	    solver.towerhanoi(n, solver.source, solver.destination, solver.auxillary);
	    System.out.println("The sequences of moves are:---");
	    System.out.println("A = source peg , B = auxillary peg, C = destination peg");
	    solver.hanoi1(n, source, destination, auxillary);
    }
}


class Block
{
    private int size;
    private int moveblock;
    public Block(int size)
    {
    this.size = size;
    moveblock = 0;
    }
    public void move()
    {
    moveblock++;
    }
    public int getSize()
    {
    	return size;
    }
}

class Wait 
{
  public static void oneSec() 
  {
     try 
     {
       Thread.currentThread().sleep(1000);
       }
     catch (InterruptedException e)
      {
       e.printStackTrace();
       }
     }  
  public static void manySec(long sec) 
  {
     try 
     {
       Thread.currentThread().sleep(sec);
    }
     catch (InterruptedException e) 
     {
       e.printStackTrace();
       }
     }
}
