package codility;

public class DFS {

	public static void main(String[] args) {

		int a[]= {9,1,4,9,0,4,8,9,0,1};
		//converting a 1D matrix to a 2d graph
		int arr[][]= new int[a.length][a.length];
		int city=0;
		for(int i=0;i<a.length;++i) {
			city=a[i];
			for(int j=0;j<a.length;++j)
			{
				if(j==city ) {
					arr[i][j]=1;
					arr[j][i]=1;
				}

			}
		}

		for(int i=0;i<a.length;++i) {
			for(int j=0;j<a.length;++j)
			{
				System.out.print(arr[i][j]+",");
			}
			System.out.println();
		}
		
	}

}
