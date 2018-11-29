public class EditDistance {

	public static void main(String [] args){
		String start = "plasma";
		String end =   "altruism";
		
		int editDistance = calcEditDistance(start,end);
		System.out.println("Edit Distance : "+editDistance);
	}
	
	private static int calcEditDistance(String start, String end){
		int n = start.length();
		int m = end.length();
		
		int editDistance[][] = new int[n+1][m+1];
		
		for(int i=0;i<=n;i++){
			editDistance[i][0] = i;
		}
		
		for(int j=0;j<=m;j++){
			editDistance[0][j] = j;
		}
		
		for (int i=1;i<=n;i++){
			for (int j=1;j<=m;j++){
				if(start.charAt(i-1) == end.charAt(j-1)){
					int minDist = Math.min(editDistance[i][j-1]+1, editDistance[i-1][j]+1 );
					editDistance[i][j] = Math.min(minDist,editDistance[i-1][j-1]);
				}
				else{
					int minDist = Math.min(editDistance[i][j-1] + 1, editDistance[i-1][j]+1);
					editDistance[i][j] = Math.min(minDist,editDistance[i-1][j-1]+1);
				}
			}
		}
		
		return editDistance[n][m];
	}
	
	
}
