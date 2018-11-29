/**
 * Copyright 1998-2012 by Mark Watson. All rights reserved. Originally written
 * by Mark Watson and later review by Rambod Rahmani. The following might be
 * slightly different from the original one.
 */
package chap2.search.maze.depthfirst;

import java.awt.Color;
import java.util.Scanner;

import javax.swing.DebugGraphics;
import javax.swing.JFrame;

import chap2.search.maze.Maze;
import chap2.search.maze.depthfirst.gui.MazeDepthFirstSearchJPanel;

/**
 * @author Rambod Rahmani &lt;rambodrahmani@autistici.org&gt;
 */
public class MazeDepthFirstSearch extends JFrame
{
    /**
     * The serialization runtime associates with each serializable class a version
     * number, called a serialVersionUID, which is used during deserialization to
     * verify that the sender and receiver of a serialized object have loaded
     * classes for that object that are compatible with respect to serialization. If
     * the receiver has loaded a class for the object that has a different
     * serialVersionUID than that of the corresponding sender's class, then
     * deserialization will result in an InvalidClassException. A serializable class
     * can declare its own serialVersionUID explicitly by declaring a field named
     * "serialVersionUID" that must be static, final, and of type long:
     */
    // ANY-ACCESS-MODIFIER static final long serialVersionUID = 42L;
    /**
     * If a serializable class does not explicitly declare a serialVersionUID, then
     * the serialization runtime will calculate a default serialVersionUID value for
     * that class based on various aspects of the class, as described in the
     * Java(TM) Object Serialization Specification. However, it is strongly
     * recommended that all serializable classes explicitly declare serialVersionUID
     * values, since the default serialVersionUID computation is highly sensitive to
     * class details that may vary depending on compiler implementations, and can
     * thus result in unexpected InvalidClassExceptions during deserialization.
     * Therefore, to guarantee a consistent serialVersionUID value across different
     * java compiler implementations, a serializable class must declare an explicit
     * serialVersionUID value. It is also strongly advised that explicit
     * serialVersionUID declarations use the private modifier where possible, since
     * such declarations apply only to the immediately declaring
     * class--serialVersionUID fields are not useful as inherited members.
     */
    private static final long serialVersionUID = 6440782002968347265L;

    // JPanel used to show the maze on the JFrame
    private MazeDepthFirstSearchJPanel depthFirstSearchJPanel = null;

    // Current search engine
    private DepthFirstSearchEngine depthFirstSearchEngine = null;

    /**
     * Default constructor. Creates a {@link DepthFirstSearchEngine} and starts the
     * depth first search on a maze with the specified number of rows and columns.
     * 
     * @param rows
     *            the number of rows of the maze.
     * @param columns
     *            the number of columns of the maze.
     */
    public MazeDepthFirstSearch(int rows, int columns)
    {
	depthFirstSearchEngine = new DepthFirstSearchEngine(rows, columns);

	try
	{
	    // initialize GUI
	    initialize();
	}
	catch (Exception e)
	{
	    System.out.println("GUI initilization error: " + e);
	}

	/**
	 * Repaints this component.<br>
	 * If this component is a lightweight component, this method causes a call to
	 * this component's <code>paint</code> method as soon as possible. Otherwise,
	 * this method causes a call to this component's <code>update</code> method as
	 * soon as possible.
	 */
	repaint();
    }

    /**
     * @throws Exception
     */
    private void initialize() throws Exception
    {
	// TODO: Add scrollbars to the frame.

	this.setContentPane(getDepthFirstSearchJPanel());

	this.setCursor(null);

	// Closing the application when this JFram is closed.
	this.setDefaultCloseOperation(EXIT_ON_CLOSE);

	// JFrame title.
	this.setTitle("Maze Depth First Search");

	// Getting the dimensions of the maze to set the correct size for the JFrame.
	final Maze maze = depthFirstSearchEngine.getMaze();
	final int mazeRows = maze.getRows();
	final int mazeColumns = maze.getColumns();

	// Setting frame size.
	this.setSize(20 + mazeRows * 31, 40 + mazeColumns * 31);

	// Setting frame visible
	this.setVisible(true);
    }

    /**
     * @return the current instance of depthFirstSearchJPanel.
     */
    private MazeDepthFirstSearchJPanel getDepthFirstSearchJPanel()
    {
	if (depthFirstSearchJPanel == null)
	{
	    // Initialize the JPanel if not already initialized.
	    depthFirstSearchJPanel = new MazeDepthFirstSearchJPanel(depthFirstSearchEngine);

	    // Sets the background color of this component.
	    depthFirstSearchJPanel.setBackground(Color.white);

	    // Enables or disables diagnostic information about every graphics operation
	    // performed within the component or one of its children.
	    depthFirstSearchJPanel.setDebugGraphicsOptions(DebugGraphics.NONE_OPTION);

	    depthFirstSearchJPanel.setRequestFocusEnabled(false);
	}

	return depthFirstSearchJPanel;
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
	    System.out.println(
		    "Starting Maze Depth First Search with a maze of size " + inputRows + " by " + inputColumns + ".");

	    // Starts a Depth First Search on a maze of the given dimensions.
	    new MazeDepthFirstSearch(inputRows, inputColumns);
	}
	else
	{
	    System.out.println("Invalid inputs.");
	}

	scanner.close();

	/*
	 * The JFrame that opens will show how poor is the path a depth first search can
	 * find between the start and goal locations in the maze. The maze is a 10-by-10
	 * grid. The letter S marks the starting location in the upper left corner and
	 * the goal position is marked with a G in the lower right corner of the grid.
	 * Blocked grid cells are painted light gray. The basic problem with the depth
	 * first search is that the search engine will often start searching in a bad
	 * direction, but still find a path eventually, even given a poor start. The
	 * advantage of a depth first search over a breadth first search is that the
	 * depth first search requires much less memory. We will see that possible moves
	 * for depth first search are stored on a stack (last in, first out data
	 * structure) and possible moves for a breadth first search are stored in a
	 * queue (first in, first out data structure).
	 */
    }
}
