#include <iostream>
#include "container.h"
#include "list.h"
#include "vector.h"
#include "bubblesort.h"
#include "selectionsort.h"
#include "mergesort.h"

using namespace std;

void containerMenu(Container *&);
void elementMenu(Container *);
void sortMenu(Container *);

int main(void) {
    Container * container;
    //SortAlgorithm * sortAlgo;

    containerMenu(container);

    /*
    container->insert(8);
    container->insert(64);
    container->insert(16);
    container->insert(32);
    container->insert(128);
    container->insert(4);
    */
    elementMenu(container);
    container->print();

    //sortAlgo = new SelectionSort();

    //container->set_sort(sortAlgo);
    sortMenu(container);
    container->sort();

    container->print();
}

void containerMenu(Container *& container) {
    int selection = 0;

    while (1) {
        cout << "Select a container:" << endl
            << "  1. List" << endl
            << "  2. Vector" << endl << endl
            << "        Selection: ";
        cin.clear();
        cin >> selection;
        if (selection == 1 || selection == 2)
            break;
        cout << endl << "Error: Invalid selection!" << endl
            << "Please enter your selection as either 1 or 2." << endl
            << endl;
    }
 
    switch(selection) {
        case 1:
            container = new List();
            break;
        case 2:
            container = new Vector();
            break;
    }
}

void elementMenu(Container * container) {
    int element;

    cout << "Enter an integer to store as an element in the container."
        << endl << "Enter a non-integer to end." << endl;
    cin.clear();
    while (cin >> element) {
        cout << endl << "Element: ";
        container->insert(element);
    }
}

void sortMenu(Container * container) {
    int selection = 0;

    while (selection != 1 || selection != 2 || selection != 3) {
        cout << "Choose a method to sort the container." << endl
            << "  1. Bubble Sort" << endl
            << "  2. Selection Sort" << endl
            << "  3. Merge Sort" << endl << endl
            << "        Selection:";
        cin.clear();
        cin.ignore(10000, '\n');
        cin >> selection;
        if (selection == 1 || selection == 2 || selection == 3)
            break;
        cout << "Please enter a valid selection" << endl;
    }
    switch (selection) {
        case 1:
            container->set_sort(new BubbleSort());
            break;
        case 2:
            container->set_sort(new SelectionSort());
            break;
        case 3:
            container->set_sort(new MergeSort());
            break;
    }
}
