import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Deque;
import java.util.Iterator;
import java.util.List;

public class TowerOfHanoi {

    public static void main(String[] args) throws Exception {
        new TowerOfHanoi();
    }

    int N = 4;       
    Hanoi hanoi;
    List<String> list = new ArrayList<String>();  

    public TowerOfHanoi() throws Exception {
        hanoi = new Hanoi(N);
        list.add("(init) " + hanoi.toString());    

        recursive(N, 0, 2);   

        int i = 0;
        for (String e : list) {
            System.out.println((i++) + " : " + e);
        }
    }

  
    void recursive(int n, int from, int to) {
        if (n > 0) {
            int work = 3 - (from + to);
            recursive(n - 1, from, work);
            hanoi.move(from, to);
            String log = String.valueOf((char)('A' + from)) + " -> " + String.valueOf((char)('A' + to));
            log += " " + hanoi.toString();
            list.add(log);  
            recursive(n - 1, work, to);
        }
    }

   
    class Hanoi {
        int n;   

        @SuppressWarnings("unchecked")
        Deque<Integer>[] stack = new Deque[3];    
        {
            for (int i = 0; i < 3; i++) {
                stack[i] = new ArrayDeque<Integer>();
            }
        }

        public Hanoi(int n) {
            this.n = n;

            while (n > 0) {
                push(0, n--);  
            }
        }

        void push(int to, int no) {
            stack[to].addLast(no);
        }


        int pop(int from) {
            return stack[from].removeLast();
        }

        void move(int from, int to) {
            push(to, pop(from));
        }

        @Override
        public String toString() {
            final StringBuilder sb = new StringBuilder(n * 9);
            for (int i = 0; i < 3; i++) {
                if (i > 0) {
                    sb.append(",");
                }
                if (stack[i].isEmpty()) {
                    sb.append("[]");
                    continue;
                }

                int j = 0;
                Iterator<Integer> it = stack[i].iterator();
                sb.append("[");
                while (it.hasNext()) {
                    int v = it.next();
                    if (v == 0) {
                        break;
                    }
                    if (j++ > 0) {
                        sb.append(",");
                    }
                    sb.append(v);
                }
                sb.append("]");
            }
            return sb.toString();
        }
    }
}