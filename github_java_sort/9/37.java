













import java.applet.Applet;
import java.awt.Button;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;


public class TwoSorts extends Applet{

	private final int APPLET_WIDTH = 500;
    private final int APPLET_HEIGHT = 500;
    int[] sortSelection;
    int[] sortInsertion;
    private int index = 0;
    private int index2 = 1;
	private int min = 0;
	private int temp;
	
	
	
	public void init()
	   {
	      setBackground (Color.yellow);
	      setSize (APPLET_WIDTH, APPLET_HEIGHT);  
	      
	      sortSelection = new int [10];
	      sortInsertion = new int [10];
	      
	      for(int i = 0; i < sortSelection.length; i++){
	    	  int rand = (int) (Math.random() * 100) + 1;
	    	  sortSelection[i] = rand;
	    	  sortInsertion[i] = rand;
	      }
	      init2();
	   }
	 
	 
	 
	 public void paint (Graphics page)
	   {
		 page.drawString("Selection Sort", 185, 135);
		 page.drawString("Insertion Sort", 185, 285);
		 int location = 150;
		 int location2 = 150;
		 min = index;
		 
 			for (int i = 0; i < sortSelection.length; i++){
 				page.fillRect(location,150,10,sortSelection[i]);
 				location += 15;
		 			}
 			
 			for (int i = 0; i < sortInsertion.length; i++){
 				page.fillRect(location2,300,10,sortInsertion[i]);
 				location2 += 15;
		 			}
			for (int scan = index+1; scan < sortSelection.length; scan++){
            if (sortSelection[scan] < (sortSelection[min]))
            min = scan;
			}
		 		 
	 		temp = sortSelection[min];
	 		sortSelection[min] = sortSelection[index];
	 		sortSelection[index] = temp;
		 			
		 	int key = sortInsertion[index2];
 	        int position = index2;

 	        while (position > 0 && key < (sortInsertion[position-1]))
 	        {
 	        	sortInsertion[position] = sortInsertion[position-1];
 	            position--;
 	        }
 	            
 	        sortInsertion[position] = key;
 	      	}
			   
			Button butn = new Button("Pass");
			
			
			public void init2() {
		        butn.addActionListener(new ButnHandler());
			    this.add(butn); 
			    }
			
			
		    class ButnHandler implements ActionListener {
		        public void actionPerformed(ActionEvent e) {

		        	repaint();
		        	if(index < sortSelection.length - 1){index++;}
		        	else {System.out.println("Selection sort finished");}
		        	if(index2 < sortInsertion.length - 1){index2++;}
		        	else {System.out.println("Insertion sort finished");}
		        } 
		    }    
	 }