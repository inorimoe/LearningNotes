//###############################
//插入排序，降序，时间戳不准（不会）
//###############################
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main(int argc, char const *argv[])
{
    int listConfusion[300];
    clock_t start_t, end_t;
    int key,j;
    clock_t timer;

    for(int i=0;i<300;i++)
    {
        listConfusion[i]=rand();
        i%10==9?printf(" %d\n",listConfusion[i]):printf(" %d",listConfusion[i]);
    }
    /* 程序开始之前计时start */
    start_t = clock();
    //insertion-sort code
    for(int i=1;i<300;i++)
    {
        key = listConfusion[i];
        for(j=i;j>0&&key>listConfusion[j-1];j--)
        {
            listConfusion[j]=listConfusion[j-1];
        }
        listConfusion[j] = key;
    }
    /* 程序块结束后计时end */
    end_t = clock();
    //output
    for(int i=0;i<300;i++)
    {
        i%10==9?printf(" %d\n",listConfusion[i]):printf(" %d",listConfusion[i]);
    }
    timer = end_t - start_t;
    printf("time cost is: %ld secs",timer);
    return 0;
}
