package com.puzzle;

/**
 * Created by mbiswas on 6/7/18.
 */

//Problem: https://www.geeksforgeeks.org/c-program-for-tower-of-hanoi/
public class TowerOfHanoi {


    public static void towerofhanoi(int n, char from_road, char to_rod , char help_rod){
        if(n == 1){
            System.out.println("Move Disc 1 from " +from_road +" to " +to_rod);
            return;
        }

        towerofhanoi(n-1 , from_road, help_rod , to_rod);
        System.out.println("Move Disc " +n +" from " +from_road +" to " +to_rod);
        towerofhanoi(n-1, help_rod, to_rod, from_road);
    }

    //best : https://www.youtube.com/watch?v=5_6nsViVM00

    public static void towerofhanoi2(int n, char start, char middle , char end){
        if(n == 1){
            System.out.println(start +"->" +end);
            return;
        }

        towerofhanoi2(n-1,start,end,middle);
        towerofhanoi2(1, start,middle,end);
        towerofhanoi2(n-1, middle,start,end);
    }


    public static void towerofhanoi3(int n, char start, char middle , char end){
        if(n == 1){
            System.out.println("Moving ring 1 "+start +"->" +end);
            return;
        }

        towerofhanoi3(n-1,start,end,middle);
        System.out.println("Moving ring " +n +" "+start +"->" +end);
        towerofhanoi3(n-1, middle,start,end);
    }

    public static void main(String[] args) {

        towerofhanoi(3, 'A', 'C', 'B');
        towerofhanoi2(3, 'A', 'B', 'C');
        towerofhanoi3(3, 'A', 'B', 'C');

    }
}
