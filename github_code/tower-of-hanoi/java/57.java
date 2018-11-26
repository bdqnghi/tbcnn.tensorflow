public class TowerOfHanoi {
	public static void main(String[] args) {
	int numOfDisks=3;
	System.out.println("Tower of Hanoi Problem for Thee disks");
	towerOfHanoi(numOfDisks,'A','B','C');
	}
	public static void towerOfHanoi(int disks,char first,char middle,char last){
		if(disks==1){
			System.out.println("Disk 1 from "+first+" to "+last);
		}
		else{
			towerOfHanoi(disks-1, first,last,middle);
			System.out.println("Disk "+disks+" from "+first+" to "+last);
			towerOfHanoi(disks-1,middle, first,last);
		}
	}
}
