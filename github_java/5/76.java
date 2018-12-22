import java.io.*;
import java.util.*;

// DO NOT!! IMPORT JAVA.LANG

public class Swamp
{
  	// JUST FOR YOUR DEBUGGING - DELETE THIS METHOD AND ITS CALL BEFORE HANDIN 
	// ----------------------------------------------------------------
	private static void printSwamp(String label, int[][] swamp )
	{
		System.out.println( label );
		System.out.print("   ");
		for(int c = 0; c < swamp.length; c++)
			System.out.print( c + " " ) ;
		System.out.print( "\n   ");
		for(int c = 0; c < swamp.length; c++)
			System.out.print("- ");
		System.out.print( "\n");

		for(int r = 0; r < swamp.length; r++)
		{	System.out.print( r + "| ");
			for(int c = 0; c < swamp[r].length; c++)
				System.out.print( swamp[r][c] + " ");
			System.out.println("|");
		}
		System.out.print( "   ");
		for(int c = 0; c < swamp.length; c++)
			System.out.print("- ");
		System.out.print( "\n");
	}
	// --YOU-- WRITE THIS METHOD (LOOK AT PRINTSWAMP FOR CLUES)
   	// ----------------------------------------------------------------
	private static int[][] loadSwamp( String infileName, int[] dropInPt  ) throws Exception
	{
		File swampFile = new File( infileName );
		Scanner inputFile = new Scanner( swampFile );
		
		int dimension = inputFile.nextInt();
		dropInPt[0] = inputFile.nextInt();
		dropInPt[1] = inputFile.nextInt();
		int[][] swamp = new int[dimension][dimension];
		for( int r = 0; r < swamp.length; r++ )
			for( int c = 0; c < swamp.length; c++ )
				swamp[r][c] = inputFile.nextInt();
		inputFile.close();		
		return swamp;
	}
	public static void main(String[] args) throws Exception
	{
		int[] dropInPt = new int[2]; // row and col will be on the 2nd line of input file;
		int[][] swamp = loadSwamp( args[0], dropInPt );
		
		//check 1
		String label1 = "loaded swamp";
		printSwamp( label1, swamp );
		
		
		int row=dropInPt[0], col = dropInPt[1];	
		
		//check 2
		System.out.println( dropInPt[0] + " " + dropInPt[1] );
		
		String path = ""; // with each grows to => "[2,3][3,4][3,5][4,6]" etc 
		depthFirstSearch( swamp, row, col, path );
		
		
	} // END MAIN

	static void depthFirstSearch( int[][] swamp, int r, int c, String path )
	{
		//append new [r,c] to path string
		path += ("[" + r + "," + c + "]" );
		
	
		
		//check if on edge of swamp
		if ( onEdge( r, c, swamp ) ) 
		{
			System.out.println( path );
			return;
		}
		
		//begin DFS algorithm
		//start clockwise sweep of neighboring cells
		
		//check N
		if( swamp[r-1][c] == 1 )
		{
			swamp[r][c] = -1;
			depthFirstSearch( swamp, r-1, c, path );
			swamp[r][c] = 1;
		}
		//check NE
		if( swamp[r-1][c+1] == 1 )
		{
			swamp[r][c] = -1;
			depthFirstSearch( swamp, r-1, c+1, path );
			swamp[r][c] = 1;
		}
		//check E
		if( swamp[r][c+1] == 1 )
		{
			swamp[r][c] = -1;
			depthFirstSearch( swamp, r, c+1, path );
			swamp[r][c] = 1;
		}
		//check SE
		if( swamp[r+1][c+1] == 1 )
		{
			swamp[r][c] = -1;
			depthFirstSearch( swamp, r+1, c+1, path );
			swamp[r][c] = 1;
		}
		//check S
		if( swamp[r+1][c] == 1 )
		{
			swamp[r][c] = -1;
			depthFirstSearch( swamp, r+1, c, path );
			swamp[r][c] = 1;
		}
		//check SW
		if( swamp[r+1][c-1] == 1 )
		{
			swamp[r][c] = -1;
			depthFirstSearch( swamp, r+1, c-1, path );
			swamp[r][c] = 1;
		}
		//check W
		if( swamp[r][c-1] == 1 )
		{
			swamp[r][c] = -1;
			depthFirstSearch( swamp, r, c-1, path );
			swamp[r][c] = 1;
		}
		//check NW
		if( swamp[r-1][c-1] == 1 )
		{
			swamp[r][c] = -1;
			depthFirstSearch( swamp, r-1, c-1, path );
			swamp[r][c] = 1;
		}
		
		return;
		
		
	} // END DFS
	
	static boolean onEdge( int r, int c, int[][] swamp )
	{
		if( r == 0 || r == swamp.length-1 || c == 0 || c == swamp.length-1 ) return true;
		return false;
	}//END onEdge

}
