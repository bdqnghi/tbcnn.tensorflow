public class TowerOfHanoi {
    private static int num = 0;

    public static void moveDisk(int n, String fromTow, String toTow, String auxTow) {
        num++;
        if (n == 1)
            System.out.println("Move disk " + n + " from " + fromTow + " to " + toTow
                + ".");
        else {
            moveDisk(n - 1, fromTow, auxTow, toTow);
            System.out.println("Move disk " + n + " from " + fromTow + " to " + toTow
                + ".");    //表示将n号盘从form 挪到 to。
            moveDisk(n - 1, auxTow, toTow, fromTow);
        }
    }

    public static int getNum() {
        return num;
    }
}