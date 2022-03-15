class Solution {
public:
    const vector<string> pad = {
        "", "", "abc", "def", "ghi", "jkl",
        "mno", "pqrs", "tuv", "wxyz"
    };
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) return {};
        vector<string> ret;
        queue<string> que;
        que.push(string());
        for(int i = que.front().size(); i < digits.size(); i = que.front().size()){
            string ss = que.front();
            que.pop();
            auto& vstr = pad[digits[i] - '0'];
            for(auto ch : vstr){
                que.push(ss + ch);
            }
        }
        while(!que.empty()){
            ret.push_back(que.front());
            que.pop();
        }
        return ret;
    }
};