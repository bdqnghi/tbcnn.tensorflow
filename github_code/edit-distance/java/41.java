package org.odk.voice.digits2string;

/**
 * See http://en.wikipedia.org/wiki/Levenshtein_distance
 * @author alerer
 *
 */
public class LevenshteinDistanceCalculator {
  
  int[][] calcArray;
  
  public LevenshteinDistanceCalculator(int maxSize){
    calcArray = new int[maxSize + 1][maxSize + 1];
  }
  
  public int getDistance(String a, String b){
      for (int i = 0; i <= a.length(); i++) {
        calcArray[i][0] = i;
      }
      for (int j = 0; j <= b.length(); j++) {
        calcArray[0][j] = j;
      }
      for (int j = 0; j < b.length(); j++) {
        for (int i = 0; i < a.length(); i++) {
          if (a.charAt(i) == b.charAt(j)){
            calcArray[i+1][j+1] = calcArray[i][j];
          } else {
            calcArray[i+1][j+1] = min3(calcArray[i][j+1],
                                       calcArray[i+1][j],
                                       calcArray[i][j])
                                       + 1;
          }
        }
      }
      return calcArray[a.length()][b.length()];
      
//      int LevenshteinDistance(char s[1..m], char t[1..n])
//      {
//        // d is a table with m+1 rows and n+1 columns
//        declare int d[0..m, 0..n]
//      for i from 0 to m
//        d[i, 0] := i // deletion
//      for j from 0 to n
//        d[0, j] := j // insertion
//     
//      for j from 1 to n
//      {
//        for i from 1 to m
//        {
//          if s[i] = t[j] then 
//            d[i, j] := d[i-1, j-1]
//          else
//            d[i, j] := minimum
//                       (
//                         d[i-1, j] + 1,  // deletion
//                         d[i, j-1] + 1,  // insertion
//                         d[i-1, j-1] + 1 // substitution
//                       )
//        }
//      }
//     
//      return d[m, n]
//    }

  }
  
  public int min3(int a, int b, int c) {
    return Math.min(a, Math.min(b, c));
  }
}
