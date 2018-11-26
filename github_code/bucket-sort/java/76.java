package wit.lk.algorithm.ch03;

public class BucketSort {
	private int[] buckets;
	private int[] array;
	
	public BucketSort(int range,int[] array){
		buckets = new int[range];
		this.array = array;
	}
	
	/**
	 * ����
	 */
	public void sort(){
		if(array != null && array.length > 1){
			for(int i = 0; i < array.length; i++){
				buckets[array[i]]++;
			}
		}
	}
	
	/**
	 * �Ӵ�С����
	 */
	public void print(){
		//�����������
		for(int i = buckets.length - 1; i >= 0; i--){
			for(int j = 0; j < buckets[i]; j++){
				System.out.println(i);
			}
		}
	}
}
