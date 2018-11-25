class Solution {
public:
    
    int binarySearch(vector<int> &array, int target) {
        
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
