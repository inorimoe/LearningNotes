template<typename Array, typename Length, typename value>
int binarySearch(Array arr, Length len, value val)
{
    Length left = 0;
    Length right = len-1;

    while(left <= right)
    {
        auto mid = left + (right -left)/2;
        if(arr[mid] == val){
            return mid;
        }else if(arr[mid] < val){
            left = mid + 1;
        }else{
            right = mid - 1;
        }
    }
    return -1;
}