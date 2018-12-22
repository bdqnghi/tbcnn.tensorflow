import java.util.*;

class BSorting{
    public static void main(String[]args){
        Scanner sc = new Scanner(System.in);
        int[] numbers = new int[7];

        System.out.println("Enter numbers:");
        for(int i = 0; i <= numbers.length - 1; i++){
            numbers[i] = sc.nextInt();
        }

        for(int i = 0; i <= numbers.length - 1; i++){
            System.out.print(numbers[i] + " ");
        }
        System.out.println();


        for(int i = 0; i <= numbers.length - 1; i++){
            for(int j = 0; j < numbers.length - 1; j++){
                if(numbers[j] > numbers[j + 1]){
                    int temp = numbers[j];
                    numbers[j] = numbers[j + 1];
                    numbers[j + 1] = temp;
                }
            }
            for(int k = 0; k <= numbers.length - 1; k++){
                System.out.print(numbers[k] + " ");
            }
        }

        for(int i = 0; i <= numbers.length - 1; i++){
            System.out.print(numbers[i] + " ");
        }


    }
}
