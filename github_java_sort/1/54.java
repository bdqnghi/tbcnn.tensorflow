

import java.awt.*;
import javax.swing.*;

public class InsertionSorter {

	private int[] arr;
	private int sorted= -1;
	private int firstSpot = -1;
	private int secondSpot = -1;
	private JComponent component;

	private static final int DELAY = 100;
	
	

	public InsertionSorter(int[] arrayOne, JComponent element) {
		arr = arrayOne;
		component = element;
	}

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
	
		
	
		public void sort() throws InterruptedException {
			int i = 1;
			while (i < arr.length) {
				
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
