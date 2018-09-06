int* twoSum(int* nums, int numsLen, int sum) {
    int a;
    static int re[2];
    re[0]=re[1]=-1;
    for(int i =0;i<numsLen;++i)
    {
        a = sum - nums[i];
        re[0]=i;
        for(int j=0;j<numsLen;++j)
        {
            if(i==j)continue;
            if(nums[j]==a)
            {
                re[1]=j;
                break;
            }
        }
        if(re[1]!=-1)
            break;
    }
    return re;
}
