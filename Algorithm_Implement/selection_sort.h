template<typename Array, typename Length>
void selectionSort(Array arr, Length len)
{
    Length i;
    Length j;
    Length min_idx;
    for(i = 0;i < len-1; ++i)
    {
        //找到有序区的边界
        min_idx = i;
        //找到无序区的最小值
        for(j = i+1; j<len; ++j)
        {
            if(arr[j] < arr[min_idx])
            {
                min_idx = j;
            }
        }
        //交换
        auto tmp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = tmp;
    }
}