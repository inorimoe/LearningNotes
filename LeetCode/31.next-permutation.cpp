/*
 * @lc app=leetcode id=31 lang=cpp
 *
 * [31] Next Permutation
 */

// @lc code=start
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int idx = nums.size() - 1;
        for(;idx-1 > -1 && nums[idx-1] >= nums[idx]; --idx){};
        sort(nums.begin() + idx, nums.end());
        if(idx==0){
            return;
        }
        int jdx = idx;
        for(; nums[jdx] <= nums[idx-1] ; ++jdx){};
        swap(*(nums.begin()+ idx-1),*(nums.begin() + jdx));
        sort(nums.begin() + idx, nums.end());
    }
};
// @lc code=end

