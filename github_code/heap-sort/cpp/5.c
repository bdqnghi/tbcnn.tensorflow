#include <stdio.h>
//array�Ǵ������Ķ����飬i�Ǵ�����������Ԫ�ص�λ�ã�nlength������ĳ���
//�����������ǣ���������array���������
void HeapAdjust(int array[], int i, int nLength)
{
	int nChild;
	int nTemp;
	for(; 2*i+1<nLength; i=nChild)
	{
		//�ӽ���λ��=2*�������λ�ã�+1
		nChild=2*i+1;
		//�õ��ӽ���нϴ�Ľ��
		if(nChild<nLength-1 && array[nChild+1]>array[nChild])
			++nChild;
		//����ϴ���ӽ����ڸ������ô�ѽϴ���ӽ�������ƶ����滻���ĸ����
		if(array[i]<array[nChild])
		{
			nTemp = array[i];
			array[i] = array[nChild];
			array[nChild] = nTemp; 
		}
		else break; //�����˳�ѭ��
	}
}
//�������㷨
void HeapSort(int array[], int length)
{
	int i;
	//�������е�ǰ�벿��Ԫ�أ�������֮���һ��Ԫ�������е�����Ԫ��
	//length/2-1�����һ����Ҷ�ڵ㣬�˴�"/"Ϊ����
	for(i=length/2-1; i>=0; --i)
		HeapAdjust(array, i, length);

	for(i=0; i<length; i++)
	{
		printf("%d ", array[i]);
	}
	printf("\n");
	
	//�����һ��Ԫ�ؿ�ʼ�����н��е��������ϵ���С�����ķ�Χֱ����һ��Ԫ��
	for(i=length-1; i>0; --i)
	{
		//�ѵ�һ��Ԫ�غ͵�ǰ�����һ��Ԫ�ؽ�����
		//��֤��ǰ�����һ��λ�õ�Ԫ�ض��������ڵ��������֮������
		array[i] = array[0]^array[i];
		array[0] = array[0]^array[i];
		array[i] = array[0]^array[i];
		//������С����heap�ķ�Χ��ÿһ�ε�����ϱ�֤��һ��Ԫ���ǵ�ǰ���е����ֵ
		HeapAdjust(array,0,i);
	}
}

int main()
{
	int i;
	int num[] = {4,7,8,6,5,2,3,0,1,9};
	HeapSort(num,sizeof(num)/sizeof(int));
	for(i=0; i<sizeof(num)/sizeof(int); i++)
	{
		printf("%d ",num[i]);
	}
	printf("\nok\n");
	return 0;
}