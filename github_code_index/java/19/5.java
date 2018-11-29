package sort.bucket;

import java.util.Iterator;
import java.util.LinkedList;
import java.util.Queue;

/**
 * ˫��Ͱ�����ȶ���,ÿ�������Ȱ�ÿ��λΪһͰ������Ͱ��ÿһͰ���ٰ�ÿһλΪһͰ
 * @author linjy
 *
 */
public class BucketSort {
	
	private int[] sortArray = null;
	
	private LeafBucket[] buckets = null;
	
	private void initBuckets(){
		buckets = new LeafBucket[8];
		for(int i = 0; i < buckets.length; i++){
			buckets[i] = new LeafBucket(4);
		}
	}
	
	public BucketSort(int[] sortArray){
		this.sortArray = sortArray;
		initBuckets();
	}
	
	private int getSubBucketIndex(int num){
		int bitOff = 3;
		while(bitOff >= 0){
			int offNum = num >> bitOff;
			offNum &= 0x1;
			if(offNum != 0){
				return bitOff;
			}
			bitOff--;
		}
		throw new RuntimeException("subBucketIndex is not found!");
	}
	
	public void sort(){
		for(int sortItem : sortArray){
			int bitOff = 28;
			while(bitOff >= 0){
				int offSortItem = sortItem >> bitOff;
				offSortItem &= 0xF;
				if(offSortItem != 0){
				    LeafBucket leafBucket = buckets[bitOff / 4];
				    int subBucketIndex = getSubBucketIndex(offSortItem);
				    leafBucket.add(subBucketIndex, sortItem);
				    break;
				}
				bitOff -= 4;
			}
		}
		
		for(LeafBucket leafBucket : buckets){
			System.out.println(leafBucket);
		}
	}
	
	private class LeafBucket{
		private Queue<Integer>[] buckets = null;
		
		public LeafBucket(int capacity){
			buckets = new LinkedList[capacity];
			for(int i = 0; i < buckets.length; i++){
				buckets[i] = new LinkedList<Integer>();
			}
		}
		
		public void add(int bucketIndex, int element){
			LinkedList<Integer> queue = (LinkedList<Integer>)buckets[bucketIndex];
			int insertIndex = 0;
			Iterator<Integer> ite = queue.iterator();
			while(ite.hasNext()){
			    int qe = ite.next();
			    if(qe > element){
			    	break;
			    }
			    insertIndex ++;
			}
			queue.add(insertIndex, element);
		}
		
		public String toString(){
			StringBuffer sb = new StringBuffer();
			for(Queue<Integer> queue : buckets){
				if(queue.size() > 0){
					sb.append(queue.toString());
				}
				else{
					sb.append("[]");
				}
			}
			return sb.toString();
		}
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		int[] a = {3424,3432423, 1212312312, 34, 55, 55, 77, 22, 1, 20, 30,66, 67, 68, 88, 10, 100, 9};
		BucketSort bs = new BucketSort(a);
		bs.sort();

	}

}
