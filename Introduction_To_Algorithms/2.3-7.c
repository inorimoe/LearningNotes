#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define len 1000//S的长度
#define x 69990//数值x
int binary_Search(int* array,int key,int n)//匹配到key值，返回数组下标
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
    return -1;//找不到
}
void mergesort(unsigned* array,unsigned L,unsigned R)
{
    if(L<R)
    {
        unsigned M = L+(R-L)/2;
        mergesort(array , L , M );
        mergesort(array , M+1 ,R );
        merge_(array , L , M , R);
    }
}
void merge_(unsigned* array,unsigned L,unsigned M,unsigned R)
{
    unsigned j = 0;
    unsigned k = 0;
    unsigned n = 0;
    unsigned checa[R-L+1];//缓存数组
    unsigned leftArrayLen = M-L+1;//左子数列长度
    unsigned rightArrayLen = R-M;//右子数列长度

    while(j<leftArrayLen&&k<rightArrayLen)//比较大小，符合条件者选进缓存数组
    {
        if(*(array+L+j)<*(array+M+1+k))
        {
            checa[n]=*(array+L+j);
            j++;
        }
        else
        {
            checa[n]=*(array+M+1+k);
            k++;
        }
        n++;
    }
   while(j+k!=R-L+1)//把剩余子数列复制进缓存数组
   {
       if(leftArrayLen==j)
       {
            checa[n]=*(array+M+1+k);
            k++;
       }
       else if(rightArrayLen==k)
       {
           checa[n]=*(array+L+j);
            j++;
       }
       n++;
   }
    for(unsigned i=L,rang=0;i<=R;i++,rang++)//缓存数组复制给array
    {
        array[i]=checa[rang];
    }
}
int main(int argc, char const *argv[])
{
    int S[len];
    int i,m;//两个数值在数组的下标

    srand(time(NULL));
    for(int i=0;i<len;++i)
    {
        S[i]=rand();
    }
    mergesort(S,0,len);//归并排序:O(nlogn)
    for(int i=0;i<len;i++)
    {
        printf("%d ",S[i]);
    }
    for(i=0;i<len;++i)//遍历数组×二分查找:O(nlogn)
    {
        m = binary_Search(S,x-S[i],len);
        if(m!=-1)
        {
            break;
        }
    }
    if(i==len)
    {
        printf("\nUnfound number!");
    }
    else
    {
        printf("\n%d+%d=%d",S[i],S[m],x);
    }
    return 0;
}
