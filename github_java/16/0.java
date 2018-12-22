import java.util.Arrays;


class QuickSort {
    private static int[] array;
    private static int size;


    public static void main(String[] args) {
        QuickSort sort = new QuickSort(10);
        System.out.println(Arrays.toString(sort.array));

        sort.sort(0, 9);
        System.out.println(Arrays.toString(sort.array));
    }

    public void sort(int left, int right) {
        if(right - left <= 0)
            return;  // Everything is sorted
        
        else {
            // It doesn't matter  what the pivot is, but it must
            // be a value in the array
            int pivot = this.array[right];

            System.out.println("Value in right "+this.array[right]+" is made the pivot");
            System.out.println("left="+left+" right="+right+" pivot="+pivot+"\n\n");

            int pivotLocation = this.partition(left, right, pivot);
            System.out.println("Value in left "+this.array[left]+" is made the pivot\n\n");

            this.sort(left, pivotLocation - 1); // sort the left
            this.sort(pivotLocation + 1, right); // sort the right
        }
    }


    public int partition(int leftpointer, int right, int pivot) {
        int left = leftpointer - 1;

        while(true){
            while(this.array[++left] < pivot);
            System.out.println("Bigger value found against pivot "+pivot+" is "+this.array[left]);
            
            while(right > 0 && this.array[--right] > pivot);
            System.out.println("Smaller value found against pivot "+pivot+" is "+this.array[right]);

            if(left >= right) break;

            else {
                this.swap(left, right);
                System.out.println(this.array[left]+" was swapped for "+this.array[right]);
            }

        }

        this.swap(leftpointer, right);
        return leftpointer;
    }


    public void swap(int pos1, int pos2) {
        int temp = this.array[pos1];
        this.array[pos1] = this.array[pos2];
        this.array[pos2] = temp;
    }


    public void generate() {
        for(int i=0; i<this.size; ++i)
            this.array[i] = (int)(Math.random()*50)+10;
    }


    QuickSort(int size) {
        this.size = size;
        this.array = new int[size];
        this.generate();
    }
}