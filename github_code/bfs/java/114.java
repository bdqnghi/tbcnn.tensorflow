import java.util.Scanner;


public class SnakesandLadders2 {

	public static void initializeMatrix()
	{
		/*for(int i = 1;i<=99;i++)
		{
			BreadthFirstSearch.adj_matrix[i][i+1] = 1;		
		}*/
		for(int i = 1;i<=100;i++)
		{
			BreadthFirstSearch.color[i] = 0; //white
			BreadthFirstSearch.parent[i] = -1;
			BreadthFirstSearch.distance[i] = 0;
		}
	}
	
	
	public static void main(String[] args) {

		BreadthFirstSearch.source = 1;
		initializeMatrix();
		Scanner s = new Scanner(System.in);
		int T = s.nextInt();
		while(T-- != 0)
		{
			int N = s.nextInt();
			int[][] ladder = new int[N][3];
			for(int i = 0;i < N; i++)
			{
				ladder[i][0] = s.nextInt();
				ladder[i][1] = s.nextInt();
				BreadthFirstSearch.adj_matrix[ladder[i][0]][ladder[i][1]] = 1;
				BreadthFirstSearch.adj_matrix[BreadthFirstSearch.source][ladder[i][0]] = 1;
				BreadthFirstSearch.adj_matrix[ladder[i][1]][100] = 1;
				//ladder[i][2] = ladder[i][1] - ladder[i][0] + 1;
			}
			int M = s.nextInt();
			int[][] snake = new int[M][2];
			for(int i = 0;i < M; i++)
			{
				snake[i][0] = s.nextInt();
				snake[i][1] = s.nextInt();
				BreadthFirstSearch.adj_matrix[snake[i][0]][snake[i][1]] = 1;
			}
			
			BreadthFirstSearch.bfsFunction();
			for(int i = 1;i <= 100; i++)
			{
				System.out.println("Dist[" + i + "]: " + BreadthFirstSearch.distance[i] + " Parent: " + BreadthFirstSearch.parent[i]);
			}
			
			int i = 100, optimalMove = 0, previous = 100;
			while (i != 1)
			{
				int j = BreadthFirstSearch.parent[i];
				if (i == 100)
				{
					int mod_val = (100 - j)%6;
					optimalMove = (100 - j)/6;
					if (mod_val != 0)
						optimalMove++;
					previous = i;
					i = j;
					//System.out.println("optimalMove so far: " + optimalMove);
				}
				else
				{
					previous = i;
					i = j;
					if (j == 1)
					{
						int mod_val = (previous - j)%6;
						optimalMove = optimalMove + ((previous - j)/6);
						if (mod_val != 0)
							optimalMove++;
						break;
					}
					//optimalMove++;
				}
				System.out.println("optimalMove so far: " + optimalMove);
			}
			System.out.println("Optimal moves: " + optimalMove);
		}
	}

}
