//最大子数组问题，使用暴力求解，O（N^2)
#include<limits.h>
#include<stdio.h>
int exponential_2(int*a,int len)
{
    int sum=0;
    int max=INT_MIN;
    for(int i=0;i<len;++i,sum=0)
    {
        for(int j =i;j<len;++j)
        {
            sum+=a[j];
            if(sum>max)
            {
                max = sum;
            }
        }
    }
    return max;
}
int main(int argc, char const *argv[])
{
    int a[10] = {3,-4,7,-5,1,2,-4,6,8,-5};
    printf("%d",exponential_2(a,10));
    return 0;
}