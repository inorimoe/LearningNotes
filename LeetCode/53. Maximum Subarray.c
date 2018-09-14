#include<limits.h>
int maxSubArray(int* nums, int numsSize) {
    int sum = 0;
    int temp = INT_MIN;
    for(int i = 0;i<numsSize;++i)
    {
        sum += nums[i];
        if(temp<sum)
        {
            temp = sum;
        }
        if(sum < 0)
        {
            sum = 0;
        }
    }
    return temp;
}