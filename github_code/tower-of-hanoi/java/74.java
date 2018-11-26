package HanoiTower;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class HanoiTower {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        List<String> a = new ArrayList<>();
        List<String> b = new ArrayList<>();
        List<String> c = new ArrayList<>();
        String temp = scanner.next();
        while (!temp.equals("stop")) {
            a.add(temp);
            temp = scanner.next();
        }
        hanoi(a.get(0), a, b, c);
        System.out.println(c.toString());
    }

    //TODO: variable names should contain more information, just type anme is not enough
    //TODO: stack will be better
    private static void hanoi(String string, List<String> home, List<String> helper, List<String> destination) {
        int indexOfString = home.indexOf(string);
        if (indexOfString == home.size() - 1) {
            move(string, home, destination);
        } else {
            String childString = home.get(indexOfString + 1);
            hanoi(childString, home, destination, helper);
            move(string, home, destination);
            hanoi(childString, helper, home, destination);
        }
    }

    private static void move(String string, List<String> from, List<String> to) {
        to.add(string);
        from.remove(string);

//        to.add(from.pop());//TODO

    }
}
