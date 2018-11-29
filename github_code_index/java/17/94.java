package hodgepodge;
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashSet;
import java.util.LinkedHashSet;
import java.util.List;
import java.util.Set;
import java.util.TreeSet;
import java.util.Random;
public class Unique {
//	Generate all random integers within certain range without duplicates
	public static ArrayList<Integer> gene_random_unique(int max){
		ArrayList<Integer> list = new ArrayList<Integer>();
		for (int i = 0; i < max; ++i){
			list.add(i+1);
		}
		Collections.shuffle(list);
		return list;
	}
//  Generate the specified amount of random integers within certain range
	public static ArrayList<Integer> gene_random(int max, int numbersNeeded){
		ArrayList<Integer> numbers_list = new ArrayList<Integer>();
		Random rng = new Random();
		if (max < numbersNeeded){
			System.out.println("This will generate random numbers with duplicates");
			while (numbers_list.size()< numbersNeeded){
				Integer next = rng.nextInt();
				numbers_list.add(next);
			}
		}else{
			System.out.println("This will generate random numbers without duplicates");
			Set<Integer> numbers_set = new LinkedHashSet<Integer>();
			while (numbers_set.size()<numbersNeeded){
				Integer next = rng.nextInt();
				numbers_set.add(next);
			}
			numbers_list.addAll(numbers_set);	
		}
		return numbers_list;
	}
//	The function to pick up unique numbers
	public static ArrayList<Integer> get_unique(ArrayList<Integer> numbers){
		ArrayList<Integer> list =  new ArrayList<Integer>();
		Collections.sort(numbers);
		int L;
		int R;
		for (L = 0, R = 0;R < numbers.size(); ++R){
			if (numbers.get(R) != numbers.get(L)){
				list.add(numbers.get(L));
				L=R;
			}
		}
		if (numbers.size()>0){
			list.add(numbers.get(L));
		}
		return list;
	}
	public static void main(String[] args){
	ArrayList<Integer> list = gene_random(10000,300000);
//	Java自带的Set接口有两种实现类
//	1)TreeSet红黑树抽象数据结构
//	放入和查找的时间复杂度均为对数时间O(logM)(当前M个元素)
//	总时间复杂度为线性对数时间O(nlogn)
//	空间复杂度为线性空间O(n)
	long start = System.currentTimeMillis();
	Set<Integer> set_tree = new TreeSet<Integer>();
	for (int i = 0; i < list.size(); ++i){
		set_tree.add(list.get(i));
	}
	long end = System.currentTimeMillis();
	System.out.println("Red-Black-Tree Total Time Cost:"+(end-start));
//	2)HashSet散列表抽象数据结构
//	放入和查找的期望时间复杂度为常数时间O(1)
//	放入和查找的最坏情况时间复杂度分别为常数时间O(1)和线性时间O(M)（当前M个元素）
//	最坏情况下总时间复杂度为O(n^2)
//	为了保证效率，往往需要开辟比TreeSet更大空间
	start = System.currentTimeMillis();
	Set<Integer> set_hash = new HashSet<Integer>();
	for (int i = 0; i < list.size(); ++i){
		set_hash.add(list.get(i));
	}
	end = System.currentTimeMillis();
	System.out.println("HashSet Time Cost:"+(end-start));
//	3)User-defined
//	应用了排序预处理+双边界控制
//	其时间复杂度为O(nlogn)，但与上述抽象数据结构实现方法不同
//	该算法为就地算法，不需要开辟新内存空间
	start = System.currentTimeMillis();
	ArrayList<Integer> result = get_unique(list);
	end = System.currentTimeMillis();
	System.out.println("User-defined Time Cost:"+(end-start));
	}
}
