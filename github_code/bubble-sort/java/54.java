/*
 * Bsado en el codigo de German Hernandez
   *Alvaro Andres Tovar 256203
   *bubblesort 
*/
 
 
 
import java.applet.*;
import java.awt.*;
import javax.swing.*;
import java.lang.System;


public class bubblesort extends Applet 
{	
  
	static long total = 0;
	static long cases = 0;
	static double frec[] = new double[151];
	static int minFrec=150;
	static int maxFrec=0;
	static int n=0;
	static long totaltime = 0;
	static long estimatedTime=0;
	static long totalsteptime=0;
	static long steptime=0;
	
  static int bubbleSort(int v[])
    {
        
        int pasos = 0;
        int j;
        int i;
        int cadena[]= new int[n];
        
        long startTime = System.nanoTime();

        for( i=0; i < v.length; i++ )
        {
            for( j = v.length-1; j >= i+1; j--)
            {
                if(v[j] < v[j-1])
                {
                    swap(v,j,j-1);
                    pasos+=3;
                }
                pasos+=3;
            }
            pasos+=3;
        }
        estimatedTime = System.nanoTime() - startTime;
        steptime=estimatedTime/pasos;
        System.out.print(" T_estimado="+estimatedTime +"ns"+" T_promedio_paso="+steptime +"ns");

        /*for(i=0; i < v.length ;i++)
        {
            cadena[i] = v[i];
        }
        for (j=0; j<n; j++) System.out.print(v[j]);
        System.out.print(" ");
        for( i=0; i < cadena.length; i++ )
        {
            for( j = cadena.length-1; j >= i+1; j--)
            {
                if(cadena[j] < cadena[j-1])
                {
                    swap(cadena,j,j-1);
                    pasos++;
                }
            }
        }*/
        //for (j=0; j<n; j++) System.out.print(v[j]);
        //System.out.print(" ");
        
        //System.out.print(pasos +" ");
        return pasos;
    }
	
static void swap (int v[], int i, int j) {
	int	t;

	t = v[i];
	v[i] = v[j];
	v[j] = t;
}

/* recursive function to generate permutations 
	 based on c code from
	 http://www.cs.utexas.edu/users/djimenez/cs3343
*/
static void perm (int v[],int i, int n) {

	/* this function generates the permutations of the array
	 * from element i to element n-1
	 */
	int j = 0;	
	int k = 0;
	 
	/* if we are at the end of the array, we have one permutation
	 * we can use (here we print it; you could as easily hand the
	 * array off to some other function that uses it for something
	 */
	if (i == n) {
			
			cases++;
			System.out.print("perm("+cases+"): ");
		  for (j=0; j<n; j++) System.out.print(v[j]);
			
			
	  	k = bubbleSort(v);
			total+=k;
			totaltime+=estimatedTime;
			totalsteptime+=steptime;
			frec[k]++;
			
			
    	System.out.println(" Steps:"+k);
		
	} else
        {	
                 /* recursively explore the permutations starting
		 * at index i going through index n-1
		 */
		for (j=i; j<n; j++) {

			/* try the array with i and j switched */

			swap (v, i, j);
			perm (v, i+1, n);

			/* swap them back the way they were */

			swap (v, i, j);
		}
		
        }
	
}

	public void init() {
  	  	
		n = 5;
		setSize(700, 500);	
	}
	
		
	
	
	
	public void paint(Graphics g) {
		
		int k = 0;
	 	int v[] = new int[n];
		total = 0;
		totaltime = 0;
		totalsteptime = 0;
		cases = 0;
		minFrec=150;
		maxFrec=0;	
		
		for(k=0; k<151; k++) frec[k] = 0;
		
		for(k=0; k<n; k++){
				v[k]=k+1;
		} 
		
		perm(v,0,n);
		System.out.println(" Tiempo total:"+totaltime+" / Numero total de pasos:"+total+" Tiempo promedio por paso:"+totalsteptime/cases);
		
		for(k=0; k<151; k++){
					frec[k] /= (double)cases;
					if (( frec[k] > 0) && (minFrec > k)) minFrec = k;
					if (( frec[k] > 0) && (maxFrec < k)) maxFrec = k;
                }
	
		
		int i = 0;
		
		g.setColor(Color.black);
		g.drawString("Probability",10,30);
		g.drawString("Steps",350,320);
		g.drawString("n = "+n,400,30);
		g.drawString("Number of permutations = "+ cases,400,45);
		g.drawString("Average number of steps =  " + +((double) total)/((double)cases) ,400,60);
		g.drawString("Average time=  " + +((double) totalsteptime)/((double)cases) ,400,75);
		int y = 75;
		for(i=minFrec; i <= maxFrec; i++) {
			y += 15;
			g.drawString("P("+i+")="+frec[i] ,400,y);		
		}
		
		g.setColor(Color.red);
		g.drawLine(50,50,50,300);
		g.drawLine(50,300,350,300);	
		
		g.setColor(Color.black);
		
		g.drawString("1.0", 10, 50);
		g.drawString("0.8", 10, 100);
		g.drawString("0.6", 10, 150);
		g.drawString("0.4", 10, 200);
		g.drawString("0.2", 10, 250);
		g.drawString("0.0", 10, 300);
		
		int yf;
		int shift = (int) (200.0/(double)(maxFrec-minFrec+1));
		int ishift = (int) (100.0/(double)(maxFrec-minFrec+1));
		g.setColor(Color.blue);
		for (i=minFrec; i< (maxFrec+1); i=i+1){
		  yf = (int) (frec[i] *250.0) ;
			g.fillRect(50+((i-minFrec)*shift),300-yf, shift, yf);
			g.drawString(""+i,50+ishift+((i-minFrec)*shift) , 310);
		
		}
		
		
	}		
	
	public void setn(int n_value) {
      n = n_value;
			repaint();
			
   }
	
}


