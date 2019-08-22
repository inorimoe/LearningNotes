
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        map<char,int> mp;
        int start = -1;
        int maxLen = 0;
        for(int i = 0;i != s.size(); ++i){
            if(mp.find(s[i]) != mp.end() && start < mp[s[i]]){
                start = mp[s[i]];
            }
            mp[s[i]] = i;
            maxLen = max(maxLen,mp[s[i]] - start);
            
        }
        return maxLen;
    }
};
