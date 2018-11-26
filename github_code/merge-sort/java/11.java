import java.util.ArrayList;

public class MergeSorter {

    public static String mergeSortTime = "0 ms";
    public static int mergeSortComparisons = 0;
    private static Stopwatch _stopwatch = new Stopwatch();

    // called when button clicked
    public static void performMergeSort() {
        Thread thread = new Thread(() -> {
            mergeSortTime = "sorting...";
            _stopwatch.start();
            ArrayList<PhonebookEntry> mergeSorted = MergeSorter.mergeSort(Main.phonebook.getPhonebookEntries());
            _stopwatch.stop();
            mergeSortTime = SortTester.testAlphaSort(mergeSorted) ? _stopwatch.toString() : "Error";
            MainPanel.enableMergeSortButton();
        });
        thread.start();
    }

    // actual merge sort method
    public static ArrayList<PhonebookEntry> mergeSort(ArrayList<PhonebookEntry> phonebookEntries) {

        ArrayList<PhonebookEntry> sortPhonebookEntries = new ArrayList<>(phonebookEntries);
        mergeSortComparisons = 0;

        return mergeSortDivide(sortPhonebookEntries);
    }

    // recursively splits list in half, and when done, calls merge
    private static ArrayList<PhonebookEntry> mergeSortDivide(ArrayList<PhonebookEntry> list) {

        if (list.size() == 1) return list;

        ArrayList<PhonebookEntry> listA;
        listA = new ArrayList<>(list.subList(0, list.size() % 2 == 0 ? list.size() / 2 : list.size() / 2 + 1));
        ArrayList<PhonebookEntry> listB;
        listB = new ArrayList<>(list.subList(listA.size(), list.size()));

        listA = mergeSortDivide(listA);
        listB = mergeSortDivide(listB);

        return mergeSortMerge(listA, listB);
    }

    // merges two lists into one, comparing first elements if present
    // inspired by pseudo-code from http://www.algorithmist.com/index.php/Merge_sort
    private static ArrayList<PhonebookEntry> mergeSortMerge(ArrayList<PhonebookEntry> listA, ArrayList<PhonebookEntry> listB) {

        ArrayList<PhonebookEntry> list = new ArrayList<>();

        while (listA.size() > 0 && listB.size() > 0) {
            if (listA.get(0).getFullName().compareTo(listB.get(0).getFullName()) > 0) {
                list.add(listB.get(0));
                listB.remove(0);
            } else {
                list.add(listA.get(0));
                listA.remove(0);
            }
            mergeSortComparisons++;
        }
        while (listA.size() > 0) {
            list.add(listA.get(0));
            listA.remove(0);
        }
        while (listB.size() > 0) {
            list.add(listB.get(0));
            listB.remove(0);
        }

        return list;
    }
}
