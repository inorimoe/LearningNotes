#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#define getArrayLen(array) (sizeof(array)/sizeof(array[0]))
void bitSum(int A[],int B[],int S[],int n)
{
    for(int i = 0;i<n+1;i++)
    {
        S[i]=0;
    }
    for(;n>0;n--)
    {
        S[n] = A[n-1] + B[n-1] + S[n];
        switch(S[n])
        {
            case 0:S[n]=0;break;
            case 1:S[n]=1;break;
            case 2:S[n]=0;S[n-1]=1;break;
            case 3:S[n]=1;S[n-1]=1;break;
            default:break;
        }
    }
}
int main(int argc, char const *argv[])
{
    // AB为n位，S为n+1位
    int A[100];
    int B[100];
    int S[101];
    int n=getArrayLen(A);
    //写入
    srand((unsigned int)time(NULL));
    for(int j=0;j<n;j++)
    {
        A[j]=rand()%2;
        B[j]=rand()%2;
    }
    //计算
    bitSum(A,B,S,n);
    //打印
    printf(" ");
    for(int j=0;j<n;j++)
    {
        printf("%d",A[j]);
    }
    printf("\n ");
    for(int j=0;j<n;j++)
    {
        printf("%d",B[j]);
    }
    printf("\n");
    for(int j=0;j<n+1;j++)
    {
        printf("%d",S[j]);
    }
    return 0;
}
