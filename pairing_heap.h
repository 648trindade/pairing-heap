/*************************************************************************/
/*  pairing_heap.h                                                       */
/*************************************************************************/
/* Copyright (c) 2016 Saad Taame                                         */
/* Copyright (c) 2017 Rafael Gauna Trindade                              */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#ifndef PAIRING_HEAP_H
#define PAIRING_HEAP_H

template<class T>
class PairingHeap{
public:
    class Compare{
    public:
        virtual bool operator() (T const& left, T const& right){
            return left < right;
        }
    };

private:
    class HeapNode {
    public:
        T key;
        HeapNode *left_child;
        HeapNode *next_sibling;

        HeapNode():
            left_child(nullptr), next_sibling(nullptr) {}

        HeapNode(T key_, HeapNode *left_child_, HeapNode *next_sibling_):
            key(key_), left_child(left_child_), next_sibling(next_sibling_) {}

        ~HeapNode(){
            if (left_child != nullptr)
                delete left_child;
            if (next_sibling != nullptr)
                delete next_sibling;
        }

        void add_child(HeapNode *node) {
            if(left_child != nullptr)
                node->next_sibling = left_child;
            left_child = node;
        }
    };

    HeapNode* root;
    Compare&  compare_obj;

public:
    PairingHeap(Compare& compare_obj_ = Compare()):
        root(nullptr), compare_obj(compare_obj_) {}
    
    ~PairingHeap(){
        if (root != nullptr)
            delete root;
    }

    inline bool empty(void) {
        return (root == nullptr);
    }

    inline T top(void) {
        return root->key;
    }

    void push(T key) {
        root = merge(root, new HeapNode(key, nullptr, nullptr));
    }

    void pop(void) {
        HeapNode* old_root = root;
        root = two_pass_merge(root->left_child);
        old_root->left_child = nullptr;
        old_root->next_sibling = nullptr;
        delete old_root;
    }

    //FIXME: unstable to delete if joined
    void join(const PairingHeap &other) {
        root = merge(root, other.root);
    }

private:

    HeapNode* merge(HeapNode* A, HeapNode* B){
        if(A == nullptr)
            return B;
        else if(B == nullptr)
            return A;
        else if(compare_obj(A->key, B->key)) {
            A->add_child(B);
            return A;
        }
        else {
            B->add_child(A);
            return B;
        }
    }

    HeapNode* two_pass_merge(HeapNode* node) {
        if(node == nullptr || node->next_sibling == nullptr)
            return node;
        else {
            HeapNode *A, *B, *newNode;
            A = node;
            B = node->next_sibling;
            newNode = node->next_sibling->next_sibling;

            A->next_sibling = nullptr;
            B->next_sibling = nullptr;

            return merge(merge(A, B), two_pass_merge(newNode));
        }
    }
};

#endif