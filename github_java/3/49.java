package com.mike.cpsc223j.finalExam;

import java.applet.Applet;
import java.awt.Button;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Label;
import java.awt.TextField;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class HanoiTower extends Applet implements ActionListener {
	private static final long serialVersionUID = 1L;
	
	Graphics graphics;
	
	int tableWidth = 600;
	int tableTopHeight = 340;
	int pegWidth = 20;
	int pegHeight = 260;
	int numDisks = 0;
	int largestDiscWidth = 150;
	int discHeight = 20;
	
	Label lnumDisks = new Label("Enter the number of disks(<=7):");
	
	TextField tfnumDisks = new TextField(null, 5);
	
	Button bstart = new Button("Press to Start");
	
	int[][] hanoiTower = new int[3][7];
	int[] height = new int[3];
	
	public void init () {
		// defaults
		setLayout(null);
		setSize(600,400);		
		
		// populate an empty hanoiTower matrix
		emptyTower();

		// set bounds, add elements
		lnumDisks.setBounds(10, 10, 240, 20); add(lnumDisks);
		tfnumDisks.setBounds(280, 10, 30, 20); add(tfnumDisks);
		bstart.setBounds(330, 10, 150, 20); add(bstart);
		
		// draw some shapes... our initial structure with no discs
		graphics = getGraphics();
		paint(graphics);
		
		// our listener
		bstart.addActionListener(this);
	}
	
	public void emptyTower() {
		height[0] = height[1] = height[2] = 0;
		for (int i = 0; i < hanoiTower.length; i++) {
			for (int j = 0; j < hanoiTower[i].length; j++) {
				hanoiTower[i][j] = -1; // -1 is going to signify "empty"
			}
		}
	}
	
	public void actionPerformed(ActionEvent e) {
		if (e.getSource() == bstart) {
			emptyTower();
			paint(graphics);
			numDisks = Integer.parseInt(tfnumDisks.getText());
			
			// populate the tower
			height[0] = numDisks;
			for (int i = 0; i < numDisks; i++) {
				hanoiTower[0][i] = i;
			}
			paint(graphics); // paint after filling tower

			// show the tower before calling our towerOfHanoi function
			//showTowerInLog(hanoiTower, numDisks);
			
			// do some work, bitch
			towerOfHanoi(numDisks, 0, 2, 1); //  numDisks, source, destination, intermediate
			
			// show the tower after calling our towerOfHanoi function
			//showTowerInLog(hanoiTower, numDisks);
		}
	}
	
	public void showTowerInLog(int[][] hanoiTower, int numDisks) {
		for (int i = 0; i < hanoiTower.length; i++) {
			for (int j = 0; j < numDisks; j++) {
				System.out.println("hanoiTower[" + i + "][" + j + "] = " + hanoiTower[i][j]);
			}
		}
	}
	
	public void towerOfHanoi(int N, int from, int to, int temp) { // definition of elegance
		if (N == 1) {
			moveTo(from, to);
		}	else {
			towerOfHanoi(N-1, from, temp, to); //
			moveTo(from, to); // 1, 3
			towerOfHanoi(N-1, temp, to, from);
		}
	}
	
	public void moveTo(int from, int to) {
		// output as expected by original version of algorithm
		System.out.println((from + 1) + "->" + (to + 1));
		
		// set value of destination equal to the value of the origin
		hanoiTower[to][height[to]] = hanoiTower[from][height[from] - 1];
		
		// reduce height of origin by 1, and increase height of destination by 1
		height[from]--; height[to]++;
				
		// set the value of the origin to "-1", thus removing the disc from origin
		hanoiTower[from][height[from]] = -1;
		
		// repaint our environment.. 
		paint(graphics);
		//Thread.sleep(1000); // this is the one that was being used before
	}
	
	public synchronized void paint(Graphics g) {
		// give our background some contrast
		g.setColor(Color.white);
		g.fillRect(0,  40, 600, 360);
						
		// our tabletop
		g.setColor(Color.BLACK);
		g.fillRect(0, tableTopHeight, tableWidth, 30);
						
		// draw the poles which hold our discs that represent our hanoi tower.
		g.setColor(Color.BLUE);
		g.fillRect(1*(tableWidth/3) - ((tableWidth/3)/2) - pegWidth/2, 80, pegWidth, pegHeight);
		g.fillRect(2*(tableWidth/3) - ((tableWidth/3)/2) - pegWidth/2, 80, pegWidth, pegHeight);
		g.fillRect(3*(tableWidth/3) - ((tableWidth/3)/2) - pegWidth/2, 80, pegWidth, pegHeight);
				
		// let's graphically move some discs.
		g.setColor(Color.RED); int discWidth = largestDiscWidth;
		for (int i = 0; i < hanoiTower.length; i++) {
			int discHeightSpacer = discHeight;
			for (int j = 0; j < numDisks; j++) {
				if (hanoiTower[i][j] != -1) { 
					discWidth = largestDiscWidth - (8*j);
					int horizontalPos = ((i+1)*(tableWidth/3) - ((tableWidth/3)/2) - (discWidth/2));
					int verticalPos = tableTopHeight - discHeightSpacer;
					synchronized(this) {
					    g.fillRect(horizontalPos, verticalPos, discWidth, discHeight); // how to determine x and y position to draw.
					}
					discHeightSpacer += discHeight + 5;
				}
			}
		}
		
		// pause for half a second
		try {
			Thread.sleep(500);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}
}