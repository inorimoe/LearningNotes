#ifndef BUBBLE_SORT
#define BUBBLE_SORT
template<class Array, class Length>
void bubblesort(Array arr, Length len){
    if(len <= 1) return;
    for(Length i = 0; i < len; ++i){
        bool flag = false;
        for(Length j = 0; j < len - i - 1; ++j){
            if(arr[j] > arr[j+1]){
                auto tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
                flag = true;
            }
        }
        if(!flag) break;
    }
};
#endif
