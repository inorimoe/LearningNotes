#include <algorithm>
class Solution {
public:
    //太菜，用标准库函数实现
    vector<int> searchRange(vector<int>& nums, int target) {
        int lowIndex = -1;
        int maxIndex = -1;
        bool targetExist=std::binary_search(nums.begin(),nums.end(),target);
        if(targetExist){
            auto lowPtr = std::lower_bound(nums.begin(),nums.end(),target);
            auto maxPtr = std::upper_bound(nums.begin(),nums.end(),target);
            if(lowPtr != nums.end()) 
                lowIndex = lowPtr-nums.begin(),  
                maxIndex = maxPtr-nums.begin()-1;
        } 
        return {lowIndex, maxIndex};
    };
};