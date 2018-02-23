#include <iostream>
#include "Heap.h"
using namespace std;

template <class T>
Node<T>* Heap<T>::GetParentOfNode(int i)
{
    // parent of node is i/2
    int parentIndex = GetParentIndex(i);
    Node<T>* nodeAtIndex = ElementAt(parentIndex);
    return nodeAtIndex;
}

template <class T>
Node<T>* Heap<T>::GetLeftChildOfNode(int i)
{
    // left child is always 2*i
    int leftChildIndex = GetLeftChildIndex(i);
    Node<T>* nodeAtIndex = ElementAt(leftChildIndex);
    return nodeAtIndex;
}

template <class T>
Node<T>* Heap<T>::GetRightChildOfNode(int i)
{
    // right child is always 2*i + 1
    int rightChildIndex = GetRightChildIndex(i);
    Node<T>* nodeAtIndex =ElementAt(rightChildIndex);
    return nodeAtIndex;
}

template <class T>
void Heap<T>::PercolateUp(int i)
{
    int parentIndex = GetParentIndex(i);
    Node<T> *parent = GetParentOfNode(i);
    Node<T> *node = ElementAt(i);
    
    if (i != 1)
    {
        if (parent->Data > node->Data)
        {
            T tempData = parent->Data;
            parent->Data = node->Data;
            node->Data = tempData;
            // precolate up the parent
            PercolateUp(parentIndex);
        }
    }

    // else return, node is in the right place
}

template <class T>
void Heap<T>::Insert(T* values, int count)
{
    for (int i = 0; i<count; i++)
    {
        this->Insert(values[i]);
    }
}

template <class T>
void Heap<T>::Insert(T value)
{
    /*
        There is no need to check for the case of head being null in this function.
        Head is set in constructor to the dummy value at the beginning of the list
        so there is no way it will ever be null.
        if (head == nullptr)
        {
            head = newNode;
            count++;
            return;
        }
    */

    // make a new node
    Node<T>* newNode = new Node<T>(value);

    // insert new element at the end of list
    Node<T>* tail = GetTailNode();
    tail->Next = newNode;
    
    // Count the new node.
    this->count++;

    // Use heap percolate up function to move the 
    // new node into the correct location
    PercolateUp(this->count);
}

template <class T>
Node<T>* Heap<T>::GetTailNode()
{
    if (head == nullptr) return nullptr;
    Node<T>* current = head;

    while (current->Next != nullptr) current = current->Next;
    
    return current;
}

template <class T>
void Heap<T>::RemoveTail(void)
{
    Node<T>* tailNode = GetTailNode();
    if (tailNode == nullptr) return;

    Node<T>* current = head;
    while(current->Next != tailNode && current->Next != nullptr) 
        current = current->Next;

    if (current->Next == tailNode){
        current->Next = nullptr;
        delete tailNode;
    }
}

template <class T>
void Heap<T>::SiftDown(int nodeIndex) {
    int leftChildIndex, rightChildIndex, minIndex, tmp;
    leftChildIndex = GetLeftChildIndex(nodeIndex);
    rightChildIndex = GetRightChildIndex(nodeIndex);
    if (rightChildIndex >= count) {
        if (leftChildIndex >= count)
            return;
        else
            minIndex = leftChildIndex;
    } else {
        if (ElementAt(leftChildIndex)->Data <= ElementAt(rightChildIndex)->Data)
            minIndex = leftChildIndex;
        else
            minIndex = rightChildIndex;
    }
    
    if (ElementAt(nodeIndex)->Data > ElementAt(minIndex)->Data)
    {
        tmp = ElementAt(minIndex)->Data;
        ElementAt(minIndex)->Data = ElementAt(nodeIndex)->Data;
        ElementAt(nodeIndex)->Data = tmp;
        SiftDown(minIndex);
    }
}

template <class T>
void Heap<T>::RemoveMin() {
    if (IsEmpty())
        return;
    else {
        ElementAt(HEAP_MIN_INDEX)->Data = ElementAt(count)->Data;
        RemoveTail();
        count--;
        if (count > 0)
            SiftDown(HEAP_MIN_INDEX);
    }
}

template <class T>
Node<T>* Heap<T>::ElementAt(int i)
{
    int count = 0;
    Node<T>* current = head;

    while(current != nullptr)
    {
        if (count == i)
        {
            return current;
        }
        count++;
        current = current->Next;
    }
    return nullptr; // node at index was not found
}

template <class T>
void Heap<T>::Print(void)
{
    cout << "heap count: " << this->count << endl;
    Node<T> *current = head;
    while (current != nullptr)
    {
        cout << current->Data;
        if (current->Next != nullptr)
        {
            // don't print comma for the last element
            cout << ", "; 
        }
        current = current->Next;
    }
    cout << endl;
}

template <class T>
void Heap<T>::Validate(bool verbose)
{
    int index = 1;
    RecursiveValidate(index, verbose);
}

template <class T>
void Heap<T>::RecursiveValidate(int index, bool verbose)
{
    int leftChildIndex = GetLeftChildIndex(index);
    int rightChildIndex = GetRightChildIndex(index);
    if (verbose)
    {
        cout << "validating index " << index << " L" << leftChildIndex << " R" << rightChildIndex << endl;
    }
    Node<T> *current = ElementAt(index);
    Node<T> *leftChild = ElementAt(leftChildIndex);
    Node<T> *rightChild = ElementAt(rightChildIndex);

    if (current != nullptr)
    {
        if (leftChild != nullptr)
        {
            if (current->Data > leftChild->Data){
                cout << "invalid element with data " << current->Data;
                return;
            }
        }
        if (rightChild != nullptr)
        {
            if (current->Data > rightChild->Data)
            {
                cout << "invalid element with data " << current->Data;
                return;
            }
        }
    }
    if (leftChild != nullptr)
    {
        RecursiveValidate(leftChildIndex, verbose);
    } 
    if (rightChild != nullptr)
    {
        RecursiveValidate(rightChildIndex, verbose);
    }
}

template <class T>
Heap<T>::Heap(T min)
{
    this->head = new Node<T>(min);
    this->count = 0;
    this->min = min;
}

template <class T>
Heap<T>::~Heap()
{
    if (this->head != nullptr) DeleteAll(this->head);
}

template <class T>
void Heap<T>::Purge(T value)
{
    if (this->head == nullptr) return;
   // save the old head pointer and create a new one. We'll 
   // then copy valuese from the old list into the new list
   // as long as the values in the old list don't match the purge
   // value. 
   Node<T>* oldHead = this->head;
   
   // re-initialize this heap the same way we did in our constructor   
   this->head = new Node<T>(min);
   this->count = 0;

   // walk down the old linked list and insert
   // the data as long as it doesn't match the purge value
   Node<T>* current = oldHead;
   while(current != nullptr)
   {
       if (current->Data != value)
       {
           this->Insert(current->Data);
       }
       current = current->Next;
   }
}

template <class T>
void Heap<T>::DeleteAll(Node<T>* startNode)
{
    if (startNode == nullptr) return;
    Node<T>* current = startNode;
    Node<T>* temp = nullptr;
    int nodesDeleted = 0;
    while(current != nullptr)
    {
        temp = current;
        current = current->Next;
        delete temp;
        nodesDeleted++;
    }
    cout << "DeleteAll deleted " << nodesDeleted << " nodes" << endl;
}

template class Heap<int>;
template class Heap<float>;
