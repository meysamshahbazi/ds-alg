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
        // my strange way! this is NOT efficent!
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
    void push_back2(int value)
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
    void expand_capacity()
    {
        capacity *= 2;
        int * new_arr = new int [capacity];
        for(int i=0; i<size;i++)
            new_arr[i] = arr[i];


        // code for swaping ponters
        int * temp_ptr = new_arr;
        new_arr = arr;
        arr = temp_ptr;
        delete[] new_arr;
    }
    void push_back(int value)
    {
        if(size+1 == capacity) // recreate new arr
        {
           expand_capacity(); 
        }
        arr[size++] = value;    
    }
    void insert(int idx, int value)
    {
        assert(0 <= idx  && idx < size);
        if(size+1 == capacity) // recreate new arr
        {
           expand_capacity(); 
        }

        for(int i=size-1; i>=idx;i--)
            arr[i+1] = arr[i];
        arr[idx] = value;
        size++;
    }
    void right_rotate()
    {
        int back = get_back();
        for(int i=size-2; i>=0;i--)
            arr[i+1] = arr[i];

        arr[0] = back;
    }
    void left_rotate()
    {
        int front = get_back();
        for(int i=1; i<size-2;i++)
            arr[i-1] = arr[i];

        arr[size-1] = front;
    }
    void right_rotate(int times)
    {
        int times_ = times%size;
        while (times--)
        {
            right_rotate();
        }
        
            
    }
    int pop(int idx)
    {
        int pop_value = arr[idx];

        
        for(int i=idx; i<size-1;i++)
            arr[i] = arr[i+1];

        size --;
        return pop_value;
    }
    int find_transpostion(int value)
    {
        for(int i=0; i <size;i++)
            if(arr[i] == value)
                {
                    left_rotate();
                    return i;
                }

        return -1;
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
    return 0;
}