import comp102x.IO;

public class TowerOfHanoi {
    int step;
    
    void towers(int num, int from, int to) {
        int temp = 6 - from - to;
        if (num == 1){
            IO.outputln(++step + ": move disk 1 from " + from + " to " + to);
        } else {
            towers(num-1, from, temp);
            IO.outputln(++step + ": move disk " + num + " from " + from + " to " + to);
            towers(num-1, temp, to);
        }
    }
    
    void demo(int num) {
        step = 0;
        towers(num, 1, 3);
    }

}