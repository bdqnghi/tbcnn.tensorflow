package positronic.satisfiability.demos.towerofhanoi;

import java.util.List;

import positronic.satisfiability.elements.BooleanLiteral;
import positronic.satisfiability.elements.Conjunction;
import positronic.satisfiability.elements.ExclusiveDisjunction;
import positronic.satisfiability.elements.IBooleanVariable;
import positronic.satisfiability.elements.IProblem;
import positronic.satisfiability.elements.Problem;

public class TowerOfHanoi
{
	public static void main(String[] args) throws Exception
	{
		//Initialize the Tower of Hanoi with all disks on peg 0
		TowerOfHanoi start=new TowerOfHanoi("start",3,3);
		TowerOfHanoi first=new TowerOfHanoi("first",start.disks,start.numberOfPegs);
		TowerOfHanoi second=new TowerOfHanoi("second",start.disks,start.numberOfPegs);
		TowerOfHanoi third=new TowerOfHanoi("third",start.disks,start.numberOfPegs);
		TowerOfHanoi fourth=new TowerOfHanoi("fourth",start.disks,start.numberOfPegs);
		TowerOfHanoi fifth=new TowerOfHanoi("fifth",start.disks,start.numberOfPegs);
		TowerOfHanoi sixth=new TowerOfHanoi("sixth",start.disks,start.numberOfPegs);
		TowerOfHanoi seventh=new TowerOfHanoi("seventh",start.disks,start.numberOfPegs);
		TowerOfHanoi eighth=new TowerOfHanoi("eighth",start.disks,start.numberOfPegs);
		TowerOfHanoi ninth=new TowerOfHanoi("ninth",start.disks,start.numberOfPegs);
		TowerOfHanoi goal=new TowerOfHanoi("goal",3,3);
		
		IProblem problem=new TowerOfHanoiInitializer(start);
		problem=new Conjunction(problem,TowerOfHanoi.possibleMover(start,first));
		problem=new Conjunction(problem,TowerOfHanoi.possibleMover(first,second));
		problem=new Conjunction(problem,TowerOfHanoi.possibleMover(second,third));
		problem=new Conjunction(problem,TowerOfHanoi.possibleMover(third,fourth));
		problem=new Conjunction(problem,TowerOfHanoi.possibleMover(fourth,fifth));
		problem=new Conjunction(problem,TowerOfHanoi.possibleMover(fifth,sixth));
		problem=new Conjunction(problem,TowerOfHanoi.possibleMover(sixth,seventh));
		problem=new Conjunction(problem,TowerOfHanoi.possibleMover(seventh,eighth));
		problem=new Conjunction(problem,TowerOfHanoi.possibleMover(eighth,ninth));
		problem=new Conjunction(problem,TowerOfHanoi.possibleMover(ninth,goal));
		problem=new Conjunction(problem,new TowerOfHanoiFinalizer(goal));
		
		System.out.println("Goal\n"+goal);
		
		System.out.println(problem);
		
		List<?> s=problem.findModel(Problem.defaultSolver());
		if(s!=null && s.size()>0)
    {
			BooleanLiteral.interpret(s);
			System.out.println("start\n"+start);
			System.out.println("first\n"+first);
			System.out.println("second\n"+second);
			System.out.println("third\n"+third);
			System.out.println("fourth\n"+fourth);
			System.out.println("fifth\n"+fifth);
			System.out.println("sixth\n"+sixth);
			System.out.println("seventh\n"+seventh);
			System.out.println("eighth\n"+eighth);
			System.out.println("ninth\n"+ninth);
			System.out.println("goal\n"+goal);
    }
		else
			System.out.println("There is no solution.");
	}
	
	public static IProblem possibleMover(TowerOfHanoi start,TowerOfHanoi end) throws Exception
	{
		return new ExclusiveDisjunction(
			new IProblem[]
			{
					new DiskMover(start,end,0,1,0),
					new DiskMover(start,end,0,2,0),
					new DiskMover(start,end,1,0,0),
					new DiskMover(start,end,1,2,0),
					new DiskMover(start,end,2,0,0),
					new DiskMover(start,end,2,1,0),
					new DiskMover(start,end,0,1,1),
					new DiskMover(start,end,0,2,1),
					new DiskMover(start,end,1,0,1),
					new DiskMover(start,end,1,2,1),
					new DiskMover(start,end,2,0,1),
					new DiskMover(start,end,2,1,1),
					new DiskMover(start,end,0,1,2),
					new DiskMover(start,end,0,2,2),
					new DiskMover(start,end,1,0,2),
					new DiskMover(start,end,1,2,2),
					new DiskMover(start,end,2,0,2),
					new DiskMover(start,end,2,1,2)
			});
	}
	
	private int disks;
	private String name;
	private int numberOfPegs;
	private Peg[] peg;
	
	public TowerOfHanoi(String name, int disks, int pegs) throws Exception
	{
		this.disks=disks;
		this.numberOfPegs=pegs;
		this.name=name;
		//this.state=new IBooleanVariable[this.pegs][];
		this.peg=new Peg[this.numberOfPegs];

		for(int i=0;i<this.numberOfPegs;i++)
			peg[i]=new Peg(this.disks);
		
		for(int i=0;i<this.numberOfPegs;i++)
			for(int j=0;j<this.disks;j++)
				peg[i].disk[j]=new Disk(name+"$"+i+"$"+j,false);
	}
	
	public String getName()
	{
		return name;
	}
	
	public int getNumberOfDisks()
	{
		return disks;
	}
	
	public int getNumberOfPegs()
	{
		return numberOfPegs;
	}

	public IBooleanVariable getStateVariable(int peg, int disk)
	{
		return this.peg[peg].disk[disk].disk;
	}

	public void setName(String name)
	{
		this.name = name;
	}

	public void setNumberOfDisks(int disks)
	{
		this.disks = disks;
	}

	public void setNumberOfPegs(int pegs)
	{
		this.numberOfPegs = pegs;
	}

	public void setStateVariable(int peg, int disk, IBooleanVariable ib)
	{
		this.peg[peg].disk[disk].disk=ib;
	}

	public String toString()
	{
		String ret="";
		for(int i=0;i<this.numberOfPegs;i++)
		{
			ret+=(i+"\t");
			for(int j=0;j<this.disks;j++)
				if(peg[i].disk[j].getValue())
					ret+= " "+j;
				
			ret+="\n";
		}
		return ret;
	}
}
