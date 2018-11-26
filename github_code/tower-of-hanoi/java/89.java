# tower-of-hanoi
public class Towerofhanoi {
	static int c=0;
	public static void main(String[] args) {
		int n=3;
		tower(n,"Stack1","Stack2","Stack3");
		System.out.println("Minimum no of steps :"+c);
	}
	public static void tower(int top,String from,String inter, String to)
	{   
		if(top==1)
		{   c++;
			System.out.println("Step"+c+": disk 1 "+from+" to "+to);
			
		}
		else
		{ 
			tower(top-1,from,to,inter);
			 c++;
			System.out.println("Step"+c+": disk "+top+" from "+from+" to "+to);
		    tower(top-1,inter,from,to);
		}
		
	}

}
