import java.util.*;

class Sorting{
    public static void main(String[]args){
        Scanner sc = new Scanner(System.in);
        
        int[] numbers = new int[6];
        System.out.println("Enter Array:");
        for(int i = 0; i <= numbers.length - 1; i++){
            numbers[i] = sc.nextInt();
        }
        sc.close();

        for(int i = 0; i <= numbers.length - 1; i++){
            System.out.print(numbers[i] + " ");
        }
        System.out.println();

        for(int i = 0; i <= numbers.length - 1; i++){
            int minIndex = i;
            for(int j = i; j <= numbers.length - 1; j++){
                if(numbers[minIndex] > numbers[j]){
                    minIndex = j;
                }
            }
            int temp = numbers[i];
            numbers[i] = numbers[minIndex];
            numbers[minIndex] = temp;
        } 

        for(int i = 0; i <= numbers.length - 1; i++){
            System.out.print(numbers[i] + " ");
        }
    }
}