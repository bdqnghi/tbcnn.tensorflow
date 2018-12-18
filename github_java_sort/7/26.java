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
            
            interval = interval * 3 + 1;
            
            
            
            
            while (interval > 0) {
                

                for (outer = interval; outer < size; outer++) {

                    
                    
                    

                    temp = array[outer];

                    System.out.println("Copy " + array[outer] + " into temp");

                    
                    
                    

                    inner = outer;

                    System.out.println("Checking if " + array[inner - interval] + " in index " + (inner - interval) + " is bigger than " + temp);

                    
                    

                    while (inner > interval - 1 && array[inner - interval] >= temp) {

                    System.out.println("In While Checking if " + array[inner - interval] + " in index " + (inner - interval) + " is bigger than " + temp);

                    
                    
                    

                    array[inner] = array[inner - interval];

                    System.out.println(array[inner - interval] + " moved to index " + inner);

                    inner -= interval;

                    System.out.println("inner= " + inner);

                    System.out.println("outer= " + outer);
                    System.out.println("temp= " + temp);
                    System.out.println("interval= " + interval);

                }

                
                
                

                array[inner] = temp;

                System.out.println(temp + " moved to index " + inner);

                System.out.println(Arrays.toString(this.array));

            }

            
            

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
