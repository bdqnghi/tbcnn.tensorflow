package njupt.ch1.EX;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.util.Arrays;

public class Quick {
	public static void sort(Comparable[] a){
		sort(a, 0, a.length-1);
	}
	
	private static void sort(Comparable[] a, int lo, int hi){
		if(hi <= lo){
			return;
		}
		int j = partition(a, lo, hi);
		sort(a, lo, j-1);  // 将左半部分a[lo...j-1]排序
		sort(a, j+1, hi);  // 将右半部分a[j+1...hi]排序
	}
	
	private static int partition(Comparable[] a, int lo, int hi){
		//将数组切分成 a[lo..i-1], a[i], a[i+1...hi]
		int i = lo, j = hi+1;    // 左右扫描指针
		Comparable v = a[lo];    //切分元素
		while(true){
			//扫描左右数组，检查扫描是否结束，并交换元素
			while(less(a[++i], v)){
				if(i == hi)
					break;
			}
			while(less(v, a[--j])){
				if(j == lo)
					break;
			}
			if (i >= j)
				break;
			exch(a, i, j);
		}
		exch(a, lo, j);   // 将v = a[j] 放入正确的位置
		return j;         // a[lo..j-1] <= a[j] <= a[j+1...hi] 达成
	}
	
	private static boolean less(Comparable v, Comparable w){
		return v.compareTo(w) < 0 ;
		//return v < w; 即可应用于基本数据类型
	}
	
	private static void exch(Comparable[] a, int i, int j)
	{
		Comparable t = a[i];
		a[i] = a[j];
		a[j] = t;
	}
	
	private static void show(Comparable[] a){
		//  //  在单行中打印数组
		for(int i = 0; i < a.length; i++){
			System.out.print(a[i] + " ");
		}
		System.out.println();
	}
	
	public static void main(String[] args) {
		File file = new File("H:\\java_test_data\\test_data\\test_data.txt");
		String[] myArray = new String[20000];  //100：这个值你自己定义，但不宜过大，要根据你文件的大小了，或者文件的行数
		//建立数据的输入通道
		int i = 0;
		try {
			FileReader fr = new FileReader(file);
			BufferedReader buf = new BufferedReader(fr);
            String readLine = "";
            while((readLine = buf.readLine()) != null){
                myArray[i] = readLine;
                i++;
            }
            buf.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
		
		System.out.println(i);
		System.out.println(myArray.length);
		String[] a = new String[i];
        for(int j=0; j < i; j++){
        	a[j] = myArray[j];
        }
        
		//System.out.println(Arrays.toString(a));
		long start = System.currentTimeMillis();
		sort(a);
		long end = System.currentTimeMillis();
		show(a);
		System.out.println(end-start);	
	}
}
