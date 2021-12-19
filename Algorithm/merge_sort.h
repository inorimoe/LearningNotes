#include <stdlib.h>
template<typename Array, typename Idx>
void mergeSort_c(Array arr, Idx p, Idx r)
{
    //递归终止
    if( p >= r) return;
    //中间位置
    auto mid = p + (r-p)/2;
    //分治递归
    mergeSort_c(arr, p, mid);
    mergeSort_c(arr, mid+1, r);
    //合并
    auto i = p;
    auto j = mid+1;
    auto k = 0;
    auto tmpArr = static_cast<Array>(malloc(sizeof(arr[0])*(r-p+1)));
    while (i <= mid && j<= r)
    {
        if(arr[i] <= arr[j]){
            tmpArr[k++] = arr[i++];
        }else{
            tmpArr[k++] = arr[j++];
        }
    }
    auto start = i;
    auto end = mid;
    if(j <= r){
        start = j;
        end = r;
    }
    while(start <= end){
        tmpArr[k++] = arr[start++];
    }
    for(i = 0; i < r-p+1; ++i){
        arr[p+i] = tmpArr[i];
    }
    free(tmpArr);
}

template<typename Array, typename Length>
void mergeSort(Array arr, Length len)
{
    mergeSort_c(arr, 0, len-1);
}

