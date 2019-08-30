class Solution {
public:
    string convert(string s, int numRows) {
        if(numRows<2)
            return s;
        vector<string> store(numRows);
        int down = numRows;
        int up = numRows - 2;
        auto ptr = s.begin();
        while(ptr!=s.end()){
            for(int i=0;i<down&&ptr!=s.end();++i){
                store[i] += *ptr++;
            }
            if(0<up)
                for(int j=numRows-2;j!=0&&ptr!=s.end();--j){
                    store[j] += *ptr++;
                }
        }
        string sss = "";
        for(auto& str:store){
            sss += str;
        }
        return sss;
    }
};