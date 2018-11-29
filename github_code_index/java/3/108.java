
package csci152.impl;

import csci152.adt.Stack;

public class TowerOfHanoi {

	private Stack<Integer>[] post = new ArrayStack[3];
	private int numMoves = 0;
	
	public TowerOfHanoi(int numDiscs) {
		/*
		 TODO: Initialize all three posts to new stack objects,
		 and push onto post[0] the integers:
		    numDiscs, numDiscs-1, numDiscs-2, ..., 1 
		 */
                for(int i=0;i<3;i++)
                    post[i] = new ArrayStack();
                for(int i=numDiscs;i>0;i--)
                    post[0].push(i);
        }
	
	public void moveDisc(int from, int to) throws Exception {
		/* 
		 TODO:  Moves the integer from the top of post[from] to 
		 post[to].  Throws an exception if either index is not
		 0, 1, or 2; or if post[from] is empty; or if the value
		 on top of post[from] is bigger than the topmost item of
		 post[to].
		 */
                if((from <0 || from>2) || (to<0 ||to>2)||post[from].getSize()==0)
                    throw new Exception("Error");
                int x=post[from].pop();
                if(post[to].getSize()!=0){
                    int y=post[to].pop();
                    if(x>y){
                        post[to].push(y);
                        post[from].push(x);
                        throw new Exception("element is bigger");
                    }else{
                        post[to].push(y);
                        post[to].push(x);
                    }
                }else
                    post[to].push(x);
                
		numMoves++;
	}
	
	public boolean isFinished() {
		/*
		 TODO:  Returns true if and only if all of the discs are
		 on post[2] (i.e., post[0] and post[1] are empty)
		 */
                if(post[0].getSize()==0 && post[1].getSize()==0)
                    return true;
		return false;
	}
	
	public int getNumMoves() {
		return numMoves;
	}
	
	public String toString() {
		/* 
		 TODO:  Returns some string representation of the current
		 game state.... this should help with debugging
		 */
                String s = "";
                s+="post[0]: "+post[0].toString()+"\n"+"post[1]: "+post[1].toString()+"\n"+"post[2]: "+post[2].toString()+"\n";
		return s;
	}
	
}
