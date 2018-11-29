
package dynamicprogramming;
import java.util.Stack;

// complexity is 2 ^ n-1
public class TowerOfHanoi {
//     int noOfRings = 4;
    Stack<Integer> s = new Stack<Integer>();
      TowerOfHanoi buf;
      TowerOfHanoi dest;
    private TowerOfHanoi()
    {
    
    }
    
    public TowerOfHanoi(int noOfRings)
    {
        for (int i = noOfRings; i > 0; i--)
         s.push(i);
	   
	   
	   buf = new TowerOfHanoi();
	   dest = new TowerOfHanoi();
	   recRingMovement(noOfRings, buf, dest);
	 
	  while(!dest.s.isEmpty())
	       System.out.println("Ring " + dest.s.pop());
    }
    
    private void moveRingToDest(TowerOfHanoi dest)
    {
        if (!this.s.empty())
        {
            dest.s.push(this.s.pop());
        }
    }
    
    private void recRingMovement(int i, TowerOfHanoi buf, TowerOfHanoi dest) {
        
        if (i < 0)
            return;
        
        recRingMovement(i - 1, dest, buf);
        moveRingToDest(dest);
        buf.recRingMovement(i - 1, this, dest);
    }
}
