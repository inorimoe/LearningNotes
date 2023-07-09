//查找最大子数组的线性时间算法
#include<stdio.h>
#include<stdlib.h>
struct vector{
    int max;
    int left;
    int right;
} vec;
linearSearchMaximumArray(int* arr,int len)
{
    int sum = 0;
    int stmaximum = 0;
    for(int i = 0; i < len; i++)
    {
        sum +=arr[i];
        if(sum>vec.max)
        {
            vec.max = sum;
            vec.right = i;
            vec.left = stmaximum;
        }
        if(sum<0)
        {
            sum = 0;
            stmaximum = i+1;
        }
    }
}
int main(int argc, char const *argv[])
{
    int a[10] = {1,-3,4,-1,1,2,4,-2,6,-5};
    memset(&vec,0,sizeof(struct vector));
    linearSearchMaximumArray(a,10);
    printf("sumMax:%d,sumMax_left:%d,sumMax_right:%d",vec.max,vec.left,vec.right);
    //输出最大子数组，及其左右下标的位置。
    return 0;
}
