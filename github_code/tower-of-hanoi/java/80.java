/**
 * 
 */
package recursion;

/**
 * @author Ronak Goyal
 *
 */
public class TowerOfHanoi {

	/**
	 * @param args
	 */
	public static void towerOfHanoi(int n , char source, char destination, char auxillary){
		if(n==0 )return ;
		towerOfHanoi(n-1, source, auxillary, destination);
		System.out.println("Move the disk " +n + " from " + source+ " to " + destination);
		towerOfHanoi(n-1, auxillary, destination, source);
	}
	public static void main(String[] args) {
		// TODO Auto-generated method stub
       towerOfHanoi(5,'S','D','A');
	}

}
