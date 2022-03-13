class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ret;
        sort(nums.begin(), nums.end());
        int target;
        int lo;
        int hi;
        for(int i=0; i < nums.size(); ++i){
            target = -nums[i];
            if(target < 0) break;
            lo = i+1;
            hi = nums.size() - 1;
            while(lo < hi){
                int sum = nums[lo] + nums[hi];
                if(sum < target){
                    ++lo;
                } else if( sum > target){
                    --hi;
                } else {
                    vector<int> triplet{nums[i], nums[lo], nums[hi]};
                    ret.emplace_back(triplet);
                    while(lo < hi && nums[lo] == triplet[1]) ++lo;
                    while(lo < hi && nums[hi] == triplet[2]) --hi;
                }
            }
            while(i < nums.size()-1 && nums[i] == nums[i+1]) ++i;
        }
        return ret;
    }
};
