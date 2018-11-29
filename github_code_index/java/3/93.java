package TowerOfHanoi.test.CreateTower;

/**
 * Implementing the Tower of Hanoi classical algorithm
 * @author Muhammed Ahad
 * e-mail: ahad3112@yahoo.com
 */

import TowerOfHanoi.test.TowerOfHanoi;

// importing package
import TowerOfHanoi.test.Tower.HanoiTower;

public class CreateTowers {

	// three towers named left, center and right 
	public HanoiTower left;
	public HanoiTower center;
	public HanoiTower right;
	
	// constructor for the CreateTowers class
	public CreateTowers(){
		left = new HanoiTower("left",TowerOfHanoi.n);
		center = new HanoiTower("center",0);
		right = new HanoiTower("right",0);
	}
}
