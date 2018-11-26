package GuviProgs;
import java.util.*;
public class TowerOfHanoi {
	static Stack<Integer>[] towerHanoi=new Stack[5];
	public void Disk(int n,int disk1,int disk2,int disk3)
	{
	  if (n == 1) {
          System.out.println(disk1+"="+disk3);
      } else {
          Disk(n - 1, disk1,disk3,disk3);
          int d = towerHanoi[disk1].pop();                                             
          towerHanoi[disk3].push(d);
          System.out.println(disk1+"="+disk3);
          Disk(n - 1,disk2,disk1,disk3);
      }
	}
	public static void main(String[] args)
	{
		towerHanoi[1]=new Stack<Integer>();
		towerHanoi[2]=new Stack<Integer>();
		towerHanoi[3]=new Stack<Integer>();
		for(int i=3;i>0;i--)
		{
			towerHanoi[1].push(i);
		}
		TowerOfHanoi towerOfHanoi=new TowerOfHanoi();
		towerOfHanoi.Disk(3,1,2,4);
	}

}
