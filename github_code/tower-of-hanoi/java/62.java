package Dynamic;

public class TowerOfHanoi {
	static int N=3,count=0;
	
	public static void main(String[] args) {
		int n=6;
		towerOFHanoi( n,"source", "intermediate", "destination");
		System.out.println("Total moves : "+ count);
	}
	
	static void towerOFHanoi(int n, String source, String intermediate,String destination){
		//System.out.println("Move ");
		if(n==0){
			return;
		}
		count++;
		towerOFHanoi(n-1, source, destination, intermediate);
		System.out.println("Move "+ n + " to tower "+ destination);
		towerOFHanoi(n-1, intermediate, source, destination);
		
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
//	static void towerOFHanoi(int n,String source,String intermediate,String destination){
//		if(n==1){
//			//System.out.println("Move "+(n) +" to tower 3");
//			return;
//		}else{
//			count++;
//			
//			//System.out.println("Move "+ (n-1) +" to tower " + 2 +" via tower 3" );
//			towerOFHanoi(n-1,"source", "destination" , "intermediate");
//			
//			System.out.println("Move " + n + " to tower " + 2 );
//			System.out.println("Move "+ (n-1) +" to tower " + 3 +" via tower 1" );
//
//			//towerOFHanoi(n-1,"source", "intermediate", "destination");
//			towerOFHanoi(n-1,"intermediate","source", "destination");
//
//		}
//	}

}
