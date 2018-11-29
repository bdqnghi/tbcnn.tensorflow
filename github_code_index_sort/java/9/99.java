// java.util.* and java.util.streams.* have been imported for this problem.
// You don't need any other imports.

public static int[] selectionSortArray(int[] arr){
    if(arr.length<=1) return arr;
    int start = 0;
    while(start != arr.length-1) {
        int minIndex = start;
        for(int i=start+1;i<arr.length;i++) {
            if(arr[i] <= arr[minIndex]) {
                minIndex = i;
            }
        }
        int tmp = arr[start];
        arr[start] = arr[minIndex];
        arr[minIndex] = tmp;
        start++;
    }
    return arr;
}