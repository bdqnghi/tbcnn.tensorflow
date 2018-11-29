package ch.ingredientmatching.lexer;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

import org.apache.log4j.Logger;

import ch.ingredientmatching.setup.Config;

import de.abelssoft.wordtools.jwordsplitter.AbstractWordSplitter;
import de.abelssoft.wordtools.jwordsplitter.impl.GermanWordSplitter;
import org.apache.lucene.queryparser.classic.ParseException;

/**
 * the lexer converts the inputString to smaller substrings (InputWords),
 * normalizes the strings and searches them in the graph & eaternity index. it
 * also assigns levenshtein distance and weights depending on where the
 * substring occured in the original string, the length and if it was in
 * parantheses etc.
 * 
 * @author nicu
 * 
 */
public class Lexer {
	static Logger log = Logger.getLogger(Lexer.class);

	private static AbstractWordSplitter splitter;
	private Index index;

	public Lexer() throws IOException {
		// set to true if it should only split if both word parts are valid words
		splitter = new GermanWordSplitter(false);
		//with a external dictionary exceptions could be added etc, but it is a LOT slower, like a LOT!!!
//		splitter = new GermanWordSplitter(false, Config.WORD_PART_DICT_PATH);
		index = new Index();
	}

	/**
	 * controls all needed steps from the original input to the found index
	 * 
	 * @param string
	 * @throws IOException
	 */
	public List<LexWord> runLexer(String string) throws IOException, ParseException {
		List<LexWord> words = new ArrayList<LexWord>();
		decomposeString(string, words);
		decomposeIntoWordParts(words);
		searchIndex(words);
		return words;
	}

	/**
	 * uses the Index class to search in the eaternity and the graph index,
	 * finds and sets the best match (case sensitive) from each. calculates corresponding
	 * levenshtein-distance (not case sensitive)
	 * 
	 * @throws IOException
	 * @param words
	 */
	private void searchIndex(List<LexWord> words) throws IOException, ParseException {
		log.info("searchIndex");
		String indexResult;
		int indexDistance;
		int id;
		for (LexWord word : words) {
			log.debug("lexWord in loop: <" + word.getInputString() + ">");
			String input = word.getInputString();

			// search in eaternity index
			indexResult = "";
			id = Config.ID_ERROR_CODE;
			indexResult = findBestIndexResult(
					index.searchEaternityIndex(input), input);
			if(!indexResult.isEmpty()){
				log.debug("found result with n-gram-index");
				//not case sensitive
				indexDistance = LevenshteinDistance.getLevenshteinDistance(input,
						indexResult, false);
				//search the id
				id = index.getEaternityIndexId(indexResult);
				word.setEaternityIndexId(id);
				word.setEaternityIndex(indexResult);
				word.setLevenshteinEaternity(indexDistance);
			}else{
				log.debug("search index with spellchecker");
				//try the spellchecker
				indexResult = findBestIndexResult(index.searchSpellCheckerEaternityIndex(input), input);
				if(!indexResult.isEmpty()){
					indexDistance = LevenshteinDistance.getLevenshteinDistance(input,
							indexResult, false);
					// search the id
					id = index.getEaternityIndexId(indexResult);
					word.setEaternityIndexId(id);
					word.setEaternityIndex(indexResult);
					word.setLevenshteinEaternity(indexDistance);
				}
			}
		}

	}
	


	/**
	 * finds the best match between all strings in the list and the string
	 * stored in the InputWord. it then sets the best hit, calculates and sets
	 * the levenshtein-distance (case sensitive)
	 * 
	 * @param results
	 * @param input
	 */
	public static String findBestIndexResult(List<String> results, String input) {
		log.info("findBestIndexResult");
		String tempResult = "";
		int tempDistance = Integer.MAX_VALUE;
		int minDistance = Integer.MAX_VALUE;
		if (!results.isEmpty()) {
			for (String result : results) {
				tempDistance = LevenshteinDistance.getLevenshteinDistance(
						input, result, true);
				if (tempDistance < minDistance) {
					minDistance = tempDistance;
					tempResult = result;
				}
			}
		}
		log.debug("findBestIndexResult result: <" + tempResult +">");
		return tempResult;
	}

	/**
	 * takes the original input and fills the list of InputWords with  the whole
	 * input, everything before a comma, everything before parentheses and also
	 * everything separated by white spaces
	 *
	 * @param inputString
	 * @param words
	 */
	private void decomposeString(String inputString, List<LexWord> words) {
		log.info("decomposeString");
		log.debug("input is splitted in substrings: ");
		//eliminate duplicate whitespaces
		inputString = inputString.replaceAll("\\s+", " ");
		//full input
		String fullWord = eliminateSpecialChars(eliminatePunctuationMarks(inputString).trim());
		LexWord fullInputWord = new LexWord(fullWord);
		fullInputWord.setPossitionInInputString(0);
		if(fullWord.contains(" ")){
			fullInputWord.setSingleWord(false);
			words.add(fullInputWord);
			log.debug("added full input: <"+fullWord+">");
		}
		
		//before comma
		String bfCTemp = inputString.split("\\,")[0].trim();
		// if has no white space, or equals the original input, then it will become a duplicate
		if(bfCTemp.contains(" ") && !bfCTemp.equals(inputString)){
			LexWord commaWord = new LexWord(bfCTemp);
			commaWord.setSingleWord(false);
			commaWord.setPossitionInInputString(0);
			words.add(commaWord);
			log.debug("added commaWord: <" + commaWord.getInputString() +">");
		}
		
		//before parentheses
		String bfPTemp = inputString.split("\\(")[0].trim();
			// if has no white space, then it will become a duplicate
			if(bfPTemp.contains(" ") && !bfPTemp.equals(bfCTemp) && !bfPTemp.equals(inputString)){
				LexWord parenthesisWord = new LexWord(bfPTemp);
				parenthesisWord.setSingleWord(false);
				parenthesisWord.setPossitionInInputString(0);
				words.add(parenthesisWord);
				log.debug("added parenthesisWord: <" + parenthesisWord + ">");
			}
			
		//before numbers
			String bfNTemp = inputString.split("[0-9]")[0].trim();
			// if has no white space, then it will become a duplicate
			if(bfNTemp.contains(" ") && !bfNTemp.equals(bfCTemp) && !bfNTemp.equals(bfPTemp) && !bfNTemp.equals(fullWord)){
				LexWord numberWord = new LexWord(bfNTemp);
				numberWord.setSingleWord(false);
				numberWord.setPossitionInInputString(0);
				words.add(numberWord);
				log.debug("added numberWord: <" + numberWord + ">");
			}
			
			

		boolean insideParentheses = false;
		boolean afterComma = false;
		char c;
		inputString = normalizeString(inputString);

		// add a whitespace at the end of the string, otherwise last word is not
		// processed
		inputString = inputString + " ";

		// decomposes string at white spaces, "," and parentheses and creates
		// InputWords which are added to <words>
		int stringLength = inputString.length();
		int position = 0;
		
		//has initially to be empty
		String temp = "";
		for (int i = 0; i < stringLength; i++) {
			c = inputString.charAt(i);
			if (c == '(') {
				insideParentheses = true;
			} else if (c == ')') {
				insideParentheses = false;
			} else if (c == ',') {
				afterComma = true;
			} else if (c == ' ') {
				if (temp.length() > 0) {
					log.debug("splitted: <"+temp+">");
					//apply blackList
					if(!InputBlackList.blackList.contains(temp)){
						LexWord inputWord = new LexWord(
								eliminatePunctuationMarks(temp));
						inputWord.setAfterComma(afterComma);
						inputWord.setInsideParentheses(insideParentheses);
						inputWord.setPossitionInInputString(position);
						inputWord.setSingleWord(true);
						words.add(inputWord);
						log.debug("added splittedWord : <" + temp + ">");
						position++;
					}else{
						log.debug("didn't add splittedWord: <" + temp + "> because it's in the BlackList");
					}
				}
				temp = "";
			} else {
				temp = temp + c;
			}
		}
	}

	/**
	 * tries to decompose words into is parts (e.g. "butterbrot" into "butter"
	 * and "brot"). GermanWordSplitter is a rule based WordSplitter
	 * @param words
	 */
	private void decomposeIntoWordParts(List<LexWord> words) {
		log.info("decomposeIntoWordParts");

		Collection<String> parts;
		int wordsSize = words.size();
		for (int i = 0; i < wordsSize; i++) {
			// only perform it if there are no white spaces or it will confuse
			// the GermanWordSplitter
			if (!words.get(i).getInputString().contains(" ")) {
				parts = splitter.splitWord(words.get(i).getInputString());
				if (parts.size() > 1) {
					for (String part : parts) {
						part = part.trim();
						//single characters or very short strings are probably not intended
						if(part.length()>2){
							LexWord wordPart = new LexWord(part);
							wordPart.setAfterComma(words.get(i).isAfterComma());
							wordPart.setInsideParentheses(words.get(i)
									.isInsideParentheses());
							wordPart.setWordPart(true);
							wordPart.setPossitionInInputString(words.get(i)
									.getPossitionInInputString());
							wordPart.setSingleWord(true);
							words.add(wordPart);
							log.debug("added wordPart " + part);
						}
					}
				}
			}
		}

	}


	/**
	 * for parentheses and coma is needed if a string is written like:
	 * "something(whatever)", adds white spaces after these special characters
	 * 
	 * @param string
	 * @return
	 */
	private String normalizeString(String string) {
		// add whitespaces
		string = string.replace("(", " ( ");
		string = string.replace(")", " ) ");
		string = string.replace(",", " , ");
		string = string.replace("-", " ");
		string = string.replace("//", " ");
		
		string = string.replaceAll("[0-9]","");


		return string;
	}

	/**
	 * removes parentheses, special chars etc.
	 * 
	 * @return
	 */
	private String eliminatePunctuationMarks(String string) {
		string = string.replace("(", " ");
		string = string.replace(")", " ");
		string = string.replace(",", " ");
		string = string.replace("/", " ");
		string = string.replaceAll("\\s+", " ");
		string = string.replace("-", " ");
		


		return string;
	}
	
	public static String eliminateSpecialChars(String string){
		string = string.replace("ä", "a");
		string = string.replace("ü", "u");
		string = string.replace("ö", "o");
		string = string.replace("é", "e");
		string = string.replace("à", "a");
		string = string.replace("è", "e");
		string = string.replace("oe", "o");
		string = string.replace("ue", "u");
		string = string.replace("ae", "a");
		string = string.replace("ß", "");
		string = string.replaceAll("[0-9]","");
		return string;
	}

}
