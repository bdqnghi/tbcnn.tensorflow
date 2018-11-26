/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package sketch;

import java.util.ArrayDeque;
import java.util.Deque;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Stack;
import java.util.concurrent.CountDownLatch;

import sun.org.mozilla.javascript.internal.ast.ForInLoop;



/**
 *
 * @author m.alhabshi
 */
public class TowerOfHanoi {

    /**
     * @param args the command line arguments
     */
    /**
     * @param args
     */
    public static void main(String[] args) {

//        solution1();
//    	solution2();
    	
//    	TowerOfHanoi.move(5, 1, 3);
    	
//    	solution3();
    	
    	
    }

    
	private static void solution3() {
		Deque<Integer> pegA = new ArrayDeque();
        pegA.add(Integer.valueOf(1));
        pegA.add(Integer.valueOf(2));
        pegA.add(Integer.valueOf(3));
        
        Deque<Integer> pegB = new ArrayDeque();
        Deque<Integer> pegC = new ArrayDeque();
        
        int disks = pegA.size();
        
        while(pegC.size() < disks){
        	System.out.println("LOOP");
        	move(pegA, pegC);
        	move(pegA, pegB);
        	move(pegC, pegB);
        }
        
        done(pegC);
	}

    
	private static void move(Deque<Integer> from, Deque<Integer> to) {
		if(!from.isEmpty())
			to.push(from.pop());
		else if(!to.isEmpty())
			from.push(to.pop());
		else
			return;
	}

	private static void solution2() {
		Deque<Integer> pegA = new ArrayDeque();
        pegA.add(Integer.valueOf(1));
        pegA.add(Integer.valueOf(2));
        pegA.add(Integer.valueOf(3));
        
        Deque<Integer> pegB = new ArrayDeque();
        Deque<Integer> pegC = new ArrayDeque();
        
        int disks = pegA.size();
        
        while(pegC.size() < disks){
        	System.out.println("LOOP");
        	if(pegA.size() == 1){
        		pegB.push(pegA.pop());
        	}else{
		        while(pegA.size() > 1){
		        	pegB.push(pegA.pop());
		        }
        	}
        	
	        if(!pegA.isEmpty())
	        	pegC.push(pegA.pop());
	        
	        if(pegB.size() == 1){
	        	pegC.push(pegB.pop());
	        }else{
		        while(pegB.size() > 1){
		        	pegC.push(pegB.pop());
		        }
	        }
        }
        
        done(pegC);
	}

	private static void done(Deque<Integer> peg) {
		System.out.println("DONE!");
        for (Integer i : peg) {
			System.out.println(i);
		}
	}

	private static void solution1() {
		HashMap hm = new HashMap();
        CountDownLatch cdl = new CountDownLatch(10);
        Deque<Integer> d1 = new ArrayDeque();
        d1.add(Integer.valueOf(1));
        d1.add(Integer.valueOf(2));
        d1.add(Integer.valueOf(3));
        d1.add(Integer.valueOf(4));
        
        Deque<Integer> d2 = new ArrayDeque();
        Deque<Integer> d3 = new ArrayDeque();
        
        int lastMoved = 0;
        
        for (Iterator<Integer> it = d1.iterator(); it.hasNext();) {
            System.out.println(it.next());
        }
        System.out.println("------");
        while(d3.size() < 4){
            if(d2.isEmpty() || isBigger(d2.peek(), d1.peek()) && lastMoved != 1){
                d2.addFirst(d1.pop());
                lastMoved = 1;
            }else if(d3.isEmpty() || isBigger(d3.peek(), d1.peek()) && lastMoved != 1){
                d3.addFirst(d1.pop());
                lastMoved = 1;
            }else if(d3.isEmpty() || isBigger(d3.peek(), d2.peek()) && lastMoved != 2){
                d3.addFirst(d2.pop());
                lastMoved = 2;
            }else if(d1.isEmpty() || isBigger(d1.peek(), d2.peek()) && lastMoved != 2){
                d1.addFirst(d2.pop());
                lastMoved = 2;
            }else if(d1.isEmpty() || isBigger(d1.peek(), d3.peek()) && lastMoved != 3){
                d1.addFirst(d3.pop());
                lastMoved = 3;
            }
            
        }
        System.out.println("finish");
        for (Iterator<Integer> it = d3.iterator(); it.hasNext();) {
            System.out.println(it.next());
        }
	}
    
    public static boolean isBigger(Integer is, Integer than){
        if(is == null || than == null){
            return false;
        }
        return is > than;
    }
    
    
}
