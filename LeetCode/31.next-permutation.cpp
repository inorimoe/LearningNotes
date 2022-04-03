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
//最优解用reverse，画图只想到排序，没想到这个思路
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int idx = nums.size() - 1;
        for(;idx-1 > -1 && nums[idx-1] >= nums[idx]; --idx){};
        reverse(nums.begin() + idx, nums.end());
        if(idx==0){return;}
        int jdx = idx;
        for(; nums[jdx] <= nums[idx-1] ; ++jdx){};
        swap(nums[idx-1], nums[jdx]);
    }
};



