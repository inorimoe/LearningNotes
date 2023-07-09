#include <utility>
template<typename Array, typename Length>
Length partition(Array arr, Length p, Length r)
{
    auto pivot = arr[r];
    auto i = p;
    auto j = p;
    for(;j <= r-1; ++j)
    {
        if(arr[j] < pivot){
            std::swap(arr[i], arr[j]);
            ++i;
        }
    }
    std::swap(arr[i], arr[r]);
    return i;
}

template<typename Array, typename Length>
void quick_sort_c(Array arr, Length p, Length r)
{
    if( p >= r ) return;
    //获取分区点
    Length q = partition(arr, p, r);
    quick_sort_c(arr, p, q-1);
    quick_sort_c(arr, q+1, r);
}

template<typename Array, typename Length>
void quickSort(Array arr, Length len)
{
    quick_sort_c(arr, 0, len-1);
}