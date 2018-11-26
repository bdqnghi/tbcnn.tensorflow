
public class Selectionsort {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int test[] = {20, 30, 40, 50, 10};
		int i,j, temp;
		System.out.println("���� ��");	
		for(i=0;i<5;i++){
			System.out.println((i+1) + "��° ������" + test[i]);
		}
	 	for(i=0;i<4;i++){
			for(j=i+1; j<5; j++)
			{
				if(test[i] < test[j])
				{
					temp = test[i];
					test[i] = test[j];
					test[j] = temp;
				}
			}
		}
	 	System.out.println("=====================");
	 	System.out.println("=====================");
		System.out.println("���� ��");
		for(i=0;i<5;i++)
	 	{
			System.out.println((i+1) + "��° ������" + test[i]);
		}
	}
}
