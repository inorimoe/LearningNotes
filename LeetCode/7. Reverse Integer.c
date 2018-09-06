#include<limits.h>
int reverse(int x)
{
    int isMinus=0,cache=x;
    long reverse=0;
    if(x<0)
    {
        isMinus=1;
        cache=x*-1;
    }
    while(0<cache)
    {
        reverse = reverse*10+cache%10;
        cache/=10;
    }
    if(isMinus)
        reverse=-1*reverse;
    if(reverse<INT_MIN||INT_MAX<reverse)
        return 0;
    return reverse;
}