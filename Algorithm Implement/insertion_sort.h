template<typename Array, typename Length>
void insertionSort(Array arr, Length len){
    if(len <= 1 ) return;
    for(Length i = 1;i<len;++i){
        //选择数据
        auto value = arr[i];
        Length j = i -1;
        //选择插入位置
        for(;j>=0;--j){
            if(arr[j] > value){
                //数据移动
                arr[j+1] = arr[j];
            }else{
                break;
            }
        }
        arr[j+1] = value;//插入
    }
}