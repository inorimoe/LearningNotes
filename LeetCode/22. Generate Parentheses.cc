//递归
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> ret;
        generate(ret, "", n , n);
        return ret;
    }
    void generate(vector<string>& vec, string s, int left, int right){
        if(left == 0 && right == 0){
            vec.push_back(s);
            return;
        }
        if(0 < left) generate(vec, s+"(", left-1, right);
        if(left < right) generate(vec, s+")", left, right-1);
    }
};
