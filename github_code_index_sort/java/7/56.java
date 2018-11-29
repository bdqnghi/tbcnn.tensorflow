package T5;
//ϣ������
public class ShellSort {
	int a[];
	public ShellSort() {
		a = new int[]{8,19,2,3,100,99,1000,888,-1,0};
		/*
		 * ��һ����d=5��
		 * ��8,99������19,1000������2,888������3��-1������100,0��
		 * ����
		 * ��8,99������19,1000������2,888������-1,3������0,100��
		 * 8,19,2��-1,0,99,1000,888,3,100
		 * �ڶ�����d=2��
		 * (8,2,0,1000,3),(19,-1,99,888,100)
		 * ����
		 * (0,2,3,8,1000),(-1,19,99,100,888)
		 * 0,-1,2,19,3,99,8,100,1000,888
		 * ��3����d=1ʱ����ʵֻ��һ�飬����ֱ�Ӳ�������
		 * 
		 * 
		 * */
	}
	public ShellSort(int a[]) {
		this.a = a;
	}
	
	public void shellSort(){
		int n = a.length;
		/*�������򣺷���Ĺ���
		 * 1.d = ���鳤��/2;
		 * 2.d = d/2;
		 * 
		 */
		for(int d=n/2;d>0;d/=2){
//			System.out.println("d="+d+"ʱ���������");
			//��������
			for(int i=0;i<d;i++){ //����Ϊ1ʱ�������
				//������������
//				System.out.print(i+"\t");
				for(int j=i+d;j<n;j+=d){
//					System.out.print(j+"\t");
					//��ÿ��������в�������
					int insertNode = a[j];
					int k=j-d;
					while(k>=i&& a[k]>insertNode){
						a[k+d]=a[k];
						k=k-d;
//						print();
					}
					a[k+d]=insertNode;
//					print();
				}
//				System.out.println("--------------------");
				
			}
//			print();
		}
		print();
	}
	public void print(){
		for (int e : a) {
			System.out.print(e+"\t");
		}
		System.out.println("");
	}
	public static void main(String[] args) {
		ShellSort shellSort = new ShellSort();
		System.out.println("����ǰ");
		shellSort.print();
		shellSort.shellSort();
//		shellSort.print();
	}
}
