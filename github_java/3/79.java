	import java.io.*;
	class Hanoi
	{
		public int n; //n= number of operations taken in entire process
		public void hanoi(int p1,int p2,int p3,int nd)
		{
				if(nd==1)
				{
					n=n+1;
		System.out.println("Step-"+n+":Move Disc-"+nd+" from Peg-"+p1+" to Peg-"+p2);
							return;
				}
				hanoi(p1,p3,p2,nd-1);
				n++;
		System.out.println("Step-"+n+":Move Disc-"+nd+" from Peg-"+p1+" to Peg-"+p2);
				hanoi(p3,p2,p1,nd-1);
				
		}
	}
	class tower
	{
		public static void main(String args[])throws IOException
		{
			int p1=1,p2=2,p3=3;
			int nd,n;
	BufferedReader br= new BufferedReader(new InputStreamReader(System.in));
			System.out.print("\nEnter number of disc to be transfered - ");
			nd=Integer.parseInt(br.readLine());
			Hanoi H=new Hanoi();
			H.n=0;
			H.hanoi(p1,p2,p3,nd);
			System.out.println("Number of operations performed are- "+H.n);
		}
	}