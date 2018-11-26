#include<iostream>
#include<string.h>
using namespace std;
	char str1[2001];
	char str2[2001];
     
	int dp[2001][2001]; 
    

int main(){

	int t;
	cin>>t;
	while(t--){
	cin>>str1>>str2;
	
	int d1,d2,d3,i,j,len1,len2;
	 len1=strlen(str1);
	 len2=strlen(str2);
	for( i=0;i<=len1;i++)
	   dp[i][0]=i;
    for( j=1;j<=len2;j++)
       dp[0][j]=j;
     for( i=1;i<=len1;i++){
     	for( j=1;j<=len2;j++){
     		d1=((str1[i-1]==str2[j-1])?0:1)+dp[i-1][j-1];//substitution-->if last character same dont do anything(0) else replace last char(1
            d2=dp[i][j-1]+1;  //  convert (s+ch1) to (t+ch2) by inserting in ch2. so dp (s+ch1,t)+1 +1 for ch2 insertion
			 //insertion-->str2 of j-1 length is converted to 
		    d3=dp[i-1][j]+1;//deletion -->convert (s+ch1) to (t+ch2) by deleting ch1 from s.so dp[s,t+ch2]+1 +1 for ch1 deletion
            //finding minimum of 3
			if(d1<d2&&d1<d3)
               dp[i][j]=d1;
            else{
            	if(d2<d3)
            	   dp[i][j]=d2;
         	     else
         	     dp[i][j]=d3;
            }
     	}
     	
     	
     	
     }
     cout<< dp[len1][len2];
	cout<<endl;
	
	}
	
	
	
	
}
