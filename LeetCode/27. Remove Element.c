int removeElement(int* nums, int numsSize, int val) {
    int *insert = nums;
    for(int i = 0;i<numsSize;++i)
    {
        if(nums[i]!=val)
        {
            *insert++ = nums[i];
        }
    }
    return insert-nums;
}