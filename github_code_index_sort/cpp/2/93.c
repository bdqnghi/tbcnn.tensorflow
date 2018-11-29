#include <iostream>
#include <fstream>
#include <stdlib.h> // NULL
#include <stdio.h>  // srand, rand
#include <time.h>   // time for random numbers
#include <ctime>    // clock()
#include <vector>   // vectors instead of arrays
#include "merge.cpp"
#include "radix.cpp"
#include "insertion.cpp"

using namespace std;
// easy handeling of data and averages
struct data
{
    long swaps = 0;
    long comparisons = 0;
    double time_seconds = 0;
    long total_swaps = 0;
    long total_comparisons = 0;
};

int main()
{
    vector<int> small_array[3];
    vector<int> medium_array[3];
    vector<int> large_array[3];
    int index, index_two, index_three;
    data insertion_sort_data[6];
    data radix_sort_data[6];
    data merge_sort_data[6];
    ofstream log_file("log.txt");

    // random specification
    srand(time(NULL));


    // initialize small arrays
    for(index = 0; index < 3; index++)
    {
        for(index_two = 0; index_two < 1000; index_two++)
        {
            // numbers bewtween 0 and 1000000
            small_array[index].push_back(rand() % 1000001);
        }
    }

    // initialize medium arrays
    for(index = 0; index < 3; index++)
    {
        for(index_two = 0; index_two < 10000; index_two++)
        {
            // numbers bewtween 0 and 1000000
            medium_array[index].push_back(rand() % 1000001);
        }
    }

    // initialize large arrays
    for(index = 0; index < 3; index++)
    {
        for(index_two = 0; index_two < 100000; index_two++)
        {
            // numbers bewtween 0 and 1000000
            large_array[index].push_back(rand() % 1000001);
        }
    }

    log_file << "Scroll to the bottom for averages.\n\n";

    // sort data while recording times, and
    for(index = 0; index <= 3; index++)
    {
            // insertion sort
            if(index == 0)
            {
                log_file << "INSERTION SORT:\n\n";

                for(index_two = 0; index_two < 10; index_two++)
                {


                    insertion_sort_data[0].time_seconds = insertion_sort(small_array[index], insertion_sort_data[0].swaps, insertion_sort_data[0].comparisons);
                    log_file << "Sorting unsorted small array with insertion sort, taking "
                             << insertion_sort_data[0].time_seconds << " seconds" << endl;
                    insertion_sort_data[0].total_swaps += insertion_sort_data[0].swaps;
                    insertion_sort_data[0].total_comparisons += insertion_sort_data[0].comparisons;

                    log_file << "This sort took " << insertion_sort_data[0].swaps << " swaps." << endl;
                    insertion_sort_data[0].swaps = 0;
                    log_file << "This sort took " << insertion_sort_data[0].comparisons << " comparisons." << endl << endl;
                    insertion_sort_data[0].comparisons = 0;



                    insertion_sort_data[1].time_seconds = insertion_sort(small_array[index], insertion_sort_data[1].swaps, insertion_sort_data[1].comparisons);
                    log_file << "Sorting unsorted small array with insertion sort, taking "
                             << insertion_sort_data[1].time_seconds << " seconds" << endl;
                    insertion_sort_data[1].total_swaps += insertion_sort_data[1].swaps;
                    insertion_sort_data[1].total_comparisons += insertion_sort_data[1].comparisons;

                    log_file << "This sort took " << insertion_sort_data[1].swaps << " swaps." << endl;
                    insertion_sort_data[1].swaps = 0;
                    log_file << "This sort took " << insertion_sort_data[1].comparisons << " comparisons." << endl << endl;
                    insertion_sort_data[1].comparisons = 0;




                    insertion_sort_data[2].time_seconds = insertion_sort(medium_array[index], insertion_sort_data[2].swaps, insertion_sort_data[2].comparisons);
                    log_file << "Sorting unsorted medium array with insertion sort, taking "
                             << insertion_sort_data[2].time_seconds << " seconds" << endl;
                    insertion_sort_data[2].total_swaps += insertion_sort_data[2].swaps;
                    insertion_sort_data[2].total_comparisons += insertion_sort_data[2].comparisons;

                    log_file << "This sort took " << insertion_sort_data[2].swaps << " swaps." << endl;
                    insertion_sort_data[2].swaps = 0;
                    log_file << "This sort took " << insertion_sort_data[2].comparisons << " comparisons." << endl << endl;
                    insertion_sort_data[2].comparisons = 0;




                    insertion_sort_data[3].time_seconds = insertion_sort(medium_array[index], insertion_sort_data[3].swaps, insertion_sort_data[3].comparisons);
                    log_file << "Sorting unsorted medium array with insertion sort, taking "
                             << insertion_sort_data[3].time_seconds << " seconds" << endl;
                    insertion_sort_data[3].total_swaps += insertion_sort_data[3].swaps;
                    insertion_sort_data[3].total_comparisons += insertion_sort_data[3].comparisons;

                    log_file << "This sort took " << insertion_sort_data[3].swaps << " swaps." << endl;
                    insertion_sort_data[3].swaps = 0;
                    log_file << "This sort took " << insertion_sort_data[3].comparisons << " comparisons." << endl << endl;
                    insertion_sort_data[3].comparisons = 0;



                    insertion_sort_data[4].time_seconds = insertion_sort(large_array[index], insertion_sort_data[4].swaps, insertion_sort_data[4].comparisons);
                    log_file << "Sorting unsorted large array with insertion sort, taking "
                             << insertion_sort_data[4].time_seconds << " seconds" << endl;
                    insertion_sort_data[4].total_swaps += insertion_sort_data[4].swaps;
                    insertion_sort_data[4].total_comparisons += insertion_sort_data[4].comparisons;

                    log_file << "This sort took " << insertion_sort_data[4].swaps << " swaps." << endl;
                    insertion_sort_data[4].swaps = 0;
                    log_file << "This sort took " << insertion_sort_data[4].comparisons << " comparisons." << endl << endl;
                    insertion_sort_data[4].comparisons = 0;




                    insertion_sort_data[5].time_seconds = insertion_sort(large_array[index], insertion_sort_data[5].swaps, insertion_sort_data[5].comparisons);
                    log_file << "Sorting unsorted large array with insertion sort, taking "
                             << insertion_sort_data[5].time_seconds << " seconds" << endl;
                    insertion_sort_data[5].total_swaps += insertion_sort_data[5].swaps;
                    insertion_sort_data[5].total_comparisons += insertion_sort_data[5].comparisons;

                    log_file << "This sort took " << insertion_sort_data[5].swaps << " swaps." << endl;
                    insertion_sort_data[5].swaps = 0;
                    log_file << "This sort took " << insertion_sort_data[5].comparisons << " comparisons." << endl << endl;
                    insertion_sort_data[5].comparisons = 0;

                    cout << "Insertion sort #" << index_two+1 << " completed." << endl;

                    // reset values
                    for(index_three = 0; index_three < 1000; index_three++)
                    {
                        small_array[index][index_three] = (rand() % 1000001);
                    }
                    for(index_three = 0; index_three < 10000; index_three++)
                    {
                        medium_array[index][index_three] = (rand() % 1000001);
                    }
                    for(index_three = 0; index_three < 100000; index_three++)
                    {
                        large_array[index][index_three] = (rand() % 1000001);
                    }
                }


            }

            // radix sort
            if(index == 1)
            {
                log_file << "RADIX SORT:\n\n";

                for(index_two = 0; index_two < 10; index_two++)
                {


                    radix_sort_data[0].time_seconds = radix_sort(small_array[index], radix_sort_data[0].swaps, radix_sort_data[0].comparisons);
                    log_file << "Sorting unsorted small array with radix sort, taking "
                             << radix_sort_data[0].time_seconds << " seconds" << endl;
                    radix_sort_data[0].total_swaps += radix_sort_data[0].swaps;
                    radix_sort_data[0].total_comparisons += radix_sort_data[0].comparisons;

                    log_file << "This sort took " << radix_sort_data[0].swaps << " swaps." << endl;
                    radix_sort_data[0].swaps = 0;
                    log_file << "This sort took " << radix_sort_data[0].comparisons << " comparisons." << endl << endl;
                    radix_sort_data[0].comparisons = 0;



                    radix_sort_data[1].time_seconds = radix_sort(small_array[index], radix_sort_data[1].swaps, radix_sort_data[1].comparisons);
                    log_file << "Sorting unsorted small array with radix sort, taking "
                             << radix_sort_data[1].time_seconds << " seconds" << endl;
                    radix_sort_data[1].total_swaps += radix_sort_data[1].swaps;
                    radix_sort_data[1].total_comparisons += radix_sort_data[1].comparisons;

                    log_file << "This sort took " << radix_sort_data[1].swaps << " swaps." << endl;
                    radix_sort_data[1].swaps = 0;
                    log_file << "This sort took " << radix_sort_data[1].comparisons << " comparisons." << endl << endl;
                    radix_sort_data[1].comparisons = 0;




                    radix_sort_data[2].time_seconds = radix_sort(medium_array[index], radix_sort_data[2].swaps, radix_sort_data[2].comparisons);
                    log_file << "Sorting unsorted medium array with radix sort, taking "
                             << radix_sort_data[2].time_seconds << " seconds" << endl;
                    radix_sort_data[2].total_swaps += radix_sort_data[2].swaps;
                    radix_sort_data[2].total_comparisons += radix_sort_data[2].comparisons;

                    log_file << "This sort took " << radix_sort_data[2].swaps << " swaps." << endl;
                    radix_sort_data[2].swaps = 0;
                    log_file << "This sort took " << radix_sort_data[2].comparisons << " comparisons." << endl << endl;
                    radix_sort_data[2].comparisons = 0;




                    radix_sort_data[3].time_seconds = radix_sort(medium_array[index], radix_sort_data[3].swaps, radix_sort_data[3].comparisons);
                    log_file << "Sorting unsorted medium array with radix sort, taking "
                             << radix_sort_data[3].time_seconds << " seconds" << endl;
                    radix_sort_data[3].total_swaps += radix_sort_data[3].swaps;
                    radix_sort_data[3].total_comparisons += radix_sort_data[3].comparisons;

                    log_file << "This sort took " << radix_sort_data[3].swaps << " swaps." << endl;
                    radix_sort_data[3].swaps = 0;
                    log_file << "This sort took " << radix_sort_data[3].comparisons << " comparisons." << endl << endl;
                    radix_sort_data[3].comparisons = 0;



                    radix_sort_data[4].time_seconds = radix_sort(large_array[index], radix_sort_data[4].swaps, radix_sort_data[4].comparisons);
                    log_file << "Sorting unsorted large array with radix sort, taking "
                             << radix_sort_data[4].time_seconds << " seconds" << endl;
                    radix_sort_data[4].total_swaps += radix_sort_data[4].swaps;
                    radix_sort_data[4].total_comparisons += radix_sort_data[4].comparisons;

                    log_file << "This sort took " << radix_sort_data[4].swaps << " swaps." << endl;
                    radix_sort_data[4].swaps = 0;
                    log_file << "This sort took " << radix_sort_data[4].comparisons << " comparisons." << endl << endl;
                    radix_sort_data[4].comparisons = 0;




                    radix_sort_data[5].time_seconds = radix_sort(large_array[index], radix_sort_data[5].swaps, radix_sort_data[5].comparisons);
                    log_file << "Sorting unsorted large array with radix sort, taking "
                             << radix_sort_data[5].time_seconds << " seconds" << endl;
                    radix_sort_data[5].total_swaps += radix_sort_data[5].swaps;
                    radix_sort_data[5].total_comparisons += radix_sort_data[5].comparisons;

                    log_file << "This sort took " << radix_sort_data[5].swaps << " swaps." << endl;
                    radix_sort_data[5].swaps = 0;
                    log_file << "This sort took " << radix_sort_data[5].comparisons << " comparisons." << endl << endl;
                    radix_sort_data[5].comparisons = 0;

                    cout << "Radix sort #" << index_two+1 << " completed." << endl;

                    // reset values
                    for(index_three = 0; index_three < 1000; index_three++)
                    {
                        small_array[index][index_three] = (rand() % 1000001);
                    }
                    for(index_three = 0; index_three < 10000; index_three++)
                    {
                        medium_array[index][index_three] = (rand() % 1000001);
                    }
                    for(index_three = 0; index_three < 100000; index_three++)
                    {
                        large_array[index][index_three] = (rand() % 1000001);
                    }
                }
            }

            // merge sort
            if(index == 2)
            {

                for(index_two = 0; index_two < 10; index_two++)
                {


                    merge_sort_data[0].time_seconds = merge_sort(small_array[index], 0, 1000, merge_sort_data[0].swaps, merge_sort_data[0].comparisons);
                    log_file << "Sorting unsorted small array with merge sort, taking "
                             << merge_sort_data[0].time_seconds << " seconds" << endl;
                    merge_sort_data[0].total_swaps += merge_sort_data[0].swaps;
                    merge_sort_data[0].total_comparisons += merge_sort_data[0].comparisons;

                    log_file << "This sort took " << merge_sort_data[0].swaps << " swaps." << endl;
                    merge_sort_data[0].swaps = 0;
                    log_file << "This sort took " << merge_sort_data[0].comparisons << " comparisons." << endl << endl;
                    merge_sort_data[0].comparisons = 0;



                    merge_sort_data[1].time_seconds = merge_sort(small_array[index], 0, 1000, merge_sort_data[1].swaps, merge_sort_data[1].comparisons);
                    log_file << "Sorting unsorted small array with merge sort, taking "
                             << merge_sort_data[1].time_seconds << " seconds" << endl;
                    merge_sort_data[1].total_swaps += merge_sort_data[1].swaps;
                    merge_sort_data[1].total_comparisons += merge_sort_data[1].comparisons;

                    log_file << "This sort took " << merge_sort_data[1].swaps << " swaps." << endl;
                    merge_sort_data[1].swaps = 0;
                    log_file << "This sort took " << merge_sort_data[1].comparisons << " comparisons." << endl << endl;
                    merge_sort_data[1].comparisons = 0;




                    merge_sort_data[2].time_seconds = merge_sort(medium_array[index], 0, 10000, merge_sort_data[2].swaps, merge_sort_data[2].comparisons);
                    log_file << "Sorting unsorted medium array with merge sort, taking "
                             << merge_sort_data[2].time_seconds << " seconds" << endl;
                    merge_sort_data[2].total_swaps += merge_sort_data[2].swaps;
                    merge_sort_data[2].total_comparisons += merge_sort_data[2].comparisons;

                    log_file << "This sort took " << merge_sort_data[2].swaps << " swaps." << endl;
                    merge_sort_data[2].swaps = 0;
                    log_file << "This sort took " << merge_sort_data[2].comparisons << " comparisons." << endl << endl;
                    merge_sort_data[2].comparisons = 0;




                    merge_sort_data[3].time_seconds = merge_sort(medium_array[index], 0, 10000, merge_sort_data[3].swaps, merge_sort_data[3].comparisons);
                    log_file << "Sorting unsorted medium array with merge sort, taking "
                             << merge_sort_data[3].time_seconds << " seconds" << endl;
                    merge_sort_data[3].total_swaps += merge_sort_data[3].swaps;
                    merge_sort_data[3].total_comparisons += merge_sort_data[3].comparisons;

                    log_file << "This sort took " << merge_sort_data[3].swaps << " swaps." << endl;
                    merge_sort_data[3].swaps = 0;
                    log_file << "This sort took " << merge_sort_data[3].comparisons << " comparisons." << endl << endl;
                    merge_sort_data[3].comparisons = 0;



                    merge_sort_data[4].time_seconds = merge_sort(large_array[index], 0, 100000, merge_sort_data[4].swaps, merge_sort_data[4].comparisons);
                    log_file << "Sorting unsorted large array with merge sort, taking "
                             << merge_sort_data[4].time_seconds << " seconds" << endl;
                    merge_sort_data[4].total_swaps += merge_sort_data[4].swaps;
                    merge_sort_data[4].total_comparisons += merge_sort_data[4].comparisons;

                    log_file << "This sort took " << merge_sort_data[4].swaps << " swaps." << endl;
                    merge_sort_data[4].swaps = 0;
                    log_file << "This sort took " << merge_sort_data[4].comparisons << " comparisons." << endl << endl;
                    merge_sort_data[4].comparisons = 0;




                    merge_sort_data[5].time_seconds = merge_sort(large_array[index], 0, 100000, merge_sort_data[5].swaps, merge_sort_data[5].comparisons);
                    log_file << "Sorting unsorted large array with merge sort, taking "
                             << merge_sort_data[5].time_seconds << " seconds" << endl;
                    merge_sort_data[5].total_swaps += merge_sort_data[5].swaps;
                    merge_sort_data[5].total_comparisons += merge_sort_data[5].comparisons;

                    log_file << "This sort took " << merge_sort_data[5].swaps << " swaps." << endl;
                    merge_sort_data[5].swaps = 0;
                    log_file << "This sort took " << merge_sort_data[5].comparisons << " comparisons." << endl << endl;
                    merge_sort_data[5].comparisons = 0;

                    cout << "Merge sort #" << index_two+1 << " completed." << endl;

                    // reset values
                    for(index_three = 0; index_three < 1000; index_three++)
                    {
                        small_array[index][index_three] = (rand() % 1000001);
                    }
                    for(index_three = 0; index_three < 10000; index_three++)
                    {
                        medium_array[index][index_three] = (rand() % 1000001);
                    }
                    for(index_three = 0; index_three < 100000; index_three++)
                    {
                        large_array[index][index_three] = (rand() % 1000001);
                    }
                }
            }
    }

    // output averages
    log_file << "\n\nINSERTION SORT AVERAGES:\n" ;

    log_file << "Small array (unsorted):\n"
             << "Swaps: " << insertion_sort_data[0].total_swaps/10 << endl
             << "Comparisons: " << insertion_sort_data[0].total_comparisons/10 << endl;

    log_file << "Small array (sorted):\n"
             << "Swaps: " << insertion_sort_data[1].total_swaps/10 << endl
             << "Comparisons: " << insertion_sort_data[1].total_comparisons/10 << endl;

    log_file << "Medium array (unsorted):\n"
             << "Swaps: " << insertion_sort_data[2].total_swaps/10 << endl
             << "Comparisons: " << insertion_sort_data[2].total_comparisons/10 << endl;

    log_file << "Medium array (unsorted):\n"
             << "Swaps: " << insertion_sort_data[3].total_swaps/10 << endl
             << "Comparisons: " << insertion_sort_data[3].total_comparisons/10 << endl;

    log_file << "Large array (unsorted):\n"
             << "Swaps: " << insertion_sort_data[4].total_swaps/10 << endl
             << "Comparisons: " << insertion_sort_data[4].total_comparisons/10 << endl;

    log_file << "Large array (sorted):\n"
             << "Swaps: " << insertion_sort_data[5].total_swaps/10 << endl
             << "Comparisons: " << insertion_sort_data[5].total_comparisons/10 << endl;


    log_file << "\n\nRADIX SORT AVERAGES:\n" ;

    log_file << "Small array (unsorted):\n"
             << "Swaps: " << radix_sort_data[0].total_swaps/10 << endl
             << "Comparisons: " << radix_sort_data[0].total_comparisons/10 << endl;

    log_file << "Small array (sorted):\n"
             << "Swaps: " << radix_sort_data[1].total_swaps/10 << endl
             << "Comparisons: " << radix_sort_data[1].total_comparisons/10 << endl;

    log_file << "Medium array (unsorted):\n"
             << "Swaps: " << radix_sort_data[2].total_swaps/10 << endl
             << "Comparisons: " << radix_sort_data[2].total_comparisons/10 << endl;

    log_file << "Medium array (unsorted):\n"
             << "Swaps: " << radix_sort_data[3].total_swaps/10 << endl
             << "Comparisons: " << radix_sort_data[3].total_comparisons/10 << endl;

    log_file << "Large array (unsorted):\n"
             << "Swaps: " << radix_sort_data[4].total_swaps/10 << endl
             << "Comparisons: " << radix_sort_data[4].total_comparisons/10 << endl;

    log_file << "Large array (sorted):\n"
             << "Swaps: " << radix_sort_data[5].total_swaps/10 << endl
             << "Comparisons: " << radix_sort_data[5].total_comparisons/10 << endl;


    log_file << "\n\nMERGE SORT AVERAGES:\n" ;

    log_file << "Small array (unsorted):\n"
             << "Swaps: " << merge_sort_data[0].total_swaps/10 << endl
             << "Comparisons: " << merge_sort_data[0].total_comparisons/10 << endl;

    log_file << "Small array (sorted):\n"
             << "Swaps: " << merge_sort_data[1].total_swaps/10 << endl
             << "Comparisons: " << merge_sort_data[1].total_comparisons/10 << endl;

    log_file << "Medium array (unsorted):\n"
             << "Swaps: " << merge_sort_data[2].total_swaps/10 << endl
             << "Comparisons: " << merge_sort_data[2].total_comparisons/10 << endl;

    log_file << "Medium array (unsorted):\n"
             << "Swaps: " << merge_sort_data[3].total_swaps/10 << endl
             << "Comparisons: " << merge_sort_data[3].total_comparisons/10 << endl;

    log_file << "Large array (unsorted):\n"
             << "Swaps: " << merge_sort_data[4].total_swaps/10 << endl
             << "Comparisons: " << merge_sort_data[4].total_comparisons/10 << endl;

    log_file << "Large array (sorted):\n"
             << "Swaps: " << merge_sort_data[5].total_swaps/10 << endl
             << "Comparisons: " << merge_sort_data[5].total_comparisons/10 << endl;

    return 0;
}
