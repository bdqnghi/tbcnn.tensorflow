	

	

	

	#include <bits/stdc++.h>
	#define MAX_ROW	100
	#define MAX_COL 110
	#define MAX 110
	using namespace std;

	int main(){
		int t;
		int a[MAX_ROW][MAX_COL];
		for(int i=0; i<MAX_ROW; i++){
			a[i][0]=0;
		}
		for(int j=0; j<MAX_COL; j++){
			a[0][j]=0;
		}

		cout<<"No of test cases: ";
		cin>>t;

		while(t--){

			int len;
			cout<<"Enter the length of the rod : ";
			cin>>len;

			int n;
			cout<<"Enter no of cutting possibilities: ";
			cin>>n;

			int val[MAX];

			for(int i=1; i<=n; i++){
				cout<<"Enter the profit value of a piece of length "<<i<<": ";
				cin>>val[i];
			}



			for(int i=0; i<=n; i++){
				for(int j=0; j<=len; j++){

					if(i>j){
						a[i][j]=a[i-1][j];
					}
					else{
						if(i==1){
							a[i][j]=val[i]*j;
						}

						
						else{
								a[i][j]=max(a[i-1][j] , val[i]+a[i][j-i]);
						}
						

					}
					if(i>0)
						printf(" %d  ", a[i][j]);
				}
				if(i>0)
					printf("\n\n");
			}

                
			int k=0;
			int sizes[MAX];
			int row = n;
			int col = len;

			while(row && col){
				if(a[row][col]==a[row-1][col]){
					row--;
				}
				else{
					sizes[k++]=row;
					col=col-row;
				}
			}

			cout<<"The required max possible profit is :"<<a[n][len]<<endl;

			cout<<"And the sizes are : ";
			for(int i=0; i<k; i++){
				printf("%d, ", sizes[i]);
			}

			cout<<endl<<endl;
		}

		return 0;
	}

