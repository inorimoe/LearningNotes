//中心扩展法
/*
回文中心的两侧互为镜像。
因此，回文可以从他的中心展开，并且只有 2n-1 个这样的中心
（一个元素为中心的情况有 n 个，两个元素为中心的情况有 n-1 个）
*/
class Solution {
public:
    string longestPalindrome(string s) {
        if(s.size()<2)
            return s;
        for(int i=0;i<s.size();++i){
            findPalindromic(s,i,i);
            findPalindromic(s,i,i+1);
        }
        return s.substr(startPos,maxLen);
    }
private:
    int startPos=0,maxLen=0;
    void findPalindromic(string& s,int left,int right){
        while(left>=0 && right<s.size() && s[left] == s[right]){
            left--;
            right++;
        }
        if(right-left-1 > maxLen){
            maxLen = right-left-1;
            startPos = left+1;
        }
    }
};