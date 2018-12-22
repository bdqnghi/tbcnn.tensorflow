
public class towerofhanoi {
	
	private int numofmoves=0;
	public int move(int n, String from, String to, String inter ){
		if (n == 1){
			System.out.println("Move disc 1 from " + from + " to " + to);
			numofmoves++;
		}
		else {
			numofmoves++;
			//move from A to B using C
			move(n - 1, from, inter, to);
			//move last item from from A to C
			System.out.println("Move disc " + n + " from " + from + " to " + to);
			move(n - 1, inter, to, from);
		}
		return numofmoves;
	}


}
