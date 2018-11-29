/*Jaspreet Ranjit, jr4fs, Professor Edwards
 * Insertion Sort: https://www.geeksforgeeks.org/insertion-sort/
 * used same format for bubblesorter and selectionsorter
 * https://en.wikipedia.org/wiki/Insertion_sort
 */
//insert necessary packages
import java.awt.*;
import javax.swing.*;

public class InsertionSorter {

	private int[] arr;
	private int sorted= -1;
	private int firstSpot = -1;
	private int secondSpot = -1;
	private JComponent component;

	private static final int DELAY = 100;
	
	/*Constructs selection sorter.
	 * takes in array to sort and component
	 */

	public InsertionSorter(int[] arrayOne, JComponent element) {
		arr = arrayOne;
		component = element;
	}
//http://www.java2novice.com/java-sorting-algorithms/insertion-sort/
	public void draw(Graphics var) {

		int change = component.getWidth() / arr.length;
		for (int i = 0; i < arr.length; i++) {
			if (i == firstSpot) {
				var.setColor(Color.YELLOW);
			} else if (i == secondSpot) {
				var.setColor(Color.YELLOW);
			} else if (i < sorted) {
				var.setColor(Color.GRAY);
			} else {
				var.setColor(Color.BLACK);
			}
			var.fillRect(i * change, 0, 5, 5*arr[i]);
		}
	} 	
	//https://www.geeksforgeeks.org/insertion-sort/
		//TA gave me advice on using pause(2), Worked together with another student in office hours to work through logic of the method
	//Liana poon and i worked on this sort method together with the TA and used the website to get an idea behind the logic
		public void sort() throws InterruptedException {
			int i = 1;
			while (i < arr.length) {
				//try block to catch interrupted exception thrown by sort() method
				try {
					int j = i;
					while (j > 0 && arr[j-1] > arr[j]) {
						int i1 = arr[j];
						int i2 = arr[j-1];
						arr[j] = i2;
						arr[j-1] = i1;
						j--;					
					}
					i++;
					sorted = i;
					firstSpot = i;
					secondSpot = j;
				} finally {

				}
				pause(2);
			}
		}
	public void pause(int g)
			throws InterruptedException
	{
		component.repaint();
		Thread.sleep(g * DELAY);
	}

}
