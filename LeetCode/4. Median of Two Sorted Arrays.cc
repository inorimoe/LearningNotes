//第一次用堆排AC，不是最优解
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