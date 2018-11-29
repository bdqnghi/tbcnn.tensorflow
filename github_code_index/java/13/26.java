import java.util.Arrays;

class ShellSort {

    private int size;
    private int[] array;

    ShellSort(int arraySize) {
        this.size = arraySize;
        this.array = new int[this.size];
        this.generate();
    }

    private void generate() {
        for(int i=0; i<this.size; ++i)
            this.array[i] = (int)(Math.random()*50)+10;
    }

    public void sort() {
        int inner, outer, temp;
        int interval = 1;
        
        while (interval <= size / 3) {
            // Define an interval sequence
            interval = interval * 3 + 1;
            
            // Keep looping until the interval is 1
            // Then this becomes an insertion sort
            
            while (interval > 0) {
                // Continue incrementing outer until the end of the array is reached

                for (outer = interval; outer < size; outer++) {

                    // Store the value of the array in temp unless it has to be
                    // copied to a space occupied by a bigger number closer to the
                    // beginning of the array

                    temp = array[outer];

                    System.out.println("Copy " + array[outer] + " into temp");

                    // inner is assigned the value of the highest index to check
                    // against all values the proceed it. Along the way if a
                    // number is greater than temp it will be moved up in the array

                    inner = outer;

                    System.out.println("Checking if " + array[inner - interval] + " in index " + (inner - interval) + " is bigger than " + temp);

                    // While there is a number bigger than temp move it further
                    // up in the array

                    while (inner > interval - 1 && array[inner - interval] >= temp) {

                    System.out.println("In While Checking if " + array[inner - interval] + " in index " + (inner - interval) + " is bigger than " + temp);

                    // Make room for the smaller temp by moving values in the
                    // array
                    // up one space if they are greater than temp

                    array[inner] = array[inner - interval];

                    System.out.println(array[inner - interval] + " moved to index " + inner);

                    inner -= interval;

                    System.out.println("inner= " + inner);

                    System.out.println("outer= " + outer);
                    System.out.println("temp= " + temp);
                    System.out.println("interval= " + interval);

                }

                // Now that everything has been moved into place put the value
                // stored in temp into the index above the first value smaller
                // than it is

                array[inner] = temp;

                System.out.println(temp + " moved to index " + inner);

                System.out.println(Arrays.toString(this.array));

            }

            // Once we get here we have interval sorted our array
            // so we decrement interval and go again

            interval = (interval - 1) / 3;
        }

    }
}



    public static void main(String[] args) {
        ShellSort sort = new ShellSort(10);
        System.out.println(Arrays.toString(sort.array));

        sort.sort();
        System.out.println(Arrays.toString(sort.array));
    }
}
