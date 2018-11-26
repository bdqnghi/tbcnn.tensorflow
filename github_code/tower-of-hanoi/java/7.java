package positronic.satisfiability.demos;

import java.util.List;

import positronic.satisfiability.elements.BitFixer;
import positronic.satisfiability.elements.BooleanLiteral;
import positronic.satisfiability.elements.BooleanVariable;
import positronic.satisfiability.elements.Conjunction;
import positronic.satisfiability.elements.ExclusiveDisjunction;
import positronic.satisfiability.elements.IBooleanVariable;
import positronic.satisfiability.elements.IProblem;
import positronic.satisfiability.elements.Problem;

class MoveDisk extends Problem implements IProblem
{
	private static final long serialVersionUID = 7296744222237300730L;

	public MoveDisk(
			TowerOfHanoi pretransfer,
			TowerOfHanoi postransfer,
			int sourcepeg,
			int targetpeg, 
			int disk) throws Exception
	{
		this.setClauses(new Conjunction(
				new BitFixer(pretransfer.getStateVariable(sourcepeg,disk),
						true),
				new BitFixer(postransfer.getStateVariable(sourcepeg,disk),
						false),
				new BitFixer(pretransfer.getStateVariable(targetpeg,disk),
								false),
				new BitFixer(postransfer.getStateVariable(targetpeg,disk),
								true)
					).getClauses());
	}
}

/*class TowerOfHanoiFinalizer extends Problem implements IProblem
{
	private static final long serialVersionUID = 1L;
	
	public TowerOfHanoiFinalizer(final TowerOfHanoi tower) throws Exception
	{
		for(int i=0;i<tower.pegs;i++)
			for(int j=0;j<tower.disks;j++)
				tower.state[i][j]=BooleanVariable.getBooleanVariable(tower.name+"$"+i+"$"+j,(i==1)?true:false);
		this.setClauses(new TowerOfHanoiFixer(tower).getClauses());
	}
}*/

public class TowerOfHanoi
{
	/*public static void main(String[] args) throws Exception
	{
		//Initialize the Tower of Hanoi with all disks on peg 0
		TowerOfHanoi start=new TowerOfHanoi("start",3,3);
		
		IProblem problem=
			new TowerOfHanoiInitializer(start);
		
		System.out.println(start);
		
		TowerOfHanoi first=new TowerOfHanoi("first",start.disks,start.pegs);
		problem=new Conjunction(problem,
				new Disjunction(
						new IProblem[]
						{
								new TowerOfHanoiTransferer(start,first,0,1,1),
								new TowerOfHanoiTransferer(start,first,0,2,1),
								new TowerOfHanoiTransferer(start,first,1,0,1),
								new TowerOfHanoiTransferer(start,first,1,2,1),
								new TowerOfHanoiTransferer(start,first,2,0,1),
								new TowerOfHanoiTransferer(start,first,2,1,1)
						}));
		TowerOfHanoi second=new TowerOfHanoi("second",start.disks,start.pegs);
		problem=new Conjunction(problem,
				new Disjunction(
						new IProblem[]
						{
								new TowerOfHanoiTransferer(first,second,0,1,1),
								new TowerOfHanoiTransferer(first,second,0,2,1),
								new TowerOfHanoiTransferer(first,second,1,0,1),
								new TowerOfHanoiTransferer(first,second,1,2,1),
								new TowerOfHanoiTransferer(first,second,2,0,1),
								new TowerOfHanoiTransferer(first,second,2,1,1)
						}));
		TowerOfHanoi third=new TowerOfHanoi("third",start.disks,start.pegs);
		problem=new Conjunction(problem,
				new Disjunction(
						new IProblem[]
						{
								new TowerOfHanoiTransferer(second,third,0,1,1),
								new TowerOfHanoiTransferer(second,third,0,2,1),
								new TowerOfHanoiTransferer(second,third,1,0,1),
								new TowerOfHanoiTransferer(second,third,1,2,1),
								new TowerOfHanoiTransferer(second,third,2,0,1),
								new TowerOfHanoiTransferer(second,third,2,1,1)
						}));
		TowerOfHanoi fourth=new TowerOfHanoi("fourth",start.disks,start.pegs);
		problem=new Conjunction(problem,
				new Disjunction(
						new IProblem[]
						{
								new TowerOfHanoiTransferer(third,fourth,0,1,1),
								new TowerOfHanoiTransferer(third,fourth,0,2,1),
								new TowerOfHanoiTransferer(third,fourth,1,0,1),
								new TowerOfHanoiTransferer(third,fourth,1,2,1),
								new TowerOfHanoiTransferer(third,fourth,2,0,1),
								new TowerOfHanoiTransferer(third,fourth,2,1,1)
						}));
		TowerOfHanoi fifth=new TowerOfHanoi("fifth",start.disks,start.pegs);
		problem=new Conjunction(problem,
				new Disjunction(
						new IProblem[]
						{
								new TowerOfHanoiTransferer(fourth,fifth,0,1,1),
								new TowerOfHanoiTransferer(fourth,fifth,0,2,1),
								new TowerOfHanoiTransferer(fourth,fifth,1,0,1),
								new TowerOfHanoiTransferer(fourth,fifth,1,2,1),
								new TowerOfHanoiTransferer(fourth,fifth,2,0,1),
								new TowerOfHanoiTransferer(fourth,fifth,2,1,1)
						}));
		TowerOfHanoi sixth=new TowerOfHanoi("sixth",start.disks,start.pegs);
		problem=new Conjunction(problem,
				new Disjunction(
						new IProblem[]
						{
								new TowerOfHanoiTransferer(fifth,sixth,0,1,1),
								new TowerOfHanoiTransferer(fifth,sixth,0,2,1),
								new TowerOfHanoiTransferer(fifth,sixth,1,0,1),
								new TowerOfHanoiTransferer(fifth,sixth,1,2,1),
								new TowerOfHanoiTransferer(fifth,sixth,2,0,1),
								new TowerOfHanoiTransferer(fifth,sixth,2,1,1)
						}));
		TowerOfHanoi goal=new TowerOfHanoi("goal",3,3);
		problem=new Conjunction(problem,
				new Disjunction(
						new IProblem[]
						{
								new TowerOfHanoiTransferer(sixth,goal,0,1,1),
								new TowerOfHanoiTransferer(sixth,goal,0,2,1),
								new TowerOfHanoiTransferer(sixth,goal,1,0,1),
								new TowerOfHanoiTransferer(sixth,goal,1,2,1),
								new TowerOfHanoiTransferer(sixth,goal,2,0,1),
								new TowerOfHanoiTransferer(sixth,goal,2,1,1)
						}));
		problem=new Conjunction(problem,new TowerOfHanoiFinalizer(goal));
		System.out.println(goal);
		
		System.out.println(problem);
		
		List<?> s=problem.findModel(SolverFactory.newMiniSAT());
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
    }
		else
			System.out.println("There is no solution.");
	}*/
	
	/*public static void main(String[] args) throws Exception
	{
		//Initialize the Tower of Hanoi with all disks on peg 0
		TowerOfHanoi start=new TowerOfHanoi("start",2,3);
		
		IProblem problem=new TowerOfHanoiInitializer(start);
		
		System.out.println(start);
		
		TowerOfHanoi goal=new TowerOfHanoi("goal",2,3);
		TowerOfHanoi first=new TowerOfHanoi("first",start.disks,start.pegs);
		problem=new Conjunction(problem,TowerOfHanoi.possibleMover(start,first));
		problem=new Conjunction(problem,TowerOfHanoi.possibleMover(first,goal));
		problem=new Conjunction(problem,new TowerOfHanoiFinalizer(goal));
		System.out.println(goal);
		
		System.out.println(problem);
		
		List<?> s=problem.findModel(SolverFactory.newMiniSAT());
		if(s!=null && s.size()>0)
    {
			BooleanLiteral.interpret(s);
			System.out.println("start\n"+start);
			System.out.println("first\n"+first);
			System.out.println("goal\n"+goal);
    }
		else
			System.out.println("There is no solution.");
	}*/
	public static void main(String[] args) throws Exception
	{
		//Initialize the Tower of Hanoi with all disks on peg 0
		TowerOfHanoi start=new TowerOfHanoi("start",3,3);
		TowerOfHanoi first=new TowerOfHanoi("first",start.disks,start.pegs);
		TowerOfHanoi second=new TowerOfHanoi("second",start.disks,start.pegs);
		TowerOfHanoi third=new TowerOfHanoi("third",start.disks,start.pegs);
		TowerOfHanoi fourth=new TowerOfHanoi("fourth",start.disks,start.pegs);
		TowerOfHanoi fifth=new TowerOfHanoi("fifth",start.disks,start.pegs);
		TowerOfHanoi sixth=new TowerOfHanoi("sixth",start.disks,start.pegs);
		TowerOfHanoi seventh=new TowerOfHanoi("seventh",start.disks,start.pegs);
		TowerOfHanoi eighth=new TowerOfHanoi("eighth",start.disks,start.pegs);
		TowerOfHanoi ninth=new TowerOfHanoi("ninth",start.disks,start.pegs);
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
					new MoveDisk(start,end,0,1,0),
					new MoveDisk(start,end,0,2,0),
					new MoveDisk(start,end,1,0,0),
					new MoveDisk(start,end,1,2,0),
					new MoveDisk(start,end,2,0,0),
					new MoveDisk(start,end,2,1,0),
					new MoveDisk(start,end,0,1,1),
					new MoveDisk(start,end,0,2,1),
					new MoveDisk(start,end,1,0,1),
					new MoveDisk(start,end,1,2,1),
					new MoveDisk(start,end,2,0,1),
					new MoveDisk(start,end,2,1,1),
					new MoveDisk(start,end,0,1,2),
					new MoveDisk(start,end,0,2,2),
					new MoveDisk(start,end,1,0,2),
					new MoveDisk(start,end,1,2,2),
					new MoveDisk(start,end,2,0,2),
					new MoveDisk(start,end,2,1,2)
			});
	}
	
	private int disks;
	private String name;
	private int pegs;
	private IBooleanVariable[][] state;
	
	public TowerOfHanoi(String name, int disks, int pegs) throws Exception
	{
		this.disks=disks;
		this.pegs=pegs;
		this.name=name;
		this.state=new IBooleanVariable[this.pegs][];

		for(int i=0;i<this.pegs;i++)
			state[i]=new IBooleanVariable[this.disks];
		
		for(int i=0;i<this.pegs;i++)
			for(int j=0;j<this.disks;j++)
				state[i][j]=BooleanVariable.getBooleanVariable(name+"$"+i+"$"+j,false);
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
		return pegs;
	}

	public IBooleanVariable getStateVariable(int peg, int disk)
	{
		return this.state[peg][disk];
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
		this.pegs = pegs;
	}

	public void setStateVariable(int peg, int disk, IBooleanVariable ib)
	{
		this.state[peg][disk]=ib;
	}

	public String toString()
	{
		String ret="";
		for(int i=0;i<this.pegs;i++)
		{
			ret+=(i+"\t");
			for(int j=0;j<this.disks;j++)
				if(state[i][j].getValue())
					ret+= " "+j;
				
			ret+="\n";
		}
		return ret;
	}
}

class TowerOfHanoiFinalizer extends Problem implements IProblem
{
	private static final long serialVersionUID = 1L;
	
	public TowerOfHanoiFinalizer(final TowerOfHanoi tower) throws Exception
	{
		for(int i=0;i<tower.getNumberOfPegs();i++)
			for(int j=0;j<tower.getNumberOfDisks();j++)
				tower.setStateVariable(i,j,BooleanVariable.getBooleanVariable(tower.getName()+"$"+i+"$"+j,false));
		tower.getStateVariable(0,2).setValue(true);
		tower.getStateVariable(2,1).setValue(true);
		tower.getStateVariable(0,0).setValue(true);
		
		this.setClauses(new TowerOfHanoiFixer(tower).getClauses());
	}
}

class TowerOfHanoiFixer extends Problem implements IProblem
{
	private static final long serialVersionUID = 1L;
	
	public TowerOfHanoiFixer(final TowerOfHanoi tower) throws Exception
	{
		final IProblem[] problems=new IProblem[tower.getNumberOfPegs()*tower.getNumberOfDisks()];
		int count=0;
		for(int i=0;i<tower.getNumberOfPegs();i++)
			for(int j=0;j<tower.getNumberOfDisks();j++)
				problems[count++]=new BitFixer(tower.getStateVariable(i,j));
		this.setClauses(new Conjunction(problems).getClauses());
	}
}

class TowerOfHanoiInitializer extends Problem implements IProblem
{
	private static final long serialVersionUID = 1L;
	
	public TowerOfHanoiInitializer(final TowerOfHanoi tower) throws Exception
	{
		for(int i=0;i<tower.getNumberOfPegs();i++)
			for(int j=0;j<tower.getNumberOfDisks();j++)
				tower.setStateVariable(i,j,BooleanVariable.getBooleanVariable(tower.getName()+"$"+i+"$"+j,(i==0)?true:false));
		this.setClauses(new TowerOfHanoiFixer(tower).getClauses());
	}
}
