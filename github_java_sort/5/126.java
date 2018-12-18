

import java.awt.*;
import javax.swing.*;

public class BubbleSorter {
	private int[] arr;
	private int sorted= -1;
	private int firstSpot = -1;
	private int secondSpot = -1;
	private JComponent component;

	private static final int DELAY = 100;

	

	public BubbleSorter(int[] arrayOne, JComponent element) {
		arr = arrayOne;
		component = element;
	}


	public void draw(Graphics var) {

		int change = component.getWidth() / arr.length;
		for (int i = 0; i < arr.length; i++) {
			if (i == firstSpot) {
				var.setColor(Color.PINK);
			} else if (i == secondSpot) {
				var.setColor(Color.GREEN);
			} else if (i < sorted - 1) {
				var.setColor(Color.BLACK);
			} else if (i >= sorted) {
				var.setColor(Color.GRAY);
			}else {
				var.setColor(Color.BLACK);
			}
			var.fillRect(i * change, 0, 5, 5*arr[i]);
		}
	} 
	
	 
	public void sort() throws InterruptedException {

		for (int i = 0; i < arr.length - 1; i++) {
			for (int j = 0; j < arr.length - i - 1; j++) {
				if (arr[j] > arr[j+1]) {
					int temp = arr[j];
					arr[j] = arr[j+1];
					arr[j+1] = temp;
				}
				firstSpot = j+1;
				sorted = arr.length-i;
				pause(1);
			}
		}
	}
	public void pause(double o)
			throws InterruptedException
	{
		component.repaint();
		Thread.sleep((long) (o * DELAY));
	}
}