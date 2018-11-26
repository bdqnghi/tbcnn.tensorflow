/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package selectionsortjava;

import java.util.Scanner;
import java.util.List;
import java.util.ArrayList;
/**
 *
 * @author Stefano D'Alessio
 */
public class SelectionSortJava {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        
        Scanner input = new Scanner(System.in);
        List<Integer> numbers = new ArrayList<Integer>();
        
        System.out.println("---This is a simple program which takes a list of integer as input and order them from the smallest to the biggest");
        System.out.println("---Enter a new integer each time is requested. To terminate insert 'q'");
        
        System.out.printf("Insert the first character: ");
        String next = input.next();
        while(isInteger(next)) {
            numbers.add(Integer.parseInt(next));
            System.out.printf("Insert the next character: ");
            next = input.next();
        }
        
        if(!(next.equals("q"))) {
            System.out.println("---ERROR: Unknown command. Program exited");
            return;
        }
        
        printArray(numbers);
    }
    
    
    private static boolean isInteger(String str) {
        try {
            Integer.parseInt(str);
            return true;
        } catch (NumberFormatException e){}
        return false;
    }
    
    
    private static void printArray(List<Integer> numbers) {
        System.out.printf("Inserted numbers: {");
        for (Integer number: numbers)
            System.out.printf(" %s ", Integer.toString(number));
        System.out.println("}");
    }
}
