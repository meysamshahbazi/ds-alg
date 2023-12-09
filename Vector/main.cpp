#include <iostream>
#include <cassert>

using namespace std;

class Vector 
{
private: 
    int * arr = nullptr;
    int size{0};
    int capacity;
public:
    Vector(int size):size(size)
    {
        if (size < 0) 
            size = 1;
        capacity = 1024;
        // arr = new int[size] {};
        arr = new int[capacity] {};
    }

    ~Vector()
    {
        delete[] arr;
        arr = nullptr;
    }

    int get_size()
    {
        return size;
    }

    int get(int idx)
    {
        assert(0 <= idx  && idx < size);
        return arr[idx];
    }

    void set(int idx, int val)
    {
        assert(0 <= idx  && idx < size);
        arr[idx] = val;
    }

    void print()
    {
        for(int i = 0; i < size; i++)
            cout<<arr[i]<<" ";
        cout<<endl;
    }

    int find(int value)
    {
        for (int i = 0; i < size; i++)
            if (arr[i] == value)
                return i;
        
        return -1;// -1 is indicator for Not found 
    }

    int get_front()
    {
        return arr[0];
    }

    int get_back()
    {
        return arr[size-1];
    }

    void push_back1(int value) { // based on size! O(n^2) for n push_back!
        int *arr2 = new int[size + 1];
        for (int i = 0; i < size; i++)
            arr2[i] = arr[i];

        arr2[size++] = value;

        swap(arr, arr2);

        delete []arr2;
    }

    void expand_capacity()
    {
        capacity *= 2;
        int * new_arr = new int[capacity] { };
        for (int i = 0; i < size; i++)
            new_arr[i] = arr[i];

        swap(new_arr, arr);
        delete[] new_arr;
    }

    void push_back(int value) // O(n lg n) for n push back
    {
        if (size == capacity) // recreate new arr
           expand_capacity(); 
        
        arr[size++] = value;    
    }

    void insert(int idx, int value)
    {
        assert(0 <= idx  && idx < size);
        if (size == capacity) // recreate new arr
           expand_capacity(); 

        for(int i = size - 1; i >= idx; i--)
            arr[i+1] = arr[i];

        arr[idx] = value;
        size++;
    }

    void right_rotate() // hw1 p1
    {
        int back = get_back();
        for (int i = size - 2; i >= 0; i--)
            arr[i + 1] = arr[i];

        arr[0] = back;
    }

    void left_rotate() // hw1 p2
    {
        int front = get_back();
        for (int i = 1; i < size - 2; i++)
            arr[i - 1] = arr[i];

        arr[size - 1] = front;
    }

    void right_rotate(int times) // hw1 p3
    {
        int times_ = times % size;
        while (times--)
            right_rotate();
    }

    int pop(int idx) // hw1 p4
    {
        int pop_value = arr[idx];
        for(int i = idx; i < size - 1; i++)
            arr[i] = arr[i + 1];

        size--;
        return pop_value;
    }

    int find_transpostion(int value) // hw1 p5
    {
        int idx = find(value);
        
        if (idx > 0)  
            swap(arr[idx - 1], arr[idx]);

        return idx;
    }

};

int main(int argc, const char ** argv)
{
    Vector v(10);
    for (int i=0;i<10;i++)
        v.set(i,i);
    v.print();

    // for(int i=0; i < 2000; i++)
    //     v.push_back(i);

    v.push_back(111);
    v.print();
    v.insert(2,777);
    v.print();
    v.right_rotate();
    v.print();
    cout<<"-------------------"<<endl;
    v.right_rotate(20000);
    v.print();
    cout<<"-------------------"<<endl;
    int p = v.pop(1);
    v.print();
    cout<<"Pop value is: "<<p<<endl;
    cout<<v.find(5)<<" "<<v.find(11)<<endl;
    cout<<v.find(777)<<" "<<v.find(11)<<endl;
    cout<<"-------------------"<<endl;
    // hw1 p 5
    v.print();
    for (int i = 0; i < 10; i++)
        cout << v.find_transpostion(9)<< ", ";
    
    cout<< "\n";
    v.print();
    // ALL HWs are Done! :)
    return 0;
}