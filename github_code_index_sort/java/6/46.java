import java.math.*;
import java.io.*;
import java.util.Scanner;
import java.io.File;
import java.*;
import java.io.*;
import java.util.*;
/*java.lang.OutOfMemoryError: Java heap space
 * 2��java -Xms32m -Xmx800m className
������ִ��JAVA���ļ�ʱ�����������������className����Ҫִ�е�ȷ������������������
�����������ˡ�����ִ�е��ٶȱ�û�����õ�ʱ���ܶࡣ*/
public class Radix {
	
	public static  void main(String args[])
	{
		if(args.length != 1)
		{
			System.out.println("wrong args. java Radix max_process");
			return ;
		}
		
		RadixData radixer = new RadixData(Integer.valueOf(args[0]));
		
		radixer.getData();
		
		long begintime = System.currentTimeMillis();
		
		try{
			
		for(int i = 0; i<16 / radixer.log2_radix; ++i)
		{
			//System.out.println(i);
			for(int a = 0; a < radixer.MAX_PROCESS; a++)
			{
				for(int b = 0; b<radixer.radix; b++)
				{
					radixer.record[a][b].removeAllElements();
				}
			}
			
			
			//System.out.println(i+1);
			
			Vector sorts = new Vector();
				//parallel radixSort R;
			for(int j = 0, d = (radixer.num + radixer.MAX_PROCESS - 1) / radixer.MAX_PROCESS, b = 0; j < radixer.MAX_PROCESS; j++, b += d)
			{
				Thread t = new Thread(new RadixSorter(radixer, b, Math.min(b+d, radixer.num),j, i));
				//radixSort(b, Math.min(b+d, num), j, i);
				sorts.addElement(t);
				t.start();
			}
			
			for(int j = 0; j<sorts.size(); ++j)
			{
				((Thread) sorts.get(j)).join();
			}
			sorts.clear();
			
			//System.out.println(i+2);
			
			radixer.calCount();
			
			//System.out.println(i+3);
			
			for(int j = 0, d = (radixer.num + radixer.MAX_PROCESS - 1) / radixer.MAX_PROCESS, b = 0; j < radixer.MAX_PROCESS; j++, b += d)
			{
				//writeBack(b, Math.min(b+d, radixer.num), j);
				Thread t = new Thread(new RadixWriter(radixer, b, Math.min(b+d, radixer.num),j));
				sorts.addElement(t);
				t.start();
			}
			for(int j = 0; j<sorts.size(); ++j)
			{
				((Thread) sorts.get(j)).join();
			}
			sorts.removeAllElements();
			
			//System.out.println(i+5);
			//swap 
			int tmp[] = radixer.data;
			radixer.data = radixer.tmp_data;
			radixer.tmp_data = tmp;
		}
		
		}catch (Exception e) {
			System.out.println("Exception from main");
			System.out.println(e.toString());
			System.out.println(e.getLocalizedMessage());
		}
		
		long endtime=System.currentTimeMillis();

		long costTime = (endtime - begintime);
		//validate result
		for(int i = 1; i<radixer.num; i++) if(radixer.data[i]<radixer.data[i-1])
		{
			System.out.println("Error!");
		}
		
		System.out.println(1.0*costTime/1000);
	}
}