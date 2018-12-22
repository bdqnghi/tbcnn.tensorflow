package main.breadthfirstsearch;

import java.util.Arrays;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Set;
import java.util.function.Function;

/**
 * Given two words(start and end), and a dictionary, find the length of shortest transformation
 * sequence from start to end, such that:
 * 	Only one letter can be changed at a time
 *  Each intermediate word must exist in the dictionary
 *  
 *  example: 
 *  	start = "hit"
 *  	end = "cog"
 *  	dict=["hot", "dot", "dog", "lot", "log"]
 *  	As one shortest transformation is 
 *  	"hit"->"hot"->"dot"->"dog"->"cog", return its length 5
 *  
 *  Note: 
 *  	Return 0 if there is no such transformation
 *  	All words have the same length
 *  	All words contain only lowercase alphabetic characters
 *  
 *  Analysis:
 *  	Since the requirement is to find shortest path, 
 *  	We should use breadth-first-search
 *  	Time complexity O(n)
 *  	Space complexity O(n)
 *  	
 * @author yuchenyang
 *
 */
public class WordLadder
{
	public static void main(String[] args)
	{
		String beginWord = "hit";
		String endWord = "cog";
	    String[] elements = {"hot","dot","dog","lot","log"};
		Set<String> wordList = new HashSet<>(Arrays.asList(elements));
		
		System.out.println(ladderLength(beginWord, endWord, wordList));
	}
	
	public static int ladderLength(String beginWord, String endWord, Set<String> wordList)
	{
		Queue<State> q = new LinkedList();
		HashSet<State> visited =new HashSet();//used to determine state of the whole graph(wordList)
	
		//Functions used as criteiras
		final Function<State, Boolean> stateIsValid = (State s)->wordList.contains(s.word) || s.word.equals(endWord);
		final Function<State, Boolean> stateIsTarget = (State s)->s.word.equals(endWord);
		final Function<State, HashSet<State>> stateExtend = (State s)->{
			//one step of breadth search
			HashSet<State> result = new HashSet<>();
			
			char[] array = s.word.toCharArray();
			for(int i=0; i<array.length;i++)
			{
				final char old = array[i];
				
				/*
				 * brute force approach, try to modify one character of the string, 
				 * if it happens to match strings in dictionary, then add it into the result path
				 */
				for(char c = 'a'; c <= 'z'; c++)
				{
					//prevent replacing the same value
					if(c == array[i])
					{
						continue;
					}
					
					array[i] = c;//record the current value
					State newState = new State(new String(array), s.level+1);
					
					if(stateIsValid.apply(newState) && !visited.contains(newState))
					{
						result.add(newState);
					}
					array[i] = old;//restore
				}
			}
			return result;
		};
		
		//start breadth-first-search
		State startState = new State(beginWord, 0);
		q.offer(startState);//enqueue the current state
		visited.add(startState);//also mark the current state as visited
		while(!q.isEmpty())
		{
			State state = q.poll();//dequeue the first element of the queue

			//terminate condition
			if(stateIsTarget.apply(state))
			{
				return state.level + 1;
			}
			
			HashSet<State> newStates = stateExtend.apply(state);
			for(State newState: newStates)
			{
				q.offer(newState);
				visited.add(newState);
			}
				
		}
		return 0;
	}
	
	private static class State
	{
		String word;
		int level;
		
		/**
		 * 
		 * @param word, represent the current word(which is a sequence of chars)
		 * @param level, how many steps are needed to get from startWord to the currentWord
		 */
		public State(String word, int level)
		{
			this.word = word;
			this.level = level;
		}
		
		@Override
		public int hashCode()
		{
			return word.hashCode();
		}

		@Override
		public boolean equals(Object other)
		{
			if(this == other)
			{
				return true;
			}
			if(this.hashCode() != other.hashCode())
			{
				return false;
			}
			if(!(other instanceof State))
			{
				return false;
			}
			
			return this.word.equals(((State)other).word);
		}
	}
}
