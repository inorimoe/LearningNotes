int removeDuplicates(int* nums, int numsSize) {
    int *insert,*pop;
    insert = pop = nums;
    if(!numsSize)return 0;
    for(int i = 0;i<numsSize-1;++i)
    {
        ++pop;
        if(*insert<*pop)
        {
            *(++insert) = *pop;
        }
    }
    return insert-nums+1;
}