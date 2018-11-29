package com.example.swathi.gameboggle;


import java.util.ArrayList;

import android.app.Activity;
import android.content.Context;
import android.util.Log;
import android.widget.Toast;
import java.util.ArrayList;



public class ValidWords {
    //
    private int difficulty;
    private ArrayList<WordNode> validList[];

    //These variables are used in finding the list of valid words
    private String tempBoard[][];
    private boolean visited[][];
    private int total;
    private int maxLength;//This variable is used to limit words to a specified length.  not meant for final version

    //Dictionary
    private Dictionary dictionary;


    //default constructor, assumed it won't be used
    public ValidWords() {
        total = 0;
        difficulty = 0;
        maxLength = 16;
        dictionary = null;
    }


    // Initializes ValidWords for a specific board
    public ValidWords(ArrayList<String> squares, int difficulty, Dictionary dictionary) {
        tempBoard = new String[4][4];
        visited = new boolean[4][4];
        this.difficulty = difficulty;
        //Board is i = 0 ... 3 horizontally, j = 0 ... 3 from top to bottom.  [0][0] is top left, [3][0] is top right
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                visited[i][j] = false;
                tempBoard[i][j] = squares.get(i + (j * 4));
            }
        }
        total = 0;
        maxLength = 16;
        validList = (ArrayList<WordNode>[]) new ArrayList[26];
        for (int j = 0; j < 26; j++) {
            validList[j] = new ArrayList<WordNode>();
        }

        this.dictionary = dictionary;
        this.findAllWords();
    }

    // compares the number of words to the difficulty
    public boolean checkValidBoard() {
        switch (difficulty) {
            case 1:             //easy
                if (total < 2)
                    return false;
                break;
            case 2:             //normal
                if (total < 5)
                    return false;
                break;
            case 3:             //difficult
                if (total < 7)
                    return false;
                break;
            default:
                return false;
        }
        return true;
    }

    //Finds all the words on the board using a depth-first-search
    private void findAllWords() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                //findWords(tempBoard[i][j], i, j, 1);
                findWords("", i, j, 0);
            }
        }
    }

    //performs the actually depth-first-search for the findAllWords() function
    private void findWords(String oldString, int x, int y, int oldWordLength) {
        //This check will be removed once checkPrefix exists.  without checkPrefix checking the board will take too long so this statement limits it
        if (oldWordLength + 1 > maxLength)
            return;
        //First check to make sure the recursive function is safe to call
        //checks that the function is searching within the bounds of the board
        if (x > 3 || x < 0 || y > 3 || y < 0)
            return;
        //Makes sure the square hasn't been checked already
        if (visited[x][y])
            return;

        //Create a new string and do the next step in the depth-first-search
        String newString = oldString.concat(tempBoard[x][y]);


        //This line will increase the speed by a lot
        //without this line then, for example, the algorithm will check all possible strings that start with azq, even though no real words start with that (I think)
        if (!dictionary.isPrefix(newString))
            return;

        visited[x][y] = true;

        for (int i = -1; i < 2; i++) {
            for (int j = -1; j < 2; j++) {
                findWords(newString, x + i, y + j, oldWordLength + 1);
            }
        }

        //At this point the program is on the way back from the depth-first-search, so now check that the current word is ok.

        if (oldWordLength > 1) {
            if (dictionary.isWord(newString)) {
                if (addValidWord(newString))
                    total++;
            }
        }


        //TESTING CODE: adds all strings without checking with dictionary
        //if newString is 3 letters long then wordLength will equal 2
        /*
        if (oldWordLength > 1)
        {
            addValidWord(newString);
            total++;
        }
        */

        visited[x][y] = false;

        return;
    }

    // Words can be valid, invalid, and already found.  wordNode will simply contain a word
    //   string and a boolean found for tracking this
    private class WordNode {
        private String word;
        private boolean found;

        public WordNode(String word) {
            this.word = word;
            found = false;
        }

        public String getWord() {
            return word;
        }

        public boolean isFound() {
            return found;
        }

        public void markFound() {
            found = true;
        }
    }

    //This function will add a word to the data structure (unless it is already in there)
    private boolean addValidWord(String aWord) {
        if (aWord.length() < 1)
            return false;
        char firstLetter = aWord.charAt(0);
        //index will be 0 if char == A, 1 if char == B and so on
        int index = firstLetter - 97;
        WordNode temp = null;

        //This loop checks all words that start with firstLetter to see if the word already exists
        for (int i = 0; i < validList[index].size(); i++) {
            if (validList[index].get(i).getWord().equals(aWord)) {
                return false;
            }
        }

        temp = new WordNode(aWord);
        validList[firstLetter - 97].add(temp);

        return true;
    }

    //return 0 for not found, 1 for found and already used, 2 for found and not already found
    //return -1 if aWord.length() < 3
    public int checkWord(String aWord) {
        if (aWord.length() < 3) {
            return -1;
        }

        char firstLetter = aWord.charAt(0);
        int index = firstLetter - 97;
        WordNode temp = null;

        for (int i = 0; i < validList[index].size(); i++) {
            temp = validList[index].get(i);
            if (temp.getWord().equals(aWord)) {
                if (temp.isFound())
                    return 1;
                temp.markFound();
                i = validList[index].size();
                return 2;
            }
        }
        return 0;
    }

    // Words were initially stored in WordNodes,
    //   must retrieve String from the WordNodes and return them all in an ArrayList
    public ArrayList<String> getValidWords() {
        ArrayList<String> temp = new ArrayList<String>();

        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < validList[i].size(); j++) {
                temp.add(validList[i].get(j).getWord());
            }
        }

        return temp;
    }


    // Returns the words found by the player
    public ArrayList<String> getFoundWords() {
        ArrayList<String> temp = new ArrayList<String>();

        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < validList[i].size(); j++) {
                if (validList[i].get(j).isFound())
                    temp.add(validList[i].get(j).getWord());
            }
        }

        return temp;
    }


}