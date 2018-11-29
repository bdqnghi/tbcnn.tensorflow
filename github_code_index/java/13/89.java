package package2;

/**
 * ϣ������
 * ���ڲ������򣬽�����Ӧ�õ���������Ȼ���𽥼�С������ϣ������ͨ���Ӵ�������Ԫ��֮��ļ��������Щ�м���Ԫ���н��в�������
 * �Ӷ�ʹ�������ܴ��ȵ��ƶ�<ÿ��n��Ԫ�ؽ�������>������Щ�������Ź�һ����֮��ϣ�������㷨��С������ļ���ٽ�������
 * �����ν�����ȥ��
 * ������в���Knuth����ģ�h = 3*h+1;�����кܳ��á�
 * Ч�ʣ�ʱ�伶��O(N^2/3)~O(N^7/6)
 */
public class ShellSort {
	
	private int[] a;
	private int curLoc,size;
	
	public ShellSort(int max){
		size = max;
		a = new int[max];
		curLoc = 0;
	}
	
	public void insert(int ele){
		a[curLoc++]=ele;
	}

	private void shellSort(){
		int h=1,inner,outter,temp;
		while(h<=curLoc/3){//h�Ǽ��,�ں���ļ����У�h��ֵ�ǲ����
			h=3*h+1;
		}
		while(h>0){
			for(outter = h;outter<curLoc;outter++){//outter���������ƶ�
				//a[outter]�Ǳ��Ԫ�أ��ڲ��������У����Ԫ���Ҳ��Ǵ������Ԫ��
				temp = a[outter];
				inner = outter;//innner>=h
				//inner>h-1��֤inner-h>0
				while(inner>h-1 && a[inner-h]>=temp){
					a[inner] = a[inner-h];
					inner -= h;
				}
				a[inner]=temp;//�ҵ����m��λ�ã�����
			}
			h=(h-1)/3;
		}
		
	}
	
	public void println(){
		for(int i=0;i<size;i++){
			System.out.println(a[i]+"^^^^");
		}
	}
	
	public static void main(String[] args) {
		ShellSort shellSort = new ShellSort(10);
		shellSort.insert(2);
		shellSort.insert(23);
		shellSort.insert(1);
		shellSort.insert(43);
		shellSort.insert(4);
		shellSort.insert(3);
		shellSort.insert(5);
		shellSort.insert(6);
		shellSort.insert(0);
		shellSort.insert(7);
		shellSort.shellSort();
		shellSort.println();
	}

}
