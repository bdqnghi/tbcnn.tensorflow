#include <iostream>

using namespace std;

int binarySearch (int array[], int size, int searchValue) {

    int low = 0;
    int high = size - 1;
    int mid;

    while (low <= high) {
        mid = (low + high) / 2;
        if(searchValue == array[mid]) {
            return mid;
        } else if (searchValue > array[mid]) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1;

}

int main () {

    int a[] = {1, 12, 15, 27, 48, 49, 87, 97};
    int userValue;
    int result;

    cout << "Enter a integer" << endl;
    cin >> userValue;
    result = binarySearch(a, 8, userValue);
    if (result >= 0) {
        cout << "The number " << userValue << " was found at element with index " << result << endl;
    } else {
        cout << "The number " << userValue << " was not found" << endl;
    }
}
