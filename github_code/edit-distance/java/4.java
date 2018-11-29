/**
 * File Name:   Edit_distance.java
 * Description: The normal edit distance algorithm
 * Author:      Hengfeng Li
 */
import java.io.*;
import java.util.HashSet;
import java.util.Iterator;

public class Edit_distance {

    /**
     * The normal edit distance algorithm with deletion +1,
     * insertion + 1, mismatch +1, match 0.
     */
    public static int edit3(String string1, String string2){
        int length1, length2;
        length1 = string1.length();
        length2 = string2.length();

        int F[][] = new int[length1+1][length2+1];

        for(int i = 0; i <= length1; i++) {
            F[i][0] = i;
        }
        for(int i = 0; i <= length2; i++) {
            F[0][i] = i;
        }

        for(int i = 1; i <= length1; i++) {
            for(int j = 1; j <= length2; j++) {
                F[i][j] = min3(F[i-1][j] + 1,
                        F[i][j-1] + 1,
                        F[i-1][j-1] + equal(string1.charAt(i-1),string2.charAt(j-1)));
            }
        }
        return  F[length1][length2];
    }

    /** Get the minimum in three numbers */
    public static int min3(int a, int b, int c) {
        if( a > b )
            return (( c > b) ? b : c);
        else
            return (( c > a) ? a : c);
    }

    private static int equal(char char1, char char2) {
        return (( char1 == char2) ? 0 : 1);
    }

    /** Search a word by computing the number of edit distance */
    public static TopQueue search(String target, String dictFile) throws IOException {
        BufferedReader reader;
        reader = new BufferedReader(new FileReader(dictFile));

        TopQueue topQueue = new TopQueue();
        String word;

        int distance;

        while((word = reader.readLine()) != null)
        {
            // get the number of edit distance
            distance = Edit_distance.edit3(target,word);

            if(!topQueue.isEmpty()){
                if(distance < topQueue.getEntryDistance()){
                    topQueue.add(word,distance);
                }
            } else {
                topQueue.add(word,distance);
            }
        }
        return topQueue;
    }

    /** Output the alternatives according to the wrong words */
    public static void outputAlternatives(HashSet<String> wrongWords,
                    String outputFile, String dictFile, Trie trie) throws IOException {

        PrintWriter writer;
        writer = new PrintWriter(new FileOutputStream(outputFile));

        TopQueue topQueue;
        TopNode topNode;

        double probability;
        int wordFrequency;

        String word;

        for (Iterator<String> iter = wrongWords.iterator();iter.hasNext();) {
            // get a wrong word
            word = iter.next();

            writer.println(word);

            // search the alternatives by using the approximate techniques
            topQueue = search(word, dictFile);

            // get the best match
            topNode = topQueue.getTopOne();

            // get the frequency of the best match
            wordFrequency = trie.search(topNode.getWord()).getFrequency();

            // compute how probably this best match could be a correction to the query
            probability = Selection.isNewWord(topNode.getDistance(), wordFrequency);

            if(probability < Selection.thresholdED) {
                // if the probability less than a threshold,
                // then it may be a new word.
                writer.print("This is a new word.");
                writer.println();
            }
            else {
                topQueue.print(writer);
            }
        }

        writer.flush();
        writer.close();
    }

    public static void main(String[] args) throws Exception{
        String dictFile = "words.txt";
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String line;
        TopQueue topQueue;

        if(args.length == 1) {
            dictFile = args[0];
        }
        else if(args.length == 0) {
            System.out.println("The system will using the default setting.");
            System.out.println("java Edit_distance words.txt");
        }
        else {
            System.out.println("usage: java Edit_distance [dictionary]");
            return;
        }

        while((line = reader.readLine()) != null){
            System.out.println("edit3:");
            long startTime = System.currentTimeMillis();
            topQueue = search(line, dictFile);
            topQueue.print();
            long consumingTime = System.currentTimeMillis() - startTime;
            System.out.println(consumingTime + " ms");
        }
    }
}
