package ASSIGNMENT4;


public class selectionsort {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int a[]={23,12,40,2,37};
	   selsort(a);
	}

	public static void selsort(int a[]){
		int n=a.length;
		int temp;
		int pos=0;
		for(int i=0;i<n;i++){
			for(int j=i+1;j<n;j++){
				if(a[i]>a[j])
					pos=j;
			}
		   temp=a[i];
		   a[i]=a[pos];
		   a[pos]=temp;
		}
      
		 System.out.println("the sorted array is ");
		 for(int i=0;i<n;i++){
			 System.out.print(a[i]+ " ");
		 }
	}

}
