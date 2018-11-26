package com.amid88.runners.homework;

import com.amid88.app.homework.lesson9.MultiplyArray;

import static com.amid88.runners.homework.Lesson10Runner.scannerInputAny;

/**
 * Created by dstrashko on 12/8/16.
 */
public class Lesson9Runner {

    public static void main(String[] args) {

        boolean parameterFlag = true;
        int[] testArray = {2,17,9,12,54,37,0};


        do {
            int parameter = scannerInputAny("\nWelcome to program 'Lesson9'. Please choose one of the options below: \n" + "\t"+
                    "1. Bubble-sort ascending\n" +"\t" +
                    "2. Bubble-sort descending\n" +"\t" +
                    "3. Selected-sort ascending\n" + "\t" +
                    "4. Selected-sort descending\n" + "\t" +
                    "5. Generate random matrix\n" + "\t" +
                    "6. Generate multiplication table\n" + "\t" +
                    "0. Exit from the program");
            switch (parameter) {
                case 0: parameterFlag = false;
                    System.out.println("Thank you for using our program. Bye!");
                    break;
                case 1:
                    MultiplyArray.printArray(MultiplyArray.bubbleSortAscending(testArray));
                    break;
                case 2:
                    MultiplyArray.printArray(MultiplyArray.bubbleSortDescending(testArray));
                    break;
                case 3:
                    MultiplyArray.printArray(MultiplyArray.selectionSortAscending(testArray));
                    break;
                case 4:
                    MultiplyArray.printArray(MultiplyArray.selectionSortDescending(testArray));
                    break;
                case 5:
                    MultiplyArray.printArray(MultiplyArray.generateRandomMatrix());
                    System.out.println("The maximum element of matrix is: " + MultiplyArray.maxElementOfMatrix);
                    break;
                case 6:
                    int[][] multiplicationTable = MultiplyArray.multiplicationTable(15);
                    for(int i = 0; i < multiplicationTable[0].length; i++){
                        System.out.println(multiplicationTable[0][i] + " * " +
                                multiplicationTable[1][i] + " = " + multiplicationTable[2][i]);
                    }
                    break;
                default:
                    parameterFlag = true;
                    System.out.println("Wrong input");
                    break;
            }
        } while (parameterFlag == true);


    }
}
