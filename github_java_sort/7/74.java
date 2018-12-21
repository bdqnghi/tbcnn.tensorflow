import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;



public class ReadFile {

    
    public void readFile(String inputFile)
    {
        try {
                HeapSort heap = new HeapSort();
                WriteFile write = new WriteFile();
                int inputSize = 50;
                BufferedReader readFile = new BufferedReader(
                                new FileReader(new File(inputFile)));
                String nextInput = readFile.readLine();
                
                
                
                
                if (nextInput.contains(" ")) 
                {
                    inputSize = Integer.parseInt(nextInput.trim());
                }
            
            
            
                
                int[] inputArr = new int[inputSize];    
                int[] inputCopy1 = new int[inputSize];  
                int[] inputCopy2 = new int[inputSize];  
                int[] inputCopy3 = new int[inputSize];  
                int[] inputCopy4 = new int[inputSize];  

            
                
                
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
            
                
                int index = 0;
                for (int each : inputArr) {
                    inputCopy1[index] = each;
                    inputCopy2[index] = each;
                    inputCopy3[index] = each;
                    inputCopy4[index] = each;
                    index++;
                }
                
                

                
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
            
                
                long startClock = System.nanoTime();
                heap.heap_sort(inputArr, inputSize);
                long endClock = System.nanoTime();
                long timeElapsed = endClock-startClock;

                
                
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
            


            
            
            
            ShellSort shell = new ShellSort();
            int knuthArr[] = new int[20];
            int gap = 0;
            int elem = 0;
            for (elem = 0; elem < 20; elem++) {
                gap = (3 * gap) + 1;
                knuthArr[elem] = gap;
            }
            

            
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

            
            
            startClock = System.nanoTime();
            shell.sort(knuthArr, inputCopy2);
            endClock = System.nanoTime(); 
            timeElapsed = endClock - startClock;
            
            
            
            
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
            
            
            
            startClock = System.nanoTime(); 
            shell.sort(primeArr, inputCopy3);
            endClock = System.nanoTime(); 
            timeElapsed = endClock - startClock; 
            
            
            
            
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
    
    
    public static void main(String[] args)
    {
        ReadFile read = new ReadFile();
        HeapSort.outputLocation = args[0];

        for (int n = 1; n < args.length; n++) {
            read.readFile(args[n]);
        }
    }
}
