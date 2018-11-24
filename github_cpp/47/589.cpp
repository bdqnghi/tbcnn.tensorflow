class Solution {
public:
    /**
     * @param nums: The integer array.
     * @param target: Target number to find.
     * @return: The first position of target. Position starts from 0. 
     */
    int binarySearch(vector<int> &array, int target) {
        // write your code here
        int start = 0, end = array.size() - 1, mid;
        while (start + 1 < end) {
            mid = start + (end - start) / 2;
            if (array[mid] == target) end = mid;
            else if(array[mid] > target) end = mid;
            else start = mid;
        }
        if (array[start] == target) return start;
        if (array[end] == target) return end;
        return -1;
    }
};
