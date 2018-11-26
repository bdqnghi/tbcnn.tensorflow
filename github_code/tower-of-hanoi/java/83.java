package question1;


import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;


/**
 * Class description
 * 
 *  This class will solve the TowerOfHanoi Problem
 * 
 * @version1.10 19 Jul 2017
 * @author Pawan Manglani
 */

public class TowerOfHanoi {


	/** The al. type of ArrayList*/
	private ArrayList<String> al = new ArrayList<>();

	/** The step type of String. */
	private String step;

	/** The number of disk. */
	public int number_of_disk=0;

	/**
	 * Tower of hanoi.
	 *
	 * @param source the source String
	 * @param destination the destination String
	 * @param auxiliary the auxiliary String
	 * @param disk_count the count of disk
	 * @throws IllegalArgumentException the illegal argument exception
	 * @throws NullPointerException the null pointer exception
	 */
	protected void towerOfHanoi(String source,String destination,
			String auxiliary,int disk_count) throws IllegalArgumentException,NullPointerException{

		if(number_of_disk<=0) {
			throw new IllegalArgumentException("Number of disk should not be less than 1");
		}
		else if((source== null) || (destination== null) || (auxiliary== null)) {
			throw new NullPointerException("String Can't be null");
		}
		if(disk_count==number_of_disk) {
			step = "Move Disk "+ (disk_count)+" from " + source + " to " + destination;
			al.add(step);
		}
		else {
			towerOfHanoi(source,auxiliary,destination,disk_count+1);
			step = "Move Disk "+ (disk_count)+" from " + source + " to " + destination;
			al.add(step);
			towerOfHanoi(auxiliary,destination,source,disk_count+1);
		}
	}

	/**
	 *  solveHanoi function.
	 *
	 * 
	 * @param disk_count the disk count
	 * @param source the source String
	 * @param destination the destination String
	 * @param auxiliary the auxiliary String
	 * @return the array list
	 */
	public List<String> solveHanoi(int disk_count,
			String source,String destination,String auxiliary) {
		List<String> result = new ArrayList<>();
		try {
			number_of_disk = disk_count;
			disk_count = 1;
			towerOfHanoi(source,destination,auxiliary,disk_count);
			result = al;
		}catch(Exception e) {
			System.out.println(e.getMessage());
			result.add(e.getMessage());
		}
		return result;
	}


	/**
	 * The main method.
	 *
	 * @param args the command-line arguments
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		TowerOfHanoi obj = new TowerOfHanoi();
		List<String> result;
		int disk_count = 1;
		String source = "A",destination="B",auxiliary="C";
		try {
			result = obj.solveHanoi(disk_count, source, destination, auxiliary);
			Iterator<String> itr =result.iterator();
			while(itr.hasNext()) {
				System.out.println(itr.next());
			}
		}catch(Exception e) {
			e.printStackTrace();
		}

	}

}
