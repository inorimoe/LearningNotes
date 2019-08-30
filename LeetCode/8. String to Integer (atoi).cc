#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string>

#define INT_MIN  -0x7fffffff-1//小心注意 0x8000 0000 的形式,千万不要用它，写成-2147483647-1也好
#define INT_MAX 0x7fffffff//2147483647
using namespace std;

class Solution {
public:
    int myAtoi(string str) {          
        auto pStr = str.begin();
        if(pStr == str.end()) 
            return 0;
        while(isspace(*pStr)){
            pStr++;
        }
        bool negative = false;
        if(*pStr == '-'||*pStr == '+'){
            if(*pStr == '-')
                negative = true;
            pStr++;
        }
        int sum = 0;
        //
        while(isdigit(*pStr)){
            int digite = *pStr - '0';
            if(negative){
                if(sum<(INT_MIN+digite)/10)
                    return INT_MIN;
                sum = sum*10 - digite ;
            }
            else{
                if(sum>(INT_MAX-digite)/10)
                    return INT_MAX;
                sum = sum*10 + digite ;
            }
            
            pStr++;
        }
        return sum;
    }
};

int main()
{
    
    printf("\"%s\" = %d\n", "123", Solution().myAtoi("123"));
    printf("\"%s\" = %d\n", "   123", Solution().myAtoi("    123"));
    printf("\"%s\" = %d\n", "+123", Solution().myAtoi("+123"));
    printf("\"%s\" = %d\n", " -123", Solution().myAtoi(" -123"));
    printf("\"%s\" = %d\n", "123ABC", Solution().myAtoi("123ABC"));
    printf("\"%s\" = %d\n", " abc123ABC", Solution().myAtoi(" abc123ABC"));
    printf("\"%s\" = %d\n", "2147483647", Solution().myAtoi("2147483647"));
    printf("\"%s\" = %d\n", "-2147483648", Solution().myAtoi("-2147483648"));
    printf("\"%s\" = %d\n", "2147483648", Solution().myAtoi("2147483648"));
    
    printf("\"%s\" = %d\n", "-2147483647", Solution().myAtoi(string("-2147483647")));
    return 0;
}