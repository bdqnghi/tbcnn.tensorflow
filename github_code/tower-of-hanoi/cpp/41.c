/*AUTHOR - SATYAM RAMAWAT */
#include<stdio.h>
#include<math.h> 
int toh(int, char, char, char);//forward declaration
int main()
{
    int n; 
    printf("Enter the number of disks : ");
    scanf("%d", &n);
    printf("The sequence of moves involved in the Tower of Hanoi are :\n");
    toh(n, 'L', 'R', 'M');
    int f=pow(2,n+1);
    printf("\n\n The number of Function call is : %d",f-1);
    int m=pow(2,n);
    printf("\n Number of disk movements is : %d \n",m-1);
    //return 0;
}

int toh(int num, char left, char right, char mid)
{
    if (num == 1)
    {
        printf("\n Move disk 1 from %c to %c", left, right);
        return 0;
    }
    toh(num - 1, left, mid, right);
    printf("\n Move disk %d from %c to %c", num, left, right);
    toh(num - 1, mid, right, left);
}
