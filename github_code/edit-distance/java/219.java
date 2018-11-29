import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Levenshtein {

    String word;

    public Levenshtein(String word1){
        this.word = word1;
    }

    public int levenshteinDistance(String word2) {

        int distance[][] = new int[word.length() + 1][word2.length() + 1];
        // i et j itèrent sur word1 et word2
        int i,j;
        int edit; //coût de substitution
        //initialisation de la distance

        for (i=0 ; i<=word.length();i++){
            distance[i][0] = i;
        }
        for (j=0 ; j<=word2.length();j++){
            distance[0][j] = j;
        }

        for(i=1;i<=word.length();i++){
            for (j=1;j<=word2.length();j++){

                int db = distance[i-1][j-1]; // diagonal box
                int lb = distance[i][j-1]; // left box
                int tb = distance[i-1][j]; // top box

                if(word.charAt(i-1)==word2.charAt(j-1)){
                    edit =0;
                }
                else {
                    edit = 1;
                }

                distance[i][j] = Math.min(db + edit,Math.min(lb+1,tb+1));
            }
        }

        return distance[distance.length-1][distance[0].length -1];
    }

    /**
     * Calcule la distance de chaque mot d'une liste par rapport à word1 et sélectionner les n meilleurs
     * @param wordsList liste des mots à comparer
     * @param n nombre de mots à retourner
     * @return la liste des mots associés à leur distance par rapport à word1
     */
    public List<String> bestWords(List<String> wordsList,int n){

        Map<String,Integer> bestWordsMap = new HashMap<>();

        for (String element : wordsList){
            int d = levenshteinDistance(element);
            bestWordsMap.put(element,d);
        }

        Map<String,Integer> sortMap = MapTools.sortByValueAscending(bestWordsMap);
        //MapTools.printMap(sortMap);
        List<String> bestWords = new ArrayList<>();
        for (Map.Entry<String,Integer> mapEntry : sortMap.entrySet()){
            if(bestWords.size()<n) bestWords.add(mapEntry.getKey());
            else break;
        }

        return bestWords;
    }
}
