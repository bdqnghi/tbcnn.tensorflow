package window.levenshteinPopup;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.FontMetrics;
import java.awt.Graphics;
import java.awt.GridLayout;

import javax.swing.BorderFactory;
import javax.swing.JPanel;
import javax.swing.JTextArea;
import javax.swing.border.Border;

import backend.stringDist.LevenshteinDistance;

/**
 * The popup window to show the Levenshtein Distance
 * @author Nathan Ong and Jose Michael Joseph
 */
public class LevenshteinPopup extends JPanel
{
	/**
	 * 
	 */
	private static final long serialVersionUID = -7770124299138867935L;
	
	private final String input;						//The raw keyboard input String
	private final String output;					//The output String
	private final String levenshteinDistanceString;	//The Levenshtein Distance String
	
	//A black border
	private static final Border BORDER_BLACK = BorderFactory.createCompoundBorder(BorderFactory.createEmptyBorder(20, 20, 20, 20), BorderFactory.createLineBorder(Color.BLACK));
	
	//A white border
	private static final Border BORDER_WHITE = BorderFactory.createCompoundBorder(BorderFactory.createEmptyBorder(20, 20, 20, 20), BorderFactory.createLineBorder(Color.WHITE));
	
	//The font to use
	private static final Font FONT = new Font("default", Font.BOLD, 16);
	
	/**
	 * The constructor.
	 * Takes a string array as the Levenshtein Distance String set as provided by the {@link window.keyboard.Keyboard#getLevenshteinSet()} method.
	 * @param levenshteinSet The array of Strings that correspond to the raw keyboard input, the output, and the Levenshtein Distance String. 
	 */
	public LevenshteinPopup(String[] levenshteinSet)
	{
		this(levenshteinSet[0], levenshteinSet[1], levenshteinSet[2]);
	}
	
	/**
	 * The constructor.
	 * Takes each parameter separately.
	 * @param input The String representing the raw input from the keyboard.
	 * @param output The String representing the outputted word.
	 * @param levenshteinDistanceString The Levenshtein Distance String
	 */
	public LevenshteinPopup(String input, String output, String levenshteinDistanceString)
	{
		super();
		this.input = input;
		this.output = output;
		this.levenshteinDistanceString = levenshteinDistanceString;
		
		this.setLayout(new BorderLayout());
		
		//Input String text area
		JTextArea inputArea = new JTextArea("Input: " + this.input);
		inputArea.setFont(FONT);
		inputArea.setEditable(false);
		inputArea.setBorder(BORDER_BLACK);
		
		//Output String text area
		JTextArea outputArea = new JTextArea("Output: " + this.output);
		outputArea.setEditable(false);
		outputArea.setBorder(BORDER_BLACK);
		outputArea.setFont(FONT);
		
		//Levenshtein Visualization text area
		LevenshteinVisualizationTextArea levenshteinDistanceArea = new LevenshteinVisualizationTextArea(this.levenshteinDistanceString);
		levenshteinDistanceArea.setBorder(BORDER_WHITE);
		levenshteinDistanceArea.setFont(FONT);
		
		//add them all to the main JPanel
		JPanel center = new JPanel(new GridLayout(3,1));
		center.add(inputArea);
		center.add(outputArea);
		center.add(levenshteinDistanceArea);
		
		//add it to this JPanel
		this.add(center);
		this.setPreferredSize(new Dimension(1000, 500));
	}//end constructor(String,String,String)
}//end class

/**
 * The class representing the Levenshtein Visualization Text Area.
 * Essentially displays the Levenshtein Distance String nicely.
 * @author Nathan Ong and Jose Michael Joseph
 */
class LevenshteinVisualizationTextArea extends JPanel
{
	/**
	 * 
	 */
	private static final long serialVersionUID = 6770702192295468283L;
	
	private final String levenshteinDistanceString;	//The Levenshtein Distance String
	private final boolean verbose;
	
	/**
	 * The constructor.
	 * Defaults to including description of how the color-coding works.
	 * @param levenshteinDistanceString The Levenshtein Distance String.
	 */
	public LevenshteinVisualizationTextArea(String levenshteinDistanceString)
	{
		this(levenshteinDistanceString, true);
	}
	
	/**
	 * The constructor.
	 * @param levenshteinDistanceString The Levenshtein Distance String.
	 * @param verbose The boolean representing whether or not to include a description of what the colors mean.
	 */
	public LevenshteinVisualizationTextArea(String levenshteinDistanceString, boolean verbose)
	{
		super();
		super.setBackground(Color.BLACK);
		this.levenshteinDistanceString = levenshteinDistanceString;
		this.verbose = verbose;
	}
	
	/**
	 * {@inheritDoc}
	 * Shows the Levenshtein Distance String as color-coded text.
	 * Includes a description of the color coding if verbose is set to true.
	 */
	@Override
	public void paintComponent(Graphics g)
	{
		super.paintComponent(g);
		
		FontMetrics fm = g.getFontMetrics();
		int currX = 20;
		int currY = 20 + fm.getHeight();
		
		//output the Levenshtein Distance String as color coded.
		for(int i = 0; i < this.levenshteinDistanceString.length(); i++)
		{
			char c = this.levenshteinDistanceString.charAt(i);
			switch(c)
			{
				case LevenshteinDistance.INSERTION:
					g.setColor(Color.YELLOW);
					break;
				case LevenshteinDistance.SAME:
					g.setColor(Color.CYAN);
					break;
				case LevenshteinDistance.DELETION:
					g.setColor(Color.RED);
					break;
				default:
					char[] toDraw = null;
					//spaces can't be colored, so include the symbol representing the operation done to the space
					if(c == ' ')
					{
						toDraw = new char[]{this.levenshteinDistanceString.charAt(i-1), c};
					}
					else
					{
						toDraw = new char[]{c};
					}
					g.drawChars(toDraw, 0, toDraw.length, currX, currY);
					currX += fm.charsWidth(toDraw, 0, toDraw.length);
					break;
			}//end switch
		}//end for
		
		//display the distance
		currX = 20;
		currY = 20 + 2*fm.getHeight();
		g.setColor(Color.WHITE);
		String distance = ", Distance = " + LevenshteinDistance.calculateLevenshteinDistance(this.levenshteinDistanceString);
		g.drawChars(distance.toCharArray(), 0, distance.length(), currX, currY);
		
		//if not verbose, then don't include the description
		if(!this.verbose)
		{
			return;
		}
		
		//color coding descriptions
		currX = 20;
		currY = 20 + 3*fm.getHeight();
		String[] colorDescriptions = new String[]{"YELLOW indicates addition, ", "CYAN indicates the same, ", "RED indicates removal."};
		for(int i = 0; i < colorDescriptions.length; i++)
		{
			switch(i)
			{
				case 0:
					g.setColor(Color.YELLOW);
					break;
				case 1:
					g.setColor(Color.CYAN);
					break;
				case 2:
					g.setColor(Color.RED);
					break;
			}
			g.drawChars(colorDescriptions[i].toCharArray(), 0, colorDescriptions[i].length(), currX, currY);
			currX += fm.charsWidth(colorDescriptions[i].toCharArray(), 0, colorDescriptions[i].length());
		}//end for
		
		//why spaces have symbols in front of them
		currX = 20;
		currY = 20 + 4*fm.getHeight();
		g.setColor(Color.WHITE);
		String spaceDescription = "A symbol with a space indicates the operation needed regarding the space in the input/output";
		g.drawChars(spaceDescription.toCharArray(), 0, spaceDescription.length(), currX, currY);
	}//end method(Graphics)
}//end class
