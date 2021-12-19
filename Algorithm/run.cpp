#include "quick_sort.h"
#include "binary_search.h"
#include <iostream>

int main(){
    float arr[] = {11,13,12,14,25,34,5,6, 5, 4,3,2,1,11,26};
    quickSort(arr, 15);
    for(auto tmp:arr){
        std::cout << tmp << " ";
    }
    std::cout << std::endl << binarySearch(arr, 15, 11);
    return 0;
}