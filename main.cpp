#include "pairing_heap.h"
#include <iostream>

template<class T>
class myCompare : public PairingHeap<T>::Compare {
public:
    bool operator() (T const& left, T const& right){
        return left < right; // try replacing by '>'
    }
};

int main(void) {

    myCompare<int> compare; // optional comparing object
    PairingHeap<int> heap(compare);
    heap.push(4);
    heap.push(2);
    heap.push(5);
    heap.push(-1);
    heap.pop();

    /* heap state:
               2
              /
       5 -- 4 
    */

    std::cout << heap.top() << std::endl;
    return 0;
}
