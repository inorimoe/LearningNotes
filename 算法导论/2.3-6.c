/*****************************************
 *将插入操作改成二分法,将插入位数后面的数据往后移动的花费为n，算法分析为nlogn+n^2,还是O(n^2);
 *最坏情况的数组为反序，把数据插入数组最前，不用进行数据往后移动的操作，O(nlogn)
 *****************************************/
#include<stdio.h>
#include<stdlib.h>
#define len 10
int binarySearch(int* array,int key,int n)//匹配到key值，返回数组下标
{
    int L = 0;
    int R = n-1;
    int M = 0;
    while(L<=R)
    {
        M=L+(R-L)/2;
        if(key<array[M])
        {
            R=M-1;
        }
        else if(array[M]<key)
        {
            L=M+1;
        }
        else
        {
            return M;//找到
        }
    }
    return key<array[M]? M : M+1;//找不到，返回比key右边的array[M]的下标
}
int main(int argc, char const *argv[])
{
    int array[len]={10,9,8,7,6,5,4,3,2,1};
    int cache[len];
    memset(cache, 0, sizeof(cache));//将数组归零
    for(int i = 0;i<len;++i)
    {
        cache[binarySearch(cache,array[i],len)-1]=array[i];
        //cache为排序完的数组，不需要移动数据
    }
   for(int i = 0;i<len;++i)
    {
        printf("%d,",cache[i]);
    }
    return 0;
}
