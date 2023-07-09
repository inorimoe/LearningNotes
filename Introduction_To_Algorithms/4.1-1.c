/*猜测会返回一个最大的负数*/
//此处代码可显示归并节点的状态
#include<stdio.h>
#include<limits.h>
typedef struct vector{
    int left;
    int right;
    int sum;
    } vec;
vec max;
vec findMaximumSubarray(int*,int,int);
vec findMaxCrossingSubarray(int*,int,int,int,vec);
int main(int argc, char const *argv[])
{
    int vector[10]={-2,-3,-4,-5,-6,-7,-8,-9,-1,-10};
    max = findMaximumSubarray(vector,0,9);
    printf("%d %d %d",max.sum,max.left,max.right);
    return 0;
}
vec findMaxCrossingSubarray(int* vector,int low,int mid,int high,vec C)
{
    int maxLeft = INT_MIN;
    int maxRight = INT_MIN;
    int sum = 0;
    for(int i=mid;low<=i;--i)
    {
        sum+=vector[i];
        if(sum>maxLeft)
        {
            maxLeft=sum;
            C.left=i;
        }
    }
    for(int i=mid+1,sum = 0;i<=high;++i)
    {
        sum+=vector[i];
        if(sum>maxRight)
        {
            maxRight=sum;
            C.right=i;
        }
    }
    C.sum = maxLeft+maxRight;
    //printf("csum:%d cleft:%d cright:%d\n",C.sum,C.left,C.right);
    return C;
}
vec findMaximumSubarray(int* vector,int low,int high)
{
    //printf("low:%d high:%d\n",low,high);
    vec L,C,R;
    if(low == high)
    {
        max.left=low;
        max.right=high;
        max.sum=vector[low];
        return max;
    }
    else
    {
        L = findMaximumSubarray(vector,low,low+(high-low)/2);
        //printf("lsum:%d lleft:%d lright:%d\n",L.sum,L.left,L.right);
        R = findMaximumSubarray(vector,low+(high-low)/2+1,high);
        //printf("rsum:%d rleft:%d rright:%d\n",R.sum,R.left,R.right);
        C = findMaxCrossingSubarray(vector,low,low+(high-low)/2,high,C);
        if(L.sum>=C.sum&&L.sum>=R.sum)
            return L;
        else if(C.sum>=L.sum&&C.sum>=R.sum)
            return C;
        else
            return R;
    }
}