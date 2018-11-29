package algorithm;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

/**
 * Created by wajian on 2016/8/30.
 * java implement of HanoiTower algorithm
 * http://www.phpxs.com/code/1002217/
 */
public class HanoiTower {
    public static void main(String[] args) {
        int n = 0;
        BufferedReader buf;
        buf = new BufferedReader(new InputStreamReader(System.in));

        System.out.print("please input the number of plate:");
        try {
            n = Integer.parseInt(buf.readLine());
        } catch (NumberFormatException | IOException e) {
            e.printStackTrace();
        }
        HanoiTower hanoi = new HanoiTower();
        hanoi.move(n, 'A', 'B', 'C');
    }

    /**
     * three stake
     */
    private void move(int n, char a, char b, char c){
        if (n == 1) {
            System.out.println("plate " + n + " is moved from " + a + " to " + c);
        } else {
            move(n - 1, a, c, b);
            System.out.println("plate " + n + " is moved from " + a + " to " + c);
            move(n - 1, b, a, c);
        }
    }
}
