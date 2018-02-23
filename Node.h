#pragma once

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