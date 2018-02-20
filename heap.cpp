// compile with debug symbols on OSX: g++ heap.cpp -g -o heap.exe
// debug on OSX: lldb ./heap.exe

#include <iostream>
using namespace std;

// Linked list node class for linked list heap. Heap can hold any type :)
template <class T> 
class Node
{
public:
    T Data;
    Node* Next;
    // Convenience ctor, automatically initializes node's
    // data members so we don't forget.
    Node(T value)
    {
        Data = value;
        Next = nullptr;
    }
};

template <class T>
class Heap
{
private:
// private data
    Node<T>* head;
    int count;

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

    // TODO
    // ~Heap();
    // void Remove(T value);
};

int main (int argc, char* argv[]){
    cout << "test code will go here" << endl;
    return 0;
}