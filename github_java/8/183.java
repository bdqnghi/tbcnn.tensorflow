package by.it.group573601.grigoreva.lesson07;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStream;
import java.util.Arrays;
import java.util.Scanner;

/*
Задача на программирование: расстояние Левенштейна
    https://ru.wikipedia.org/wiki/Расстояние_Левенштейна
    http://planetcalc.ru/1721/

Дано:
    Две данных непустые строки длины не более 100, содержащие строчные буквы латинского алфавита.

Необходимо:
    Решить задачу МЕТОДАМИ ДИНАМИЧЕСКОГО ПРОГРАММИРОВАНИЯ
    Рекурсивно вычислить расстояние редактирования двух данных непустых строк

    Sample Input 1:
    ab
    ab
    Sample Output 1:
    0

    Sample Input 2:
    short
    ports
    Sample Output 2:
    3

    Sample Input 3:
    distance
    editing
    Sample Output 3:
    5

*/

public class A_EditDist {

    String ar1;
    String ar2;
    int[][] distance;

    private int editDistanceTopDown(int i, int j){
        if(distance[i][j] == Integer.MAX_VALUE){
            if(i==0)
                distance[i][j] = j;
            else if(j==0)
                distance[i][j] = i;
            else{
                int ins = editDistanceTopDown(i, j-1) + 1;
                int del = editDistanceTopDown(i-1, j) + 1;
                int sub = editDistanceTopDown(i-1, j-1) +
                        ((ar1.charAt(i - 1) == ar2.charAt(j - 1)) ? 0:1);
                distance[i][j] = Math.min(Math.min(ins, del), sub);
            }
        }
        return distance[i][j];
    }

    int getDistanceEdinting(String one, String two) {
        //!!!!!!!!!!!!!!!!!!!!!!!!!     НАЧАЛО ЗАДАЧИ     !!!!!!!!!!!!!!!!!!!!!!!!!
        ar1 = one;
        ar2 = two;
        int n = ar1.length();
        int m = ar2.length();
        distance = new int[n+1][m+1];
        for(int[] row:distance)
            Arrays.fill(row, Integer.MAX_VALUE);
        int i = n;
        int j = m;

        //!!!!!!!!!!!!!!!!!!!!!!!!!     КОНЕЦ ЗАДАЧИ     !!!!!!!!!!!!!!!!!!!!!!!!!
        return editDistanceTopDown(i, j);
    }


    public static void main(String[] args) throws FileNotFoundException {
        String root = System.getProperty("user.dir") + "/src/";
        InputStream stream = new FileInputStream(root + "by/it/a_khmelev/lesson07/dataABC.txt");
        A_EditDist instance = new A_EditDist();
        Scanner scanner = new Scanner(stream);
        System.out.println(instance.getDistanceEdinting(scanner.nextLine(),scanner.nextLine()));
        System.out.println(instance.getDistanceEdinting(scanner.nextLine(),scanner.nextLine()));
        System.out.println(instance.getDistanceEdinting(scanner.nextLine(),scanner.nextLine()));
    }
}

