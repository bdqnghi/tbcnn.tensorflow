package com.problem1.recursion;

import java.util.Scanner;

/**
 * Created by sowmyaparameshwara on 3/11/17.
 *
 * https://www.tutorialspoint.com/data_structures_algorithms/tower_of_hanoi.htm
 *
 * http://www.javawithus.com/programs/towers-of-hanoi
 */
public class TowerOfHanoi {

    public static void main(String[] args){
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        tower(n,"source","aux","dest");
    }

    private static void tower(int n, String source, String aux, String dest) {
        if(n==1)
            System.out.println(source+"==>"+dest);
        else{
            tower(n-1,source,dest,aux);
            System.out.println(source+"==>"+dest);
            tower(n-1,aux,source,dest);
        }
    }
}

