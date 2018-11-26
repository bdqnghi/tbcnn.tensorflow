package DynamicProgramming;

import java.util.Arrays;

/**
 * Created by vikram on 9/12/16.
 *
 * Objec­tive: Given a rod of length n inches and a table of prices pi, i=1,2,…,n,
 * write an algo­rithm to find the max­i­mum rev­enue rn obtain­able by cut­ting up the rod and sell­ing the pieces.


 od lengths are inte­gers and For i=1,2,…,n we know the price pi of a rod of length i inches

 Exam­ple:

 Length	1	2	3	4	5	6	7	8	9	10
 Price	1	5	8	9	10	17	17	20	24	30

 for rod of length: 4
 Best Price for rod of length 4: 10

 */
public class RodCutting {


    public static void main(String[] args) {
        int[] arr= {1,5,8,9};

        RodCutting rodCutting= new RodCutting();
        System.out.println(rodCutting.maxPriceRod(arr,4));

    }

    public int maxPriceRod(int[] rodPrice,int n)
    {
        //Create a array of  n+1 size (0 -4)
        int[] maxRodPrices= new int[n+1];


        //for loop to put values for each rod

        maxRodPrices[0]=0;

        for (int i=1;i<=n;i++)
        {
            int maxPrice =-1;
            int currPrice =0;

            //iterating for all the options available for a given length
            //putting j<i either we need to keep a check after for loop or j<i since given length should not
            // be greater than iterating loop
            for (int j=0;j<i;j++)
            {

                currPrice= rodPrice[j]+ maxRodPrices[i-j-1];
                if (maxPrice<currPrice)
                {
                    maxPrice=currPrice;
                    maxRodPrices[i]=maxPrice;
                }

            }




        }

        return maxRodPrices[maxRodPrices.length-1];


    }
}
