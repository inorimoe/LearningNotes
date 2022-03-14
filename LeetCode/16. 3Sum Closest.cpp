class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int lo, hi, ret;
        int clst = INT_MAX; 
        int sum;
        for(int i = 0; i < nums.size()-2; ++i){
            lo = i + 1;
            hi = nums.size() -1;
            while(lo < hi){
                sum = nums[i] + nums[lo] + nums[hi];
                if(abs(sum - target) < clst){
                    clst = abs(sum - target);
                    ret  = sum ;
                }
                if(sum < target) ++lo; 
                else if(target < sum) --hi;
                else return ret;
            }
        }
        return ret;
    }
};