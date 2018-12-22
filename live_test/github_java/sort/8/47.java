package quicksort;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.logging.Level;
import java.util.logging.Logger;



public class QuickSort implements Runnable {
    public static int c;
    public static int[] a;
    public static String[][] s;
    public static LinkedBlockingQueue<int[]> queue;
    public static AtomicInteger queued = new AtomicInteger(1);
    
    @SuppressWarnings("empty-statement")
    public static void main(String[] args) {
        QuickSort qs = new QuickSort();
        
        QuickSort.c = Integer.parseInt(args[1]);
        String file_in = args[0];
        String file_out = args[3];
        int thread_count = Integer.parseInt(args[2]);
        
        try {      
            qs.load(file_in);
        } catch (IOException ex) {
            Logger.getLogger(QuickSort.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        List<Thread> threads = new ArrayList<Thread>();
        QuickSort.queue = new LinkedBlockingQueue<int[]>();
       
        for (int n = 0; n < thread_count; n++) {
            Thread worker = new Thread(new QuickSort());
            worker.setName(String.valueOf(n));
            worker.start();
            threads.add(worker);
        }
        
        QuickSort.queue.offer(new int[] {0,QuickSort.a.length-1});
        
        while (QuickSort.queued.get() > 0);
        
        for ( Iterator<Thread> it = threads.iterator(); it.hasNext(); ) {
            it.next().interrupt();
        }
        
        try {        
            qs.save(file_out);
        } catch (IOException ex) {
            Logger.getLogger(QuickSort.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    public int load(String filename) throws IOException {
        FileReader fr = new FileReader(filename);
        BufferedReader br = new BufferedReader(fr);
        String row = br.readLine();
        ArrayList list = new ArrayList();
        while(row != null) {
            list.add(row);
            row = br.readLine();        
        }
        Object[] x = list.toArray();
        QuickSort.a = new int[x.length];
        QuickSort.s = new String[x.length][];
        for (int i = 0; i < x.length; i++) {
            QuickSort.a[i] = i;
            QuickSort.s[i] = ((String) x[i]).split("\t",-1);
        }
        br.close();
        return x.length;
    }
    
    public void save(String filename) throws IOException {
        FileWriter fw = new FileWriter(filename);
        for (int i = 0; i < QuickSort.a.length; i++) {
            String x = "";
            for (int j = 0; j < QuickSort.s[QuickSort.a[i]].length; j++) {
                x += QuickSort.s[QuickSort.a[i]][j] + "\t";
            }
            x = x.substring(0,x.length()-1);
            fw.write(x + "\n");
        }
        fw.close();
    }
    
    public void print_a() {
        for (int n = 0; n < QuickSort.a.length; n++) {
            System.out.print(QuickSort.s[QuickSort.a[n]][0] + "|");
        }
    }
    
    public void swap(int one, int two) {
        int tmp = QuickSort.a[one];
        QuickSort.a[one] = QuickSort.a[two];
        QuickSort.a[two] = tmp;
    }   
    
    @SuppressWarnings("empty-statement")
    public void sort(int left, int right) {
        if (right > left) {
            String pivot = QuickSort.s[QuickSort.a[right]][QuickSort.c];
            int i=left-1, j=right, tmp;
            for (;;) {
                String rs = QuickSort.s[QuickSort.a[right]][QuickSort.c];
                while(QuickSort.s[QuickSort.a[++i]][QuickSort.c].compareTo(rs) < 0);
                while(QuickSort.s[QuickSort.a[--j]][QuickSort.c].compareTo(rs) > 0 && j > i);
                if(i >= j) break;
                this.swap(i,j);
            }
            this.swap(i,right);
            QuickSort.queue.offer(new int[] {i+1,right});
            QuickSort.queue.offer(new int[] {left,i-1});
            QuickSort.queued.addAndGet(2);
        }
        QuickSort.queued.decrementAndGet();
    }

    @Override
    public void run() {
        while (true) {
            try {
                
                int[] vars = QuickSort.queue.take();
                this.sort(vars[0],vars[1]);
            } catch (InterruptedException e) {
                
                return;
            }
        }       
    }
}
