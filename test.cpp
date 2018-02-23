// compile with debug symbols on OSX: g++ *.cpp -g -o test.exe
// compile with debug symbols on Ubuntu: g++ *.cpp -g -std=c++11 -o test.exe
// debug on OSX: lldb ./test.exe
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

#include "Heap.h"

int main (int argc, char* argv[]){
    Heap<int> h1(0);
    h1.Insert(5);
    h1.Validate();
    cout << "heap 1 contains one integer" << endl;
    h1.Print();
    cout << endl;

    Heap<int> h2(0);
    h2.Insert(5);
    h2.Insert(2);
    h2.Validate();
    cout << "heap 2 contains two integers" << endl;
    h2.Print();
    cout << endl;

    Heap<int> h3(0);
    int values[] = {90, 67, 32, 24, 27, 16, 5};
    h3.Insert(values, 7);
    h3.Validate();
    cout << "heap 3 contains 7 integers" << endl;
    h3.Print();
    cout << endl;

    Heap<float> h4(0.0);
    float floatValues[] = {90.1, 67.9, 32.4, 24.7, 27.0, 16.3, 5.5};
    h4.Insert(floatValues, 7);
    h4.Validate();
    cout << "heap 4 contains 7 floats" << endl;
    h4.Print();
    cout << endl;

    cout << "remove min" << endl;
    h4.RemoveMin();
    h4.Validate();
    h4.Print();
    cout << endl;

    cout << "remove min again" << endl;
    h4.RemoveMin();
    h4.Validate();
    h4.Print();
    cout << endl;

    Heap<int> h5(0);
    cout << "Creating heap with 1000 random integers" << endl;
    srand(time(nullptr)); // seeding rand with current time gives a nice random distribution
    for (int i = 0; i<1000; i++)
    {
        h5.Insert(rand()%100);
    }

    h5.Validate();
    cout << "Heap 5 Validate completed" << endl;
    h5.Print();
    h5.Purge(4);
    h5.Validate();
    h5.Print();
    cout << endl;

    return 0;
}
