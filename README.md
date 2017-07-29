# pairing-heap
A c++ implementation of the Two-Pass Pairing Heap data structure. This is a basic implementation of a min-heap of dynamic type but it can be easily modified to add a custom comparator.

# API
* `PairingHeap heap; // Create new empty min-heap`
* `heap.empty();     // True if heap is empty`
* `heap.top();       // Return element with minimum key`
* `heap.push(T);     // Insert new element of type T`
* `heap.pop();       // Remove element with minimum key`
* `heap.join();      // Merge two heaps together (buggy to free memory)`

# Time Complexity
* `empty`, `top`, `push`, and `join` take `O(1)` time in the worst case.
* `pop` takes `O(log N)` time amortized over a sequence of operations.

# Examples
An example can be found on `main.cpp` file.
