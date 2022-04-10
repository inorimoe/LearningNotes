class Solution {
public:
    // 用需要两层判断的二分查找，有点顶
    int search(vector<int>& nums, int target) {
        int lo = 0;
        int hi = nums.size()-1;
        int mid;
        while(lo <= hi){
            mid = lo + (hi-lo)/2;
            if(nums[mid] == target){
                return mid;
            }
            else if(nums[lo] < nums[mid]){
                if(nums[lo] <= target && target < nums[mid] ){
                    hi = mid-1;
                } else {
                    lo = mid+1;
                }
            }
            else if(nums[lo] > nums[mid]){
                if(target <= nums[hi] && nums[mid] < target ){
                    lo = mid + 1;
                } else {
                    hi = mid - 1;
                }
            }
            else{
                lo++;
            }
        }
        return -1;
    }
};