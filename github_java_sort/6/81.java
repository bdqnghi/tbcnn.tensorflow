

import java.io.*;
import java.math.*;
import java.util.ArrayList;
import java.util.*;


public class Radix {


    public static void bucketSort(Integer[][] a, int maxVal, int pass){

        LinkedList<Integer[]> temp0 = new LinkedList<Integer[]>();
        LinkedList<Integer[]> temp1 = new LinkedList<Integer[]>();


        for(int i = 0; i < maxVal; i++){

            if (a[i][pass] == 0){
                temp0.add(a[i]);

            }else{
                temp1.add(a[i]);

            }

        }


        int counter = 0;
        ListIterator<Integer[]> itr0 = temp0.listIterator();
        ListIterator<Integer[]> itr1 = temp1.listIterator();

        while (itr0.hasNext()) {

          a[counter] = itr0.next();
          counter++;
        }

        while (itr1.hasNext()) {

            a[counter] = itr1.next();
            counter++;
        }





    }




    public static void main(String[] args){
        System.out.println("Welcome to Eric's Radix sort Algorithm");

        System.out.print("\nEnter the number of elements you wish to sort\t");

        Scanner input = new Scanner(System.in);
        int numElem;

        try{
            String numElemS = input.nextLine();
            numElem = Integer.parseInt(numElemS);
        }catch (Error e){
            System.out.println("\nIncorrect input -- Setting to 25");
            numElem = 25;
        }catch (NumberFormatException f){
            System.out.println("\nIncorrect input -- Setting to 25");
            numElem = 25;
        }



        int longest = 0;

        Integer ranNum[]   = new Integer[numElem];


        String strArr[] = new String[numElem];


        for(int i = 0; i< numElem; i++){
            ranNum[i] = (int) (Math.random()*numElem*10 + 1);

            String bin = Integer.toBinaryString(ranNum[i]);



            if (bin.length() >= longest){
                longest = bin.length();
            }


            strArr[i] = bin;

        }

        System.out.println();
        

        Integer binArr[][] = new Integer[numElem][longest];


        System.out.println("\nBinary encoding of generated numbers\n");

        for (int i=0; i<numElem; i++){
            char[] binString = strArr[i].toCharArray();

            String encode = "";
            int count = 0;
            for (int j = (longest-1); j>=0;j--){
                if ((binString.length-1) < j) {
                    binArr[i][j] = 0;
                    encode += 0;
                }else {
                    binArr[i][j] = Character.getNumericValue(binString[count]);
                    encode += binArr[i][j].toString();
                    count++;
                }

           }

           System.out.println(i + "\t" + encode + "\t -- " + Integer.parseInt(encode, 2));

        }


        for(int j= 0; j<longest; j++){
            System.out.println();
            System.out.println("\nPass " + (j+1));
            bucketSort(binArr, numElem, j);



                for (int i = 0; i < numElem; i++) {

                    System.out.print("\n" + i + "\t");

                    String num = "";
                    for (int h = (longest - 1); h >= 0; h--) {
                        System.out.print(binArr[i][h]);
                        num += binArr[i][h];
                    }

                    int foo = Integer.parseInt(num, 2);
                    System.out.print("\t" + " " + "\t" + foo);

                }



        }



    }


}


