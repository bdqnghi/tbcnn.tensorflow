/**
 * Student Name: Mohammed Alshutwi
 * Student ID: 18187708
 */

import java.io.*;
import java.util.*;

// This class manages the collection of words by using separate chaining 
// HashTable. The structure of this HashTable is an ArrayList of ArrayLists 
// containing AVL-Trees.
public class HashTable
{
    public static int ENGLISH_ALPHABETS = 26;   // This is the size of the main HashTable
    public static int MAX_WORD_LENGTH = 40;     // This is the size of the secondary HashTable

    private ArrayList<ArrayList<AVLTree>> data;

    public HashTable ()
    {
        // initiating the main HashTable
        data = new ArrayList<ArrayList<AVLTree>>();

        // for each bucket in the main HashTable:
        for ( int i = 0; i < ENGLISH_ALPHABETS; i++ )
            {
                // initiating and adding a secondary HashTable
                data.add( new ArrayList<AVLTree>() );

                // for each bucket the secondary HashTable:
                for ( int j = 0; j < MAX_WORD_LENGTH; j++ )
                    {
                        // initiating and adding an AVL-tree
                        data.get( i ).add( new AVLTree() );
                    }
            }
    }

    // This the hash function that hashes string key.
    // It returns an array of two integers as indicating
    // the location of the bucket in the secodary HashTable
    public int[] hash ( String key )
    {
        int[] hashValues = new int[ 2 ];
        char ch = key.charAt( 0 );

        hashValues[ 0 ] = ( ch - 'a' );                             // the bucket location in the main HashTable
        hashValues[ 1 ] = key.length() > 40? 39 : key.length()-1 ;  // the bucket location in the secondary HashTable

        return hashValues;
    }

    // This method for inserting a new word
    public void insert ( Word word )
    {
        // getting the appropriate bucket i.e. AVL-Tree
        int[] location = hash( word.getLetters() );
        AVLTree bucket = data.get( location[ 0 ] )
                             .get( location[ 1 ] );

        // invoking the AVL-Tree to insert the word
        bucket.insert( word );
    }

    // This method is for searching for words
    public Word search ( String letters )
    {
        // getting the appropriate bucket i.e. AVL-Tree
        int[] location = hash( letters );
        AVLTree bucket = data.get( location[ 0 ] )
                             .get( location[ 1 ] );

        // invoking the AVL-Tree to search the word
        return bucket.search( letters );
    }

    // This method is for displaying and writing the whole elements
    public void displayAndWrite ( PrintWriter outFile )
    {
        // for each bucket in the main HashTable:
        for ( int i = 0; i < ENGLISH_ALPHABETS; i++ )
            {
                // for each bucket in the secondary HashTable:
                for ( int j = 0; j < MAX_WORD_LENGTH; j++ )
                    {
                        // invoking the AVL-Tree to display and write its elements
                        data.get( i )
                            .get( j )
                            .displayAndWriteElements( outFile );
                    }
            }
    }

    // This method is for searching a word's neighbours
    public void checkNeighboursOfWord ( Word word )
    {
        // for each bucket in the main the HashTable:
        for ( int i = 0; i < ENGLISH_ALPHABETS; i++ )
            {
                // invoking the AVL-Tree containing words of the same
                // length as the parameter to search for neighbours
                data.get( i )
                    .get( word.length()-1 )
                    .checkNeighboursOfWord( word );
            }
    }

    // This method is for searching for matches
    public void findMatches ( Pattern pattern )
    {
        // getting a range of locations where a match can be found
        int[][] traverseRange = getTraverseRangeForMatchSearch( pattern );

        // for each bucket in the main HashTable having location within the range:
        for ( int i = traverseRange[ 0 ][ 0 ]; i <= traverseRange[ 0 ][ 1 ]; i++ )
            {
                // for each bucket in the secondary HashTable having location within the range:
                for ( int j = traverseRange[ 1 ][ 0 ]; j <= traverseRange[ 1 ][ 1 ]; j++ )
                    {
                        // invoking the AVL-Tree to search for matches
                        data.get( i )
                            .get( j )
                            .findMatches( pattern );
                    }
            }
    }

    // This method is for defining trverse range for searching for matches
    private int[][] getTraverseRangeForMatchSearch ( Pattern pattern )
    {
        int[][] range = new int[ 2 ][ 2 ];

        // difining the minimum shape that a match can get
        String patternMinCharacters = pattern.getCharacters()
                                             .replaceAll("\\*", "")
                                             .replaceAll("\\?", "a")
                                             .trim();
  
        // difining the maximum shape that a match can get
        // if the pattern doesn't contain '*'
        String patternMaxCharacters = pattern.getCharacters()
                                             .replaceAll("\\*", "")
                                             .replaceAll("\\?", "z")
                                             .trim();
        
        // getting the location of these two shapes
        int[] traverseStartPoint = hash( patternMinCharacters );
        int[] traverseEndPoint = hash( patternMaxCharacters );

        boolean containsStar = pattern.getCharacters().contains( "*" );
        boolean startsWithSymbol = pattern.getCharacters().startsWith("*") ||
                                   pattern.getCharacters().startsWith("?");

        if ( !containsStar )
            {
                // defining the traverse range in the main HashTable
                range[ 0 ][ 0 ] = traverseStartPoint[ 0 ];
                range[ 0 ][ 1 ] = traverseEndPoint[ 0 ];

                // defining the traverse range in the secondary HashTable
                range[ 1 ][ 0 ] = traverseStartPoint[ 1 ];
                range[ 1 ][ 1 ] = traverseEndPoint[ 1 ];
            }
        else
            {
                if ( !startsWithSymbol )
                    {
                        // defining the traverse range in the main HashTable
                        range[ 0 ][ 0 ] = traverseStartPoint[ 0 ];
                        range[ 0 ][ 1 ] = data.size() - 1;
        
                        // defining the traverse range in the secondary HashTable
                        range[ 1 ][ 0 ] = traverseStartPoint[ 1 ];
                        range[ 1 ][ 1 ] = MAX_WORD_LENGTH - 1;
                    }
                else
                    {
                        // defining the traverse range in the main HashTable
                        range[ 0 ][ 0 ] = 0;
                        range[ 0 ][ 1 ] = data.size() - 1;

                        // defining the traverse range in the secondary HashTable
                        range[ 1 ][ 0 ] = traverseStartPoint[ 1 ];
                        range[ 1 ][ 1 ] = MAX_WORD_LENGTH - 1;
                    }
            }

        return range;
    }
}