#include<iostream>
void mat_mul(long long int pout[2][2], long long int px[2][2])
{
	int shout[2][2];
	shout[0][0]=( ( (pout[0][0]*px[0][0])%100000) + ( (pout[0][1]*px[1][0])%100000));
	shout[0][1]=( ( (pout[0][0]*px[1][0])%100000) + ( (pout[0][1]*px[1][1])%100000));
	shout[1][0]=( ( (pout[1][0]*px[0][0])%100000) + ( (pout[1][1]*px[1][0])%100000));
	shout[1][1]=( ( (pout[1][0]*px[0][1])%100000) + ( (pout[1][1]*px[1][1])%100000));

	pout[0][0]=shout[0][0]%100000;
	pout[0][1]=shout[0][1]%100000;
	pout[1][0]=shout[1][0]%100000;
	pout[1][1]=shout[1][1]%100000;
}



int main()
{
	int number,temp;
	long long int output[2][2] = {1,0,0,1};
	long long int startX[2][2] = {1,1,1,0};
	std::cin>>number;
	while(number>0){
		temp = number%10;
		if(temp ==1)
			mat_mul(output,startX);
		mat_mul(startX,startX);
		number = number/10;
	}
	std::cout<<output[1][0];
	return 0;
	
}
	
