import java.util.*;
/**
20150108
sort
non-recursion sort
*/ 

public class A11_Sort_bubbleSort{
	public static void main(String[] args){
		A11_Sort_bubbleSort s = new A11_Sort_bubbleSort();
	//	s.input();
		s.print();
		s.bubbleSort();
		s.print();
	}
	int[] a = new int[1000];
	int length;
	A11_Sort_bubbleSort(){
		a[0] =5;
		a[1] =2;
		a[2] =3;
		a[3] =43;
		a[4] =65;
		a[5] =23;
		a[6] =456;
		a[7] =123;
		a[8] =58;
		a[9] =11;
		length =10;
		
	}
	public void input(){
		System.out.println("\n-------------------input-start---end for 0--------------\n");
		Scanner scan = new Scanner(System.in);
		int i=0;
		a[i]=scan.nextInt();
		while(a[i]!=0&&scan.hasNextInt()){
			i++;
			a[i]=scan.nextInt();	
		}
		length = i;
		System.out.println("length=  "+length);
	}
	public void bubbleSort(){
		for(int i=0; i<length-1;i++){
			for(int j=0;j<length-1-i;j++){
				compare(j,j+1);
			}
		}
	}
	public void compare(int x, int y){
		int z=0;
		if(a[x]>a[y]){
			z=a[x];
			a[x]=a[y];
			a[y]=z;
		}	
	}
	public void print(){
		int i = 0;
		System.out.println("------------------------------------------------------------------\n");
		while(a[i]!=0){
			System.out.print(a[i]+" ");
			i++;		
		}
		System.out.println("\n------------------------------------------------------------------\n");
	}
	
}

