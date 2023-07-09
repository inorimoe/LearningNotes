#include<stdio.h>
//计算array长度
#define GET_ARRAY_LEN(array,len) {len = (sizeof(array) / sizeof(array[0]));}
//线性查找V值，没有则输出-1
int A(int* array,int v)
{
    int len;
    GET_ARRAY_LEN(array,len);
     for(int i = 0;i<len;i++)
    {
        if(v==array[i])
        {
            return i;
        }
    }
    return -1;
}
int main(int argc, char const *argv[])
{
    int array[20] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    int v = 100;
    printf("%d",A(array,v));
    return 0;
}
