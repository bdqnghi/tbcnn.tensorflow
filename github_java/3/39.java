package TowerOfHanoi.Graphics;

/**
 * Implementing the Tower of Hanoi classical algorithm
 * @author Muhammed Ahad
 * e-mail: ahad3112@yahoo.com
 */

import TowerOfHanoi.test.TowerOfHanoi;
import TowerOfHanoi.test.Plate.TowerPlate;
import javax.swing.*;
import java.awt.*;
import java.util.*;

/**
 * reference Check this for drawing. http://stackoverflow.com/questions/10628492/dynamic-graphics-object-painting
 * @author maaahad
 *
 */

public class DrawGraphics extends JPanel{
	
	// plate height 
	private int plateHeight = 500/TowerOfHanoi.n;
	private int[] plateLength = new int[TowerOfHanoi.n]; // length will be based on the plate size
	private int[] plateX = new int[TowerOfHanoi.n];
	private int[] plateY = new int[TowerOfHanoi.n];
	private int[] plateNo = new int[TowerOfHanoi.n];
	
	// constructor
	public DrawGraphics(LinkedList<TowerPlate> plateList){
		int i = 0;
		for(TowerPlate plate: plateList){
			plateNo[i] = plate.getPlateNo();
			plateLength[i] = plate.getPlateNo()*20;
			plateX[i] = 400+plate.getPlatePosX()+10+(TowerOfHanoi.n-plate.getPlateNo())*10;
			plateY[i] = (TowerOfHanoi.n-1-plate.getPlatePosY())*plateHeight+30;
			i++;
		}
	}

	public void paintComponent(Graphics g){
		super.paintComponent(g);
		g.drawString("Destination Tower after solving the puzzle.",350, 650);
		Graphics2D g2 = (Graphics2D)g;
		g2.setColor(Color.BLUE);
		
		for(int i=0;i<TowerOfHanoi.n;i++){
			g2.drawRect(plateX[i], plateY[i], plateLength[i], plateHeight);
			g2.drawString(String.valueOf(plateNo[i]),plateX[i]+5 ,plateY[i]+20);
			//g2.fillRect(plateX[i], plateY[i], plateLength[i], plateHeight);
		}
	}
}
