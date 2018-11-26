package queryengine;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Map.Entry;
import java.util.NavigableMap;
import java.util.TreeMap;

import queryengine.QueryProcessor.MalformedExpressionException;
import queryengine.QueryProcessor.UserQuitException;
import structure.ApplicationContext;

public class TolerantQuery extends AbstractQuery
{

	@Override
	public ArrayList<Integer> doQuery(String input) throws UserQuitException, MalformedExpressionException
	{
		String[] splitedQuery = input.split("\\*");
		NavigableMap<String, ArrayList<Integer>> result;
		String queryNormalized;
		if (input.endsWith("*"))
		{
			queryNormalized = normalizeToken(splitedQuery[0]);
			result = tail(queryNormalized);
			printTolerantWords(result);
		}
		else if (input.startsWith("*"))
		{
			queryNormalized = normalizeToken(splitedQuery[1]);
			NavigableMap<String, ArrayList<Integer>> reverseResult = head(queryNormalized, null);
			result = unreverseMap(reverseResult);
			printTolerantWords(result);
		}
		else
		{
			NavigableMap<String, ArrayList<Integer>> reverseResult = middle(splitedQuery);
			result = unreverseMap(reverseResult);
			printTolerantWords(result);
		}
		return joinResult(result);
	}
	
	private NavigableMap<String, ArrayList<Integer>> tail(String fromKey)
	{
		char lastChar = fromKey.charAt(fromKey.length() - 1);
		char nextChar = (char)(lastChar + 1);
		String toKey = fromKey.substring(0, fromKey.length() - 1);
		toKey = toKey + nextChar;
		
		NavigableMap<String, ArrayList<Integer>> subMap = ApplicationContext.getInvertedIndex()
				.getSubMap(fromKey, true, toKey, false);
		
		return subMap;
	}
	
	private NavigableMap<String, ArrayList<Integer>> head(String fromKey,
			TreeMap<String, ArrayList<Integer>> reverseMap)
	{
		String reverseKey = new StringBuilder(fromKey).reverse().toString();
		
		char lastChar = reverseKey.charAt(reverseKey.length() - 1);
		char nextChar = (char)(lastChar + 1);
		String toKey = reverseKey.substring(0, reverseKey.length() - 1);
		toKey = toKey + nextChar;
		
		NavigableMap<String, ArrayList<Integer>> subMap;
		if (reverseMap == null)
			subMap = ApplicationContext.getReverseInvertedIndex()
				.getSubMap(reverseKey, true, toKey, false);
		else
			subMap = reverseMap.subMap(reverseKey, true, toKey, false);
		
		return subMap;
	}
	
	private NavigableMap<String, ArrayList<Integer>> middle(String[] splitedQuery)
	{
		//processa a primeira parte da query
		String firstPartQuery = normalizeToken(splitedQuery[0]);
		NavigableMap<String, ArrayList<Integer>> tailMap = tail(firstPartQuery);
		//inverte as chaves do resultado anterior
		TreeMap<String, ArrayList<Integer>> reverseMap = new TreeMap<String, ArrayList<Integer>>();
		for (Entry<String, ArrayList<Integer>> entry : tailMap.entrySet())
		{
			String key = entry.getKey();
			ArrayList<Integer> value = entry.getValue();
			String reverse = new StringBuilder(key).reverse().toString();
			reverseMap.put(reverse, value);
		}
		//processa a segunda parte da query no resultado revertido
		String secondPartQuery = normalizeToken(splitedQuery[1]);
		NavigableMap<String, ArrayList<Integer>> reverseResultMap = head(secondPartQuery, reverseMap);
		return reverseResultMap;
	}
	
	private TreeMap<String, ArrayList<Integer>> unreverseMap(NavigableMap<String, ArrayList<Integer>> reverseMap)
	{
		TreeMap<String, ArrayList<Integer>> resultMap = new TreeMap<String, ArrayList<Integer>>();
		for (Entry<String, ArrayList<Integer>> entry : reverseMap.entrySet())
		{
			String key = entry.getKey();
			ArrayList<Integer> value = entry.getValue();
			String reverse = new StringBuilder(key).reverse().toString();
			resultMap.put(reverse, value);
		}
		return resultMap;
	}
	
	private ArrayList<Integer> joinResult(NavigableMap<String, ArrayList<Integer>> result)
	{
		ArrayList<Integer> listOfDocs = new ArrayList<Integer>();
		for (Entry<String, ArrayList<Integer>> entry : result.entrySet())
		{
			for (Integer i : entry.getValue())
			{
				if (!listOfDocs.contains(i))
					listOfDocs.add(i);
			}
		}
		Collections.sort(listOfDocs);
		return listOfDocs;
	}
	
	private void printTolerantWords(NavigableMap<String, ArrayList<Integer>> map)
	{
		System.out.println("\nTermos que respondem à busca tolerante:");
		for (Entry<String, ArrayList<Integer>> entry : map.entrySet())
		{
			System.out.println(entry.getKey() + " = " + entry.getValue().toString());
		}
	}

}
