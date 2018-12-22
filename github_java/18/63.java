package �㷨����;

/**
 * ���Ĺ���ԭ����ÿһ�δӴ����������Ԫ����ѡ����С������󣩵�һ��Ԫ�أ���������е���ʼλ�ã�ֱ��ȫ�������������Ԫ������
 * @author Administrator
 *SELECTION-SORT(A)
       n =A:length
       for j = 1 to n  1
         smallest = j
         for i = j + 1 to n
            if A[i]<A[smallest]
                smallest = i
         exchange A[j] with A[smallest]
     ʱ�临�Ӷȣ� O(N^2), �ȽϵĴ�����n(n-1)/2
     ��õ������������,����0��,��������n-1��(ʵ�ʽ�����ֵ��λ��,��������ʱ����)
     ���򽻻�n/2��,����������ð��������,���ڽ�������cpuʱ��ȱȽ������Cpuʱ���,nֵ��С,ѡ�������ð�������
  �ȶ��ԣ�
  ѡ�������Ǹ�ÿ��λ��ѡ��ǰԪ����С��,�������һ��λ��ѡ����С��,��ʣ��Ԫ��������ڶ���Ԫ��ѡ��ڶ�С��,��������,ֱ����n-1��Ԫ��,
  ��n��Ԫ�ز���ѡ����,��Ϊֻʣ����һ������Ԫ����;��ô,��һ��ѡ��,���һ��Ԫ�رȵ�ǰԪ��С,����С��Ԫ���ֳ�����һ���͵�ǰԪ����ȵ�Ԫ�غ���,
  ��ô�������ȶ��Ծͱ��ƻ���;�Ƚ��ֿ�,�ٸ�����,����5 8 5 2 9,����֪����һ��ѡ���1��Ԫ��5���2����,��ôԭ����������5�����ǰ��˳��ͱ��ƻ���,����ѡ��������һ�����ȶ��������㷨
 */
public class Selection {
	
	public static Integer[] select(Integer[] ints){
		
		int length = ints.length;
		for(int j=0; j<length-1; j++){
			int smallest = j;
			for(int i=j+1; i<length; i++){
				if(ints[i] < ints[smallest]){
					smallest = i;
				}
			}
			int temp = ints[smallest];
			ints[smallest] = ints[j];
			ints[j] = temp;
		}
		
		
		return ints;
		
		
	}
	
	public static void main(String[] args) {
		
		Integer[] ints = {2,1,5,9,4,6,8,3};
		ints = select(ints);
		for(int i : ints){
			System.out.print(i);
		}
	}

}










