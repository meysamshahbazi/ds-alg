#include <iostream>
#include <cassert>

using namespace std;

class Vector 
{
private: 
    int * arr = nullptr;
    int size{0};
public:
    Vector(int size):size(size)
    {
        if (size < 0) 
            size = 1;
        
        arr = new int[size] {};
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
        for(int i=0; i<size; i++)
            cout<<arr[i]<<" ";
        cout<<endl;
    }
    int find(int value)
    {
        for(int i=0; i<size; i++)
            if(arr[i] == value)
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
    void push_back1(int value)
    {

        int * old_arr = new int[size] {};
        for(int i=0; i<size; i++)
            old_arr[i] = arr[i];

        delete[] arr;
        arr = new int[size+1] {};

        for(int i=0; i<size; i++)
            arr[i] = old_arr[i];

        arr[size] = value;
        delete[] old_arr;
        size +=1;
    }
    void push_back(int value)
    {
        int * new_arr = new int [size+1];

        for(int i=0; i<size;i++)
            new_arr[i] = arr[i];

        new_arr[size] = value;
        size ++;
        // code for swaping ponters
        int * temp_ptr = new_arr;
        new_arr = arr;
        arr = temp_ptr;
        delete[] new_arr;
    }

};

int main(int argc, const char ** argv)
{
    Vector v(10);
    for (int i=0;i<10;i++)
        v.set(i,i);
    v.print();
    v.push_back(111);
    v.print();
    cout<<v.find(5)<<" "<<v.find(11)<<endl;
    return 0;
}