package T5;

public class ShellSort {
	int a[];
	public ShellSort() {
		a = new int[]{3,7,5,2,6};
		
		
		/*
		 * 第一次是d=5组
		 * （8,99），（19,1000），（2,888），（3，-1），（100,0）
		 * 交换
		 * （8,99），（19,1000），（2,888），（-1,3），（0,100）
		 * 8,19,2，-1,0,99,1000,888,3,100
		 * 第二次是d=2组
		 * (8,2,0,1000,3),(19,-1,99,888,100)
		 * 交换
		 * (0,2,3,8,1000),(-1,19,99,100,888)
		 * 0,-1,2,19,3,99,8,100,1000,888
		 * 第3次是d=1时，其实只有一组，就是直接插入排序
		 * 
		 * 
		 * */
	}
	public ShellSort(int a[]) {
		this.a = a;
	}
	
	public void shellSort(){
		int n = a.length;
		/*分组排序：分组的规则 d为增量
		 * 1.d = 数组长度/2;
		 * 2.d = d/2;
		 * 
		 */
		for(int d=n/2;d>0;d/=2){
			System.out.println("d="+d+"时的排序情况");
			//插入排序
			for(int i=0;i<d;i++){ //增量为1时排序结束
				//遍历所有子序
				System.out.print("i值:"+i+"\t");
				for(int j=i+d;j<n;j+=d){
					System.out.print("j值："+j+"\t");
					//对每个子序进行插入排序
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
		System.out.println("排序前");
		shellSort.print();
		shellSort.shellSort();
//		shellSort.print();
	}
}
