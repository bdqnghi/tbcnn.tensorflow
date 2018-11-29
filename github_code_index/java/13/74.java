import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;


/*
 * The ReadFile class holds the main method and readFile() method. It is 
 * responsible for initiating execution, reading in the data from the input
 * file(s), maintaining the System clocks for timing execution, and calling 
 * each of the sort functions. 
 */
public class ReadFile {

    /*
     * This function reads in the data from args 1 through n. It will 
     * interpret any element in the input file that contains a " " as 
     * reflecting the size of the input, which is used to establish the 
     * size of array needed. 
     * 
     * @input: String inputFile is sent from main and collected from command
     * line args 1-n. 
     * @endstate: All sorts are complete and output file for file sizes == 50
     * is written to the location of args[0]
     * 
     * 
     */
    public void readFile(String inputFile)
    {
        try {
                HeapSort heap = new HeapSort();
                WriteFile write = new WriteFile();
                int inputSize = 50;
                BufferedReader readFile = new BufferedReader(
                                new FileReader(new File(inputFile)));
                String nextInput = readFile.readLine();
                
                
                
                //collect input size
                if (nextInput.contains(" ")) 
                {
                    inputSize = Integer.parseInt(nextInput.trim());
                }
            
            
            
                //copies for multiple runs
                int[] inputArr = new int[inputSize];    //heap sort
                int[] inputCopy1 = new int[inputSize];  //shell with Hibbard
                int[] inputCopy2 = new int[inputSize];  //shell with Knuth
                int[] inputCopy3 = new int[inputSize];  //shell with primes
                int[] inputCopy4 = new int[inputSize];  //shell with evens

            
                
                //read in array from file
                for (int index = 0; nextInput != null; index++) 
                {
                    if (nextInput.contains(" ")) 
                    {
                        inputSize = Integer.parseInt(nextInput.trim());
                        nextInput = readFile.readLine();
                    }
                    inputArr[index] = Integer.parseInt(nextInput.trim());
                    nextInput = readFile.readLine();
                }
            
                //deep copies for each run
                int index = 0;
                for (int each : inputArr) {
                    inputCopy1[index] = each;
                    inputCopy2[index] = each;
                    inputCopy3[index] = each;
                    inputCopy4[index] = each;
                    index++;
                }
                
                
//Start Heap Sort
                //print for input size == 50
                if (inputSize == 50) {
                    System.out.println("Heap Sort - Input Size: " + inputSize);
                    write.writeFile(HeapSort.outputLocation, 
                                    "Heap Sort - Input Size: " + inputSize );
                    write.writeLine(HeapSort.outputLocation );

                    System.out.println("Original Array: ");
                    write.writeFile(HeapSort.outputLocation, 
                                    "Original Array: ");
                    write.writeLine(HeapSort.outputLocation );
                    heap.printArray(inputArr, inputSize);
                }
            
                //execute sort
                long startClock = System.nanoTime();
                heap.heap_sort(inputArr, inputSize);
                long endClock = System.nanoTime();
                long timeElapsed = endClock-startClock;

                
                //print out sorted array for inputSize == 50
                if (inputSize == 50) {
                    System.out.println("Sorted Array: ");
                    write.writeFile(HeapSort.outputLocation, "Sorted Array: ");
                    write.writeLine(HeapSort.outputLocation );
                    heap.printArray(inputArr,  inputSize);
                
                    System.out.println("Time elapsed for Heap Sort with input size " 
                                    +inputSize +": " + (timeElapsed / 1000)
                                    + " microseconds.\n");
                    write.writeFile( HeapSort.outputLocation, (
                                    "Time elapsed for Heap Sort with input size " 
                                    +inputSize +": " + 
                                    ((endClock - startClock) / 1000)
                                    + " microseconds."));
                    write.writeLine(HeapSort.outputLocation );               
                    write.writeLine(HeapSort.outputLocation );               
                }
            

// start shell sort with knuth's sequence
            // Knuth formula
            // h(1) = 1
            // h(n) = 3*h(n-1)+1
            ShellSort shell = new ShellSort();
            int knuthArr[] = new int[20];
            int gap = 0;
            int elem = 0;
            for (elem = 0; elem < 20; elem++) {
                gap = (3 * gap) + 1;
                knuthArr[elem] = gap;
            }
            

            //print for input size == 50
            if (inputSize == 50) {
                System.out.println("ShellSort with input size " 
                + inputSize + ": ");
                write.writeFile(HeapSort.outputLocation, 
                                "ShellSort with input size " + inputSize + ": ");
                write.writeLine(HeapSort.outputLocation );
                
                
            
                System.out.println("All Knuth gaps: ");
                write.writeFile(HeapSort.outputLocation, "All Knuth gaps: ");
                write.writeLine(HeapSort.outputLocation );
                
                shell.printArray(knuthArr);
                
                
                System.out.print("Original array: \n");
                write.writeFile(HeapSort.outputLocation, "Original array: ");
                write.writeLine(HeapSort.outputLocation );
                
                
                shell.printArray(inputCopy2);
            }

            
            //execute sort
            startClock = System.nanoTime();
            shell.sort(knuthArr, inputCopy2);
            endClock = System.nanoTime(); 
            timeElapsed = endClock - startClock;
            
            
            
            //print if input size ==50
            if (inputSize == 50) {
                System.out.println("Sorted Array: ");
                write.writeFile(HeapSort.outputLocation, "Sorted Array: ");
                write.writeLine(HeapSort.outputLocation );
                shell.printArray(inputCopy2);
            
                System.out.println("Time Elapsed for Knuth Shell Sort with input"
                                + "size " + inputSize + ": "
                                + ((endClock - startClock) / 1000)
                                + " microseconds.\n");
                System.out.println();
                write.writeFile( HeapSort.outputLocation, 
                                ("Time Elapsed for Knuth Shell Sort with input"
                                + "size " + inputSize + ": "
                                + ((endClock - startClock) / 1000)
                                + " microseconds."));
                write.writeLine(HeapSort.outputLocation );
                write.writeLine(HeapSort.outputLocation );
            }

            
            
            
// Start shell sort with spaced out prime numbers
            int primeArr[] = { 1, 5, 17, 53, 149, 373, 1123, 3371, 10111,
                            30341, 91009, 272999 };

            if (inputSize == 50) {
                System.out.println("ShellSort with input size " 
                                + inputSize + " and spaced out prime gaps: ");
                write.writeFile(HeapSort.outputLocation, 
                                "ShellSort with input size " + inputSize 
                                + " and spaced out prime gaps: ");
                write.writeLine(HeapSort.outputLocation);
    
                
                shell.printArray(primeArr);
                
                
                System.out.println("Original array: ");
                write.writeFile(HeapSort.outputLocation, "Original array: ");
                write.writeLine(HeapSort.outputLocation);
                
                shell.printArray(inputCopy3);
            }
            
            
            //execute sort
            startClock = System.nanoTime(); 
            shell.sort(primeArr, inputCopy3);
            endClock = System.nanoTime(); 
            timeElapsed = endClock - startClock; 
            
            
            
            //Print if inputSize == 50
            if (inputSize == 50) {
                System.out.println("Sorted array: ");
                write.writeFile(HeapSort.outputLocation, "Sorted array: ");
                write.writeLine(HeapSort.outputLocation);
                shell.printArray(inputCopy3);

                System.out.println("Time Elapsed for spaced out prime gap "
                                + "Shell Sort with input size " + inputSize + ": "
                                + ((endClock - startClock) / 1000)
                                + " microseconds.\n");
                System.out.println();
                write.writeFile( HeapSort.outputLocation, 
                                ("Time Elapsed for spaced out prime gap "
                                + "Shell Sort with input"
                                + "size " + inputSize + ": "
                                + ((endClock - startClock) / 1000)
                                + " microseconds."));
                write.writeLine(HeapSort.outputLocation );
                write.writeLine(HeapSort.outputLocation );
            }
            
            
// start shellsort with composite even numbers
            int evenArr[] = { 1, 10, 30, 60, 120, 360, 1080, 3240, 9720,
                            29160, 87480, 262440 };

            if (inputSize == 50) {
                System.out.println("ShellSort with input size " 
                                + inputSize + " and spaced out even gaps: ");
                write.writeFile(HeapSort.outputLocation, 
                                "ShellSort with input size " + inputSize 
                                + " and spaced out even gaps: ");
                write.writeLine(HeapSort.outputLocation);
    
                
                shell.printArray(evenArr);
                
                
                System.out.println("Original array: ");
                write.writeFile(HeapSort.outputLocation, "Original array: ");
                write.writeLine(HeapSort.outputLocation );
                shell.printArray(inputCopy4);
            }
            
            //execute sort
            startClock = System.nanoTime();
            shell.sort(evenArr, inputCopy4);
            endClock = System.nanoTime();
            timeElapsed = endClock-startClock;
            
            
            
            if (inputSize == 50) {
                System.out.println("Sorted array: ");
                write.writeFile(HeapSort.outputLocation, "Sorted array: ");
                write.writeLine(HeapSort.outputLocation );
                shell.printArray(inputCopy4);
            
            
                System.out.println("Time Elapsed for spaced out even gap "
                                + "Shell Sort with input size " + inputSize + ": "
                                + ((endClock - startClock) / 1000)
                                + " microseconds.\n");
                System.out.println();
                write.writeFile( HeapSort.outputLocation, 
                                ("Time Elapsed for spaced out even gap "
                                + "Shell Sort with input"
                                + "size " + inputSize + ": "
                                + ((endClock - startClock) / 1000)
                                + " microseconds."));
                write.writeLine(HeapSort.outputLocation );
                write.writeLine(HeapSort.outputLocation );
            }

//Start shellsort with additional gap set (Hibbard, 1963)
            // Hibbard gap formula: (2^k)-1
            // Hibbard, Thomas N. (1963). "An Empirical Study of Minimal Storage Sorting".
            // Communications of the ACM. 6 (5): 206�213. doi:10.1145/366552.366557.

            
            //Use formula to create gap array
            int hibbardArr[] = new int[20];
            gap = 1;
            int k;
            elem = 0;
            for (elem = 0; elem < hibbardArr.length; elem++) {
                gap = 1;
                for (k = elem + 1; k > 0; k--) {
                    gap = gap * 2;
                }
                gap = gap - 1;
                hibbardArr[elem] = gap;
            }
            
            if (inputSize == 50) {
                System.out.println("ShellSort with input size " 
                                + inputSize + " and Hibbard gaps: ");
                write.writeFile(HeapSort.outputLocation, 
                                "ShellSort with input size " + inputSize 
                                + " and Hibbard gaps: ");
                write.writeLine(HeapSort.outputLocation);

                shell.printArray(hibbardArr);
                System.out.println("Original array: ");
                write.writeFile(HeapSort.outputLocation, "Original array: ");
                write.writeLine(HeapSort.outputLocation);
                shell.printArray(inputCopy1);
            }
            
            //execute sort
            startClock = System.nanoTime();
            shell.sort(hibbardArr, inputCopy1);
            endClock = System.nanoTime(); 
            timeElapsed = endClock-startClock; 
            
            
            
            if (inputSize == 50) {
                System.out.println("Sorted array: ");
                write.writeFile(HeapSort.outputLocation, "Sorted array: ");
                write.writeLine(HeapSort.outputLocation);
                
                shell.printArray(inputCopy1);
            
                System.out.println("Time Elapsed for Hibbard gap "
                                + "Shell Sort with input size " + inputSize + ": "
                                + ((endClock - startClock) / 1000)
                                + " microseconds.\n");
                System.out.println();
                write.writeFile( HeapSort.outputLocation, 
                                ("Time Elapsed for Hibbard gap "
                                + "Shell Sort with input"
                                + "size " + inputSize + ": "
                                + ((endClock - startClock) / 1000)
                                + " microseconds."));
                write.writeLine(HeapSort.outputLocation );
                write.writeLine(HeapSort.outputLocation );
            }
            
            readFile.close();
        } catch (IOException ioex) {
            ioex.printStackTrace();
        }
    }
    
    /*
     * Main initiates the program with command line arg inputs
     * arg[0] is the output file
     * All others are input files
     */
    public static void main(String[] args)
    {
        ReadFile read = new ReadFile();
        HeapSort.outputLocation = args[0];

        for (int n = 1; n < args.length; n++) {
            read.readFile(args[n]);
        }
    }
}
