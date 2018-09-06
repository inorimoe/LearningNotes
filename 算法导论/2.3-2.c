#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define arrayLen(array) (sizeof(array)/sizeof(array[0]))
//  A[8]={3,41,52,26,38,57,9,49};
/*******************************************
速度虽然比插入排序快，但是我的代码实现空间开销大。
********************************************/
void merge_sort(unsigned* array,unsigned L,unsigned R)
{
    if(L<R)
    {
        unsigned M = L+(R-L)/2;
        merge_sort(array , L , M );
        merge_sort(array , M+1 ,R );
        merge(array , L , M , R);
    }
}
void merge(unsigned* array,unsigned L,unsigned M,unsigned R)
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
    int A[8]={3,41,52,26,38,57,9,49};
    unsigned B[20000];
    for(unsigned i=0;i<arrayLen(B);i++)
    {
        B[i]=(unsigned)rand();
    }
    //归并排序
    merge_sort(A,0,arrayLen(A)-1);
    merge_sort(B,0,(unsigned)arrayLen(B)-1);
    //打印数列

    for(int i=0;i<arrayLen(A);i++)
    {
        printf("%d,",A[i]);
    }
    printf("\n");
      for(unsigned i=0;i<arrayLen(B);i++)
    {
        printf("%d,",B[i]);
    }

    return 0;
}
