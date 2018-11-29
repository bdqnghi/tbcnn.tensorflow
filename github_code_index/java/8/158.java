package levenshtein_distance;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Scanner;



public class Levenshtein_Distance {

	public static List<String> words = new ArrayList<String>(); 
	
	public static boolean is_friend(String s1, String s2)
	{
		if (s1==s2) return false; 
		if ((s1.length() == 1) && (s2.length()==1)) return true;
		if (((s1.length()==1) && (s2.length()==0)) || ((s1.length()==0) && (s2.length()==1))) return true;
		
		int[] row = new int[s2.length()+1]; //input list
		int[] col = new int[s2.length()+1]; //output list
		
		for (int i =0;i<row.length;i++)
		{
			row[i]=i; //initialize input list
		}
		
		for (int i = 0; i<s1.length(); i++)
		{
			col[0]=i+1;
			
			for (int j = 0; j<s2.length(); j++) //compare each letter of second word to the current letter
			{
				int same;
				if (s1.charAt(i)==s2.charAt(j)) { same = 0;}
				else {same = 1;}
				
				int tMin = Math.min(col[j]+1, row[j+1]+1);
				col[j+1] = Math.min(tMin, row[j]+same); 
			}

			for (int k=0; k<row.length; k++)
			{
				row[k]=col[k];	//update 		
			}
		}
					
		return (col[s2.length()] == 1);	
	}
		
	public static void fileToList() throws IOException
	{
		
		BufferedReader reader = new BufferedReader
				(new FileReader("src/levenshtein_distance/randomlist.txt"));
		String word = null;
		while ((word = reader.readLine()) != null) {
			words.add(word); //add words to arraylist
		}
		reader.close();
			
	}
	
	public static List<String> list_friends(String s)
	{
		ArrayList<String> friends = new ArrayList<String>(); 
		for (int i=0; i<words.size(); i++)
		{
			String w1 = words.get(i);
					
			if (is_friend(s, w1)) //test if its a friend
			{
				friends.add(w1);
			}
		}
		
		return friends;
	}
	
	public static List<String> friendsV2(List<String> friends, String s)
	{
		ArrayList<String> friends2 = new ArrayList<String>();
		if (friends.isEmpty()) return friends2;
		for (int i=0; i<friends.size(); i++)
		{
			List<String> f = list_friends(friends.get(i));
			friends2.addAll(f); //add to single array list
		}
		//remove all occurrences of the original word.
		friends2.removeAll(Collections.singleton(s)); 
		
		return friends2;
	}
	
	
				
		
	
	
		


	public static void main(String[] args) 
	{
		try {
			fileToList();
			Scanner user = new Scanner (System.in);
		
			String word;
			System.out.println("Enter Word");
			word = user.next();
			
			while (!(words.contains(word)))
			{
				System.out.println("Not in list");
				System.out.println("Enter Word");
				word = user.next();
			} 
			
			List<String> f = list_friends(word);
			System.out.println("Friends: " + f);
			List<String> f2 = friendsV2(f,word);
			System.out.println("Friends of friends: "+ f2);
			List<String> f3 = friendsV2(f2,word);
			System.out.println("Friends of friends of friends:" +f3);
			
			user.close();
		} catch (IOException e) {
			e.printStackTrace();
		}

	}


}
