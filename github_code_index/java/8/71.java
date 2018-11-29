package stringutils;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;
import java.util.List;

/**
 * Filters an iterator for all words a given edit distance away from a certain
 * word. Returns a list of all such words. Works best if iterator returns words
 * in alphabetical order.
 *
 * @author bbentz
 *
 */
public final class EditDistanceFilter {

  private EditDistanceFilter() {

  }

  /**
   * Filter an iterator for all words within maxDistance of baseWord.
   *
   * @param baseWord
   *          Word to measure distance from.
   * @param maxDistance
   *          Maximum allowed distance.
   * @param iterator
   *          Iterator supplying the words.
   * @return List of all of the words within the given distance.
   */
  public static List<String> filter(final String baseWord,
      final int maxDistance, final Iterator<String> iterator) {

    EditDistanceFilterInternal edfi = new EditDistanceFilterInternal(baseWord,
        maxDistance, iterator);
    return edfi.findWords();
  }

  /**
   * Internal class used to do the edit distance filter calculations.
   *
   * @author bbentz
   *
   */
  private static final class EditDistanceFilterInternal {

    private final List<List<Integer>> editDistanceArray;
    private final Iterator<String> iterator;
    private final String baseWord;
    private final int maxDistance;
    private final List<String> outputList;

    private String currentWord;

    /**
     * Private constructor for edit distance filter internal class.
     *
     * @param baseWord
     *          Word to compute edit distance against.
     * @param maxDistance
     *          Maximum distance words can be from baseWord.
     * @param iterator
     *          Source of words.
     */
    private EditDistanceFilterInternal(final String baseWord,
        final int maxDistance, final Iterator<String> iterator) {
      this.baseWord = baseWord;
      this.maxDistance = maxDistance;
      this.iterator = iterator;

      outputList = new ArrayList<>();
      editDistanceArray = new ArrayList<>();

      List<Integer> firstList = new ArrayList<>();
      for (int i = 0; i <= baseWord.length(); i++) {
        firstList.add(i);
      }

      editDistanceArray.add(firstList);
      currentWord = "";
    }

    /**
     * Returns the words within maxDistance of baseWords.
     *
     * @return The words within maxDistance of baseWords.
     */
    private List<String> findWords() {
      while (iterator.hasNext()) {
        processWord(iterator.next());
      }

      return outputList;
    }

    /**
     * Computes the edit distance to a word and adds it to the list of words
     * within maxDistance if applicable.
     *
     * @param str
     *          Word to compute edit distance to.
     */
    private void processWord(final String str) {

      // The editDistanceArray is correct up to the row returned by
      // editDistanceArray.get(editDistanceProgress);
      int editDistanceProgress = Math.min(editDistanceArray.size() - 1,
          StringUtils.sharedPrefixLength(str, currentWord));

      // Update current word
      currentWord = str;

      // Compute edit distance as far as necessary
      while (editDistanceProgress < currentWord.length()) {

        calculateEditDistanceRow(editDistanceProgress + 1);
        editDistanceProgress++;
      }

      if (editDistanceArray.get(currentWord.length())
          .get(baseWord.length()) <= maxDistance) {
        outputList.add(currentWord);
      }

    }

    /**
     * Calculates another row of the EditDistanceArray. Must be calculated up to
     * the previous rows or throws an exception.
     *
     * @param index
     *          The index of the row to calculate.
     */
    private void calculateEditDistanceRow(final int index) {
      if (editDistanceArray.size() < index) {
        throw new IllegalArgumentException(
            "ERROR: Called calculateEditDistanceRow on invalid index.");
      } else if (editDistanceArray.size() == index) {
        List<Integer> list = new ArrayList<>(
            Collections.nCopies(baseWord.length() + 1, 0));
        list.set(0, index);
        editDistanceArray.add(list);
      }

      List<Integer> previousList = editDistanceArray.get(index - 1);
      List<Integer> currentList = editDistanceArray.get(index);
      int i = index;
      int charsEqual;
      for (int j = 1; j <= baseWord.length(); j++) {
        charsEqual = baseWord.charAt(j - 1) == currentWord.charAt(i - 1) ? 0
            : 1;
        int value = Math.min(previousList.get(j) + 1, Math.min(
            currentList.get(j - 1) + 1, previousList.get(j - 1) + charsEqual));
        currentList.set(j, value);
      }

    }

    /*
     * public void debug() { StringJoiner sj = new StringJoiner("\n");
     * editDistanceArray.forEach(s -> sj.add(printList(s)));
     * System.out.println(sj.toString()); }
     *
     * public String printList(final List<Integer> list) { StringJoiner sj = new
     * StringJoiner(", ", "[", "]"); list.forEach(s ->
     * sj.add(Integer.toString(s))); return sj.toString(); }
     */

  }

}
