package mypack;

import java.util.Scanner;

public class radixsort{
    int[] a;
    public radixsort(){}
    public radixsort( int[] arr ){
        a = arr;
        sort();
    }
    void init( Scanner inp ){
        int n = inp.nextInt();
        int i = 0;
        a = new int[n];
        while(i<n){
            a[i] = inp.nextInt();
            ++i;
        }
    }
    int maxarr(){
        int max = a[0];
        int i = 1;
        while( i<a.length ){
            if( max<a[i] ){
                max = a[i];
            }
            ++i;
        }
        return max;
    }
    void sort(){
        //queue<Integer> bucket;
        //bucket = new queue<Integer>();//cai xo
        arrlist<queue<Integer>> bucket = new arrlist<queue<Integer>>( 10 );
        int i = 0;
        while( i<10 ){
            bucket.pos(i).element = new queue<Integer>();
            ++i;
        }
        int max = maxarr();
       // System.out.println("max="+max);
        int radix = 1;
        int j;
        while( max!=0 ){
            radix *= 10;
            i = 0;
            while( i<a.length ){
                bucket.pos( (a[i]/(radix/10))%10 ).element.push( a[i] );
                ++i;
            }
            i = 0;
            j = 0;
            while( i<10 ){
                while( !bucket.pos(i).element.isEmpty() ){
                    a[j] = bucket.pos(i).element.popback();
                    j++;
                }
                ++i;
            }
            max/=10;
        }
    }
    public void display(){
        int i = 0;
        while( i<a.length ){
            System.out.print(a[i]+" ");
            ++i;
        }
        System.out.println();
    }
    public static void main( String[] args ){
        /*int[] a = {23,11,13,41,73,55,64,99,8,7,8,2,1,11,11,12,21,24,87,56,44,23,12};
        radixsort temp = new radixsort(a);
        //temp.sort();
        temp.display();*/
        return;
    }
}