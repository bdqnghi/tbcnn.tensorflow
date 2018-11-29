//Solve tower of hanoi for N disks

package progs;

import java.io.PrintWriter;
import header.Program;
import header.ProgramInfo;

public class Tower extends Program{

	private static final long serialVersionUID = 506849418106032071L;

	public Tower() {super(ProgramInfo.tower_Name);}

	@Override
	public int run(PrintWriter out, String[] args) throws InterruptedException 
	{
		if(args[1] == null) return ILLEGAL_PARAMETER;
		
		int n = Integer.parseInt(args[1]);
		if(n <= 0 ) return ILLEGAL_PARAMETER;
		
		out.println(args[0]+": "+n+" rings.");
		hanoi(n, out, 1, 2);
		return SUCCESS;
	}
	
	public void hanoi(int n, PrintWriter out, int startPeg, int endPeg) throws InterruptedException
	{
		schedule();//call schedule method each iteration for thread stuff
		
		if(n==1)
			out.println("Move disk 1 from peg "+ startPeg + " to peg "+endPeg+".");
		else{
			int sparePeg = 6 - startPeg - endPeg;
			hanoi(n-1, out, startPeg,sparePeg);
			out.println("Move disk "+n+" from peg "+startPeg + " to peg "+endPeg+".");
			hanoi(n-1,out,sparePeg,endPeg);
		}
	}
	
}
