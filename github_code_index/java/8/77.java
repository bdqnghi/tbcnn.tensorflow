package distance;
import java.lang.Math;
import java.util.ArrayList;
import java.util.List;

public class Levenshtein {
	
	List<Word> dictionary = new ArrayList<Word>();
	
	public static void main(String[] args) {
		new Levenshtein().run();
		
	}
	
	public void run() {
		readDictionary();
		findNeighbors();
		runTests();
	}
	
	private void runTests() {
		calculateDistance(dictionary.get(0), dictionary.get(1), 1);
		calculateDistance(dictionary.get(0), dictionary.get(2), 2);
		calculateDistance(dictionary.get(1), dictionary.get(2), 1);
		calculateDistance(dictionary.get(0), dictionary.get(3), 3);
	}

	private void calculateDistance(Word word, Word word2, int expected) {
		int distance = word.distance(word2);
		System.out.println(word + ", " + word2 + ", distance: " + distance + " expected: " + expected);
	}

	public void readDictionary() {
		dictionary.add(new Word("cat"));
		dictionary.add(new Word("cot"));
		dictionary.add(new Word("dot"));
		dictionary.add(new Word("dog"));
	}

	public void findNeighbors() {
		for(int i = 0; i < dictionary.size(); i++)
			for(int j = i + 1; j < dictionary.size(); j++)
				if(dictionary.get(i).isNeighbor(dictionary.get(j))) {
					dictionary.get(i).addNeighbor(dictionary.get(j));
					dictionary.get(j).addNeighbor(dictionary.get(i));
				}
	}
}
