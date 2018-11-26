import java.io.IOException;
import java.io.PrintWriter;
import java.text.NumberFormat;
import java.util.Stack;

/**
 * This program lists the steps to solve the Tower of Hanoi problem with 3 pegs
 * The number of disks to start with can be input as an argument.
 * The steps are printed on screen up to 10 disks. For more than that, the steps
 * are written to a file as the output grows exponentially with the number of disks
 * 
 * The solution to Tower of Hanoi takes exponential time 
 * Big O(n) = 2 ^ n 
 *
 */
public class TowerOfHanoi {
    private class HanoiStack extends Stack<Integer> {
        private static final long serialVersionUID = 6707553568893645305L;
        @Override
        public Integer push(Integer element) {
            // good to check, but considerably affects runtime during high volume disk swaps
            // if (this.size()>0 && element > this.peek()) {
            //    throw new RuntimeException("Push error: trying to push " + element + " on top of " + this.peek());
            // }
            // every push is counted as a move in solving the problem 
            TowerOfHanoi.this.stepCount++;
            Integer i = super.push(element);
            // display the state after every PUSH move
            TowerOfHanoi.this.printStacks();
            return i;
        }
    }
    
    public HanoiStack source = new HanoiStack();
    public HanoiStack dest = new HanoiStack();
    public HanoiStack swap = new HanoiStack();
    private String filename;
    private PrintWriter out;
    private int stepCount;
    
    public void transfer(int count, HanoiStack source, HanoiStack dest, HanoiStack swap) throws IOException{
        // for more than 2 disks
        // 1. move all but the last disk from source to swap peg
        // 2. move the last disk from source to destination peg
        // 3. move back the swapped disks to destination peg
        if (count > 2) {
            transfer (count-1, source, swap, dest);
            dest.push(source.pop());
            transfer (count-1, swap, dest, source);
        }
        // for 2 or less disks, move them right away without recursion
        switch (count) {
        case 0: break;
        case 1: dest.push(source.pop());
                break;
        case 2: swap.push(source.pop());
                dest.push(source.pop());
                dest.push(swap.pop());
                break;
        }
    }
    
    public void printStacks () {
        out.print("Step " + stepCount + "\tSource :\t");
        for (int i=0; i<this.source.size(); i++) {
            out.print(this.source.elementAt(i) + " ");
        }
        out.print("\tDestination :\t");
        for (int i=0; i<this.dest.size(); i++) {
            out.print(this.dest.elementAt(i) + " ");
        }
        out.print("\tSwap :\t");
        for (int i=0; i<this.swap.size(); i++) {
            out.print(this.swap.elementAt(i) + " ");
        }
        out.println(" ");
    }
    
    public static void main(String[] args) throws IOException {
        int count = 8; // default, if no argument is provided for the count
        int SYS_OUT_LIMIT = 10; // limit after which output will be written to a file
        TowerOfHanoi tower = new TowerOfHanoi();
        
        if (args.length>0) {
            try {
                count = Integer.parseInt(args[0]);
            } catch (NumberFormatException e) {
                System.out.println("Invalid input for count. Defaulting to " + count);
            }
        }
        
        if (count > SYS_OUT_LIMIT) {
            System.out.println(count + " disks !! That's gonna take " 
                + NumberFormat.getIntegerInstance().format((int)Math.pow(2, count) - 1) 
                + " steps. Output will be written to a file. Here we go ...");
            tower.filename = System.getProperty("java.io.tmpdir") + "towerOfHanoi.txt";
            tower.out = new PrintWriter(tower.filename);
        } else {
            tower.out = new PrintWriter(System.out, true);
        }
        
        // set up the disks on the source peg to start
        for (int i=count; i>0; i--) {
            tower.source.push(new Integer(i));
        }
        tower.stepCount = 0; // reset the step count (would have been incremented when the source peg was set up)
        
        long start = System.currentTimeMillis();
        tower.out.println("... Start ...");

        tower.transfer(count, tower.source, tower.dest, tower.swap);
        
        tower.out.println("... End ...");
        long end = System.currentTimeMillis();
        long elapsed = end - start;
        long min = elapsed/60000;
        long sec = (elapsed/1000)%60;
        tower.out.println("Elapsed Time : " + (min>0 ? min + " mintue(s) " : "") 
            + (sec>0 ? sec + " second(s)" : elapsed + " milliseconds"));
        
        tower.out.println("Total Steps : " + NumberFormat.getIntegerInstance().format(tower.stepCount));
        tower.out.flush();
        tower.out.close();
        if (count > SYS_OUT_LIMIT) {
            System.out.println("Output available at " + tower.filename);
        }
    }
}
