#pragma once

#include "Node.h"

#define HEAP_MIN_INDEX 1

template <class T>
class Heap
{
private:
// private data
    Node<T>* head;
    int count;
    T min;

public:
// public interface
    // A note about the ctor. This heap will put a dummy value at 
    // position 0 which is not part of the heap. The dummy value
    // has to be specified as a value of type T. The type of T isn't
    // known by this class ahead of time so the class implementation
    // cannot assume this type or that and just make up a dummy value
    // for the position 0 element. This is why the ctor takes a parameter
    // of type T.
    Heap(T min);

    ~Heap();
    
    // insert one value
    void Insert(T value);

    // insert many values
    void Insert(T* values, int count);

    // return count of values
    int Count() { return this->count; }

    // print this class's contents
    void Print(void);

    // Walk the tree of data values and verify that the heap's order
    // is correct. Print a message if it is not.
    void Validate(bool verbose=false);

    bool IsEmpty(void){ return count==0; }

    void RemoveMin(void);

    void Purge(T value);

private:
// private implementation details
    Node<T>* GetTailNode();
    void RemoveTail(void);
    Node<T>* ElementAt(int i);
    Node<T>* GetParentOfNode(int i);
    Node<T>* GetLeftChildOfNode(int i);
    Node<T>* GetRightChildOfNode(int i);
    void PercolateUp(int index);
    void RecursiveValidate(int index, bool verbose);
    void SiftDown(int index);
    void DeleteAll(Node<T>* startNode);

    int GetRootIndex() {return 1;}
    int GetParentIndex(int i) { return i/2; };
    int GetLeftChildIndex(int i){ return 2*i; };
    int GetRightChildIndex(int i){ return (2*i)+1; }
};

