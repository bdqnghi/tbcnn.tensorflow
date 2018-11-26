package algorithmsAndDataStructure.algorithms.child;

import algorithmsAndDataStructure.algorithms.parent.SortAlgorithm;
import algorithmsAndDataStructure.domain.Airport;

import java.time.LocalTime;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

/**
 * We are going to use Built-in method which implemented merge-sort:
 * <p>
 * Strategy of Merge sort is: Divide - Conquer.
 *
 * 1- Divide whole list half
 * 2- Sort first half  -Recursion
 * 3- Sort second half  -Recursion
 * 4- Merge sorted lists
 *
 * Best Case: list has one element =  O(1)
 * Worst Case: O()
 */
class MergeSortAlgorithm extends SortAlgorithm {


    // BenchMarking: Data: 6050 , Algoritm Process took: 0.014 second(s). - FUCKING FAST than insertion (Mystry) sort even.
    @Override
    public void toSortArray(Airport[] airports) {

        System.out.println("START MergeSortAlgorithm in CLASSIC ARRAY");
        algorithmTimer.setStartInstant(LocalTime.now());

             /* Built-in optimized merge-sort */
        Comparator<Airport> byCityName = (firstElement, secondElement) ->
                firstElement.getCity().compareTo(secondElement.getCity());
        Collections.sort(Arrays.asList(airports), byCityName);

        algorithmTimer.setFinishInstant(LocalTime.now());
        algorithmTimer.printOutTime();

        System.out.println("FINISH MergeSortAlgorithm in CLASSIC ARRAY");
        System.out.println();
    }


    // BenchMarking: Data: 6050 , Algoritm Process took: 0.009 second(s).
    @Override
    public void toSortList(List<Airport> airportList) {
        System.out.println();
        System.out.println("START MergeSortAlgorithmin LIST");
        algorithmTimer.setStartInstant(LocalTime.now());

        //    Built-in optimized merge-sort
        Comparator<Airport> byCityName = (firstElement, secondElement) ->
                firstElement.getCity().compareTo(secondElement.getCity());
        Collections.sort(airportList, byCityName);

        algorithmTimer.setFinishInstant(LocalTime.now());
        algorithmTimer.printOutTime();

        System.out.println("FINISH MergeSortAlgorithm in LIST");
        System.out.println();
    }


    //BenchMarking: Data: 6050 , Algoritm Process took: 0.006 second(s).
    @Override
    public void toSortLinkedList(List<Airport> airportList) {
        System.out.println();
        System.out.println("START MergeSortAlgorithm in LINKEDLIST");
        algorithmTimer.setStartInstant(LocalTime.now());

             /* Built-in optimized merge-sort */
        Comparator<Airport> byCityName = (firstElement, secondElement) ->
                firstElement.getCity().compareTo(secondElement.getCity());
        Collections.sort(airportList, byCityName);

        algorithmTimer.setFinishInstant(LocalTime.now());
        algorithmTimer.printOutTime();

        System.out.println("FINISH MergeSortAlgorithm in LINKEDLIST");
        System.out.println();
    }
}
