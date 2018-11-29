/**
*shell�����C����ʵ��
*@time 2017��1��5�� 21:06
*just for practice
*/

#include<stdio.h>
void printArr(int *insertSortArr,int len);
void shellMoveArr(int *arr,int from,int to,int dk);
void shellInsertSort(int *insertSortArr,int len,int start,int dk);
void shellSort(int *sortArr,int len);



/**
*��ӡ����
*@param insertSortArr Ҫ���в�������������ָ��
*/
void printArr(int *insertSortArr,int len){

	for(int i=0;i<len;i++){

		printf("%5d",insertSortArr[i]);

	}

	printf("\n");
}

int main(){

	int sortArr[]={2,5,3,1,8,4,6,0};
	int len=sizeof(sortArr)/sizeof(sortArr[0]);

	shellSort(sortArr,len);
	printArr(sortArr,len);
	getchar();

	return 0;


}

/**
*����shell����
*@param int* sortArr Ҫ����shell����������ָ��
*@param int len ����ĳ���
*/
void shellSort(int *sortArr,int len){

	int dk=len;//����
	int i=0;

	while(true){
		
		
		dk=dk/2;	 //������
		dk>=1?dk:1;

		for(i=0;i<len;i=i++ ){

			shellInsertSort(sortArr,len,i,dk);

		}
		
		if(dk==1){
			break;
		}

	}
}


/**
*@param int * insertSortArr Ҫ����shell��������������ָ��
*@param int len ����ĳ���
*@param int start ��ʼ��λ��
*@param int dk ����
*/
void shellInsertSort(int *insertSortArr,int len,int start,int dk){

	int j=0;int temp=0;

	for(int i=start+dk;i<len;i=i+dk){

		j=i-dk;

		while(j>=start){

			if(insertSortArr[i]>=insertSortArr[j]){

				//j+dk j+2dk �� i-dk �������ƶ� dk λ  i �� j+dk (����dk)

				shellMoveArr(insertSortArr,j+dk,i,dk);

				break;

			}else{
				//Ҫ������� �ȵ�ǰС

				if(j==start){
					//����С�Ļ�С

					//0 0+dk 0+2dk��i-1 ����ƶ� dk λ  i dao 0
					shellMoveArr(insertSortArr,start,i,dk);
					break;

				}else{

					j=j-dk;

				}

			}	

		}

	}

}

/**
*����ƶ����� ��from��to-1 ����ƶ�dkλ
*��to�ƶ���from
*@param int* arr Ҫ����������
*@param int form �����￪ʼ�ƶ�
*@param int to		�ƶ���
*@param int to		����
*/
void shellMoveArr(int *arr,int from,int to,int dk){


	int temp=0;

	//from �� to-dk �������ƶ� ���� λ (����dk)

	temp=arr[to];//����to��ֵ

	for(int k=to-dk;k>=from;k=k-dk){

		arr[k+dk]=arr[k];


	}

	//ito �� from �� λ��
	arr[from]=temp;
}