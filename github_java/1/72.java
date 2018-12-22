/**
 * Copyright 1998-2012 by Mark Watson. All rights reserved. Originally written
 * by Mark Watson and later review by Rambod Rahmani. The following might be
 * slightly different from the original one.
 */
package chap2.search.maze.breadthfirst;

import java.awt.Color;
import java.util.Scanner;

import javax.swing.DebugGraphics;
import javax.swing.JFrame;

import chap2.search.maze.Maze;
import chap2.search.maze.breadthfirst.gui.MazeBreadthFirstSearchJPanel;

/**
 * @author Rambod Rahmani &lt;rambodrahmani@autistici.org&gt;
 */
public class MazeBreadthFirstSearch extends JFrame
{
    /**
     * Serial Version UID.
     */
    private static final long serialVersionUID = -7813706126969126099L;

    // JPanel used to show the maze on the JFrame
    private MazeBreadthFirstSearchJPanel breadthFirstSearchJPanel = null;

    // Current search engine
    private BreadthFirstSearchEngine breadthFirstSearchEngine = null;

    /**
     * Default constructor. Creates a {@link BreadthFirstSearchEngine} and starts
     * the breadth first search on a maze with the specified number of rows and
     * columns.
     * 
     * @param rows
     *            the number of rows of the maze.
     * @param columns
     *            the number of columns of the maze.
     */
    public MazeBreadthFirstSearch(int rows, int columns)
    {
	breadthFirstSearchEngine = new BreadthFirstSearchEngine(rows, columns);

	try
	{
	    // initialize GUI
	    initialize();
	}
	catch (Exception e)
	{
	    System.out.println("GUI initilization error: " + e);
	}

	repaint();
    }

    /**
     * @throws Exception
     */
    private void initialize() throws Exception
    {
	// TODO: Add scrollbars to the frame.

	this.setContentPane(getBreadthFirstSearchJPanel());

	this.setCursor(null);

	// Closing the application when this JFram is closed.
	this.setDefaultCloseOperation(EXIT_ON_CLOSE);

	// JFrame title.
	this.setTitle("MazeBreadthFirstSearch");

	// Getting the dimensions of the maze to set the correct size for the JFrame.
	final Maze maze = breadthFirstSearchEngine.getMaze();
	final int mazeRows = maze.getRows();
	final int mazeColumns = maze.getColumns();

	// Setting frame size.
	this.setSize(20 + mazeRows * 31, 40 + mazeColumns * 31);

	// Setting frame visible
	this.setVisible(true);
    }

    /**
     * @return the current instance of breadthFirstSearchJPanel.
     */
    private MazeBreadthFirstSearchJPanel getBreadthFirstSearchJPanel()
    {
	if (breadthFirstSearchJPanel == null)
	{
	    // Initialize the JPanel if not already initialized.
	    breadthFirstSearchJPanel = new MazeBreadthFirstSearchJPanel(breadthFirstSearchEngine);

	    // Sets the background color of this component.
	    breadthFirstSearchJPanel.setBackground(Color.white);

	    // Enables or disables diagnostic information about every graphics operation
	    // performed within the component or one of its children.
	    breadthFirstSearchJPanel.setDebugGraphicsOptions(DebugGraphics.NONE_OPTION);

	    breadthFirstSearchJPanel.setRequestFocusEnabled(false);
	}

	return breadthFirstSearchJPanel;
    }

    /**
     * Developer test harness.
     * 
     * @param args
     */
    public static void main(String[] args)
    {
	int inputRows = -1;
	int inputColumns = -1;
	Scanner scanner = new Scanner(System.in);

	System.out.println("Maze Depth First Search");
	System.out.println("-----------------------");
	System.out.println("Enter the number of rows:");
	inputRows = scanner.nextInt();

	System.out.println("Enter the number of columns:");
	inputColumns = scanner.nextInt();

	if ((inputRows > 0) && (inputColumns > 0))
	{
	    System.out.println("Starting Maze Breadth First Search with a maze of size " + inputRows + " by "
		    + inputColumns + ".");

	    // Starts a Breadth First Search on a maze of the given dimensions.
	    new MazeBreadthFirstSearch(inputRows, inputColumns);
	}
	else
	{
	    System.out.println("Invalid inputs.");
	}

	scanner.close();
    }
}
