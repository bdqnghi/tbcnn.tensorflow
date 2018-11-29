// Given a set of characters represented by a String, return a list containing all subsets of the characters.
//
// Assumptions
// There could be duplicate characters in the original set.
//
// Examples
// Set = "abc", all the subsets are ["", "a", "ab", "abc", "ac", "b", "bc", "c"]
// Set = "abb", all the subsets are ["", "a", "ab", "abb", "b", "bb"]
// Set = "", all the subsets are [""]
// Set = null, all the subsets are []

/*
 * Method 1
 */
/*
public class Solution {
  public List<String> subSets(String set) {
    List<String> result = new ArrayList<String>();
    // Corner check
    if (set == null) {
      return result;
    }
    // Depth-First-Search
    char[] array = set.toCharArray();
    Arrays.sort(array);
    StringBuilder sb = new StringBuilder();
    DFS(array, result, 0, sb);
    return result;
  }
  
  private void DFS(char[] array, List<String> result, int index, StringBuilder sb) {
    // Base case
    if (index == array.length) {
      result.add(sb.toString());
      return;
    }
    // Recursion rule
    DFS(array, result, index + 1, sb.append(array[index]));
    sb.deleteCharAt(sb.length() - 1);
    // Skip all the consecutive and duplicate elements.
    while (index < array.length - 1 && array[index] == array[index + 1]) {
      index++;
    }
    DFS(array, result, index + 1, sb);
  }
}
*/

/*
 * Method 2
 */
public class Solution {
  public List<String> subSets(String set) {
    List<String> result = new ArrayList<>();
    // Corner check
    if (set == null) {
      return result;
    }
    // Depth-First-Search
    char[] array = set.toCharArray();
    Arrays.sort(array);
    StringBuilder sb = new StringBuilder();
    DFS(array, result, 0, sb);
    return result;
  }
  
  private void DFS(char[] array, List<String> result, int index, StringBuilder sb) {
    // Base case
    result.add(sb.toString());
    // Recursion rule
    for (int i = index; i < array.length; i++) {
      if (i == index || array[i] != array[i - 1]) {
        sb.append(array[i]);
        DFS(array, result, i + 1, sb);
        sb.deleteCharAt(sb.length() - 1);
      }
    }
  }
}
