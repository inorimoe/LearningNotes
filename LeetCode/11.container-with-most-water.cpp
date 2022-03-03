/*
 * @lc app=leetcode id=11 lang=cpp
 *
 * [11] Container With Most Water
 */

// @lc code=start
class Solution {
public:
    int maxArea(vector<int>& height) {
        int area (0);
        int left = 0;
        int right = height.size() - 1;
        int h = 0;
        while(left < right){
            h = min(height[left], height[right]);
            area = max(area, h*(right - left));
            while(height[left] <= h && left < right) left++;
            while(height[right] <= h && left < right) right--;
        }
        return area;
    }
};
// @lc code=end

