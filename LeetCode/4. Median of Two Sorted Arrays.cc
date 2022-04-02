//第一次用堆排AC，不是最优解；
//没有看到是排序数组就一把ac了= =！ 
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        priority_queue<int> pq;
        double ret = 0;
        for(auto i : nums1){
            pq.push(i);
        }
        for(auto i : nums2){
            pq.push(i);
        }
        if( pq.size() % 2 == 0){
            int closeMid = pq.size()/2 -1;
            for(int i=0;i<closeMid;++i)
                pq.pop();
            ret = pq.top();
            pq.pop();
            ret = (ret + pq.top())/2;
        } 
        else if(pq.size() % 2 == 1){
            int mid = pq.size()/2;
            for(int i=0;i< mid;++i)
                pq.pop();
            ret = pq.top();
        }
        return ret;
    }
};

//官方题解，最优解
class Solution {
public:
    double findMedianSortedArrays(vector<int>& arr1, vector<int>& arr2) {
        if(arr1.size() > arr2.size())
            return findMedianSortedArrays(arr2, arr1);
        int lo = 0;
        int hi = arr1.size();
        int i = 0;
        int j = 0;
        int m = arr1.size();
        int n = arr2.size();
        int midA = 0;
        int midB = 0;
        while(lo <= hi){
            i = (lo + hi) / 2;
            j = (m + n + 1) / 2 - i;
            int mid_i = (i < m ? arr1[i] : INT_MAX );
            int mid_im1 = (0 < i ? arr1[i-1] : INT_MIN );
            int mid_j = (j < n ? arr2[j] : INT_MAX );
            int mid_jm1 = ( 0 < j ? arr2[j-1] : INT_MIN);
            if (mid_im1 <= mid_j){
                midA = max(mid_jm1, mid_im1);
                midB = min(mid_i, mid_j);
                lo = i+1;
            } else {
                hi = i-1;                
            }
        }
        return (m+n)&1 ? midA : (midA + midB)/2.0 ;
    }
};