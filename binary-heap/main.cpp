#include <iostream>
#include <cassert>
#include <string.h>
#include <stack>
#include <queue>
#include <math.h>
#include <bits/stdc++.h>
#include <utility>
#include<cassert>

using namespace std;

class MinHeap
{
private:
    int *array;
    int size{};
    int capacity{1000};

    int left(int node)
    {
        int p = 2 * node + 1;
        if(p>=size)
            return -1;
        return p;
    }
    int right(int node)
    {
        int p = 2 * node + 2;
        return p>=size ? -1 : p;
    }
    int parent(int node)
    {
        return node == 0 ? -1 : (node - 1) / 2;
    }
    void heapify_up(int child_pos)
    {
        int par_pos = parent(child_pos);
        if(child_pos == 0 || array[par_pos] < array[child_pos])
            return;

        swap(array[child_pos], array[par_pos]);
        heapify_up(par_pos);
    }
    void heapify_down(int parent_pos) 
    {
        int child_pos = left(parent_pos);
        int right_child = right(parent_pos);

        if(child_pos == -1)
            return;
        
        if( right_child != -1 && array[right_child] < array[child_pos])
            child_pos = right_child;

        if(array[parent_pos] > array[child_pos]) {
            swap(array[child_pos], array[parent_pos]);
            heapify_down(child_pos);
        }
    }
    void heapify()
    {
        for( int i = size/2 -1; i>= 0;--i)
            heapify_down(i);
    }

public:
    MinHeap()
    {
        array = new int[capacity] {};
        size = 0;
    }
    MinHeap(const vector<int> &v)
    {
        assert((int)v.size() <= capacity);
        array = new int [capacity] {};
        size = v.size();
        for (int i = 0; i < (int)v.size(); ++i)
            array[i] = v[i];
        
        heapify();
    }
    ~MinHeap()
    {
        delete [] array;
        array = nullptr;
    }
    void push(int key)
    {
        assert(size+1 <= capacity);
        array[size++] = key;
        heapify_up(size - 1);
    }
    void pop()
    {
        assert(!empty());
        array[0] = array[--size];
        heapify_down(0);
    }
    int top()
    {
        assert(!empty());
        return array[0];
    }
    bool empty()
    {
        return size==0;
    }
    void print_less_than(int val, int parent_pos = 0)
    {
        if (parent_pos >= size || parent_pos == -1)
            return;

        if(array[parent_pos] > val)
            return;

        cout<<array[parent_pos]<<" ";

        print_less_than(val, left(parent_pos));
        print_less_than(val, right(parent_pos));
    }
    bool is_heap_array(int *p, int n, int start_idx = 0)
    {

        int left_idx = 2 * start_idx + 1;
        int right_idx = 2 * start_idx + 2;

        if(left_idx >= n || right_idx >= n)
            return true;

        if(p[left_idx] < p[start_idx] || p[right_idx] < p[start_idx])
            return false;

        return is_heap_array(p, n, left_idx) && is_heap_array(p, n, right_idx);
    }
    void heap_sort(int *p, int n)
    {
        

    }
};

class MaxHeap
{
private:
    MinHeap heap;

public:
    MaxHeap()
    {
        
    }
    MaxHeap(const vector<int> &v)
    {
        for(const auto& a:v)
            heap.push(-a);
    }
    int pop()
    {
        heap.pop();
    }
    void push(int key)
    {
        heap.push(-key);
    }
    int top()
    {
        return -heap.top();
    }
    bool empty()
    {
        return heap.empty();
    }

};
int main()
{
    MinHeap heap;
	vector<int> v { 2, 17, 22, 10, 8, 37, 14, 19, 7, 6, 5, 12, 25, 30 };
 
	for (int i = 0; i < v.size(); ++i)
		heap.push(v[i]);

    // while (!heap.empty()) {
	// 	cout << heap.top() << " ";
	// 	heap.pop();
	// }

    // cout<<endl;
    // hw1 p2
    MaxHeap max_heap;
    for (int i = 0; i < v.size(); ++i)
		max_heap.push(v[i]);

    while (!max_heap.empty()) {
		cout << max_heap.top() << " ";
		max_heap.pop();
	}

    cout<<endl;
    // hw1 p3
    heap.print_less_than(10);
    cout<<endl;
    // hw1 p4
    int p[] = {2, 5, 12, 7, 6, 22, 14, 19, 10, 17, 8, 37, 25, 30};
    cout<<heap.is_heap_array(p,14)<<endl;
    swap(p[0], p[5]);
    cout<<heap.is_heap_array(p,14)<<endl;
    return 0;
}


