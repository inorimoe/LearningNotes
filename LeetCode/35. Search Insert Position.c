int searchInsert(int* nums, int numsSize, int target) {
    int left = 0 , right = numsSize-1,mid;
    while(left<=right){
        mid = left + (right - left)/2;
        if(target<nums[mid])
        {
            right = mid - 1 ;
        }
        else if(nums[mid]<target)
        {
            left = mid + 1 ;
        }
        else
            return mid;//找到
    }
    if(nums[mid]<target)//找不到
        return mid+1;
    else
        return mid;
}