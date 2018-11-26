/**
 * CS 241: Data Structures and Algorithms II
 * Professor: Edwin Rodr&iacute;guez
 *
 * Programming Assignment #1
 *
 *
 * @author Edgar Ruiz
 */
package edu.csupomona.cs.cs241.prog_assgmnt_1;

import java.util.Arrays;
/*
 * This class is used to test Exercise 1 of assignment:
 * The getSortedContents method should, internally, 
 * transform the heap into its array representation, 
 * and the perform Heap-Sort on it, then return the array as the result. 
 */
public class ExerciseOne {
	public static void main(String[] args){
	NodeHeap<Integer> myHeap = new NodeHeap<Integer>(Heap.MODE.MAX);
	
	myHeap.add(20);
	myHeap.add(1);
	myHeap.add(5);
	myHeap.add(100);
	myHeap.add(45);
	myHeap.add(420);
	myHeap.add(65);
	myHeap.add(84);
	
	System.out.println("Before Heap-Sort: \n" + Arrays.toString(myHeap.toArray()));
	System.out.println("After Heap-Sort: \n" + Arrays.toString(myHeap.getSortedContents()));
	
	}
}
