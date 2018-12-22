package sortAlg;

import java.util.ArrayList;
import java.util.List;

public class Bucket {
	public  static List<Integer>  sort(int[] array){
		List<Integer> out=new ArrayList<Integer>();
		Integer[] b=new Integer[1000];//����һ��ľͰ�������
		for (int i = 0; i < array.length; i++) {
			if(b[array[i]]==null){
				b[array[i]]=1;
			}else{
				b[array[i]]++;
			}
			
		}
		for (int j = 0; j < b.length; j++) {
			if(b[j]!=null){
				for (int k = 0; k< b[j]; k++) {
					out.add(j);
				}
			}
		}
		return out;
	}
   public static void main(String[] args) {
	  List<Integer> p= sort(new int[]{2,7,3,6,4,9,1,3,5});
	  for (int i = 0; i < p.size(); i++) {
		  System.out.print(p.get(i)+",");
	}
	  
   }
}
