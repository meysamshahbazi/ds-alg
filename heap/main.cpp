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
    int *array { };
    int size { };
    int capacity { 1000 };

    int left(int node)
    {
        int p = 2 * node + 1;
        if (p >= size)
            return -1;
        return p;
    }
    int right(int node)
    {
        int p = 2 * node + 2;
        return p >= size ? -1 : p;
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

        if (child_pos == -1)
            return;
        
        if (right_child != -1 && array[right_child] < array[child_pos])
            child_pos = right_child;

        if (array[parent_pos] > array[child_pos]) {
            swap(array[child_pos], array[parent_pos]);
            heapify_down(child_pos);
        }
    }
    void heapify()
    {
        for (int i = size / 2 - 1; i >= 0; --i)
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
    // hw1 p3
    void print_less_than(int val, int parent_pos = 0)
    {
        if (parent_pos >= size || parent_pos == -1 || array[parent_pos] > val)
            return;

        cout << array[parent_pos] << " ";

        print_less_than(val, left(parent_pos));
        print_less_than(val, right(parent_pos));
    }
    // hw1 p4
    bool is_heap_array(int *p, int n, int start_idx = 0)
    {

        int left_idx = 2 * start_idx + 1;
        int right_idx = 2 * start_idx + 2;

        if (left_idx >= n || right_idx >= n)
            return true;

        if (p[left_idx] < p[start_idx] || p[right_idx] < p[start_idx])
            return false;

        return is_heap_array(p, n, left_idx) && is_heap_array(p, n, right_idx);
    }
    void display()
    {
        for (int i = 0; i < size; i++)
            cout<<array[i]<<" ";
        cout<<endl;
    }
    void sort()
    {
        int n = size;
        int* array_ = array;
        for (int i=0; i <n; ++i) {
            heapify_up(size-1);
            array++;
            size--;
        }   
        size = n;
        array = array_;
    }
    void heap_sort(int *p, int n)
    {
        int* old_arr = array;
        int old_size = size;

        array  = p;
        size = n;

        heapify();

        while (size--){
            swap(array[0], array[size]);
            heapify_down(0);
        }

        for (int i = 0; i < n / 2; ++i)
            swap(array[i], array[n - i -1]);

        array = old_arr;
        size = old_size;
    }
    int getSize() 
    {
        return size;
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
    int getSize() 
    {
        return heap.getSize();
    }
};

// hw2 p2
class PriorityQueue
{
private:
    int *key { };
    int *value { };
    int size { };
    int capacity { 1000 };

    int left(int node) {
        int p = 2 * node + 1;
        if (p >= size)
            return -1;
        return p;
    }
    int right(int node) {
        int p = 2 * node + 2;
        return p >= size ? -1 : p;
    }
    int parent(int node) {
        return node == 0 ? -1 : (node - 1) / 2;
    }
    void heapify_up(int child_pos) {
        int par_pos = parent(child_pos);
        if(child_pos == 0 || key[par_pos] < key[child_pos])
            return;

        swap(key[child_pos], key[par_pos]);
        swap(value[child_pos], value[par_pos]);
        heapify_up(par_pos);
    }
    void heapify_down(int parent_pos) 
    {
        int child_pos = left(parent_pos);
        int right_child = right(parent_pos);

        if (child_pos == -1)
            return;
        
        if (right_child != -1 && key[right_child] < key[child_pos])
            child_pos = right_child;

        if (key[parent_pos] > key[child_pos]) {
            swap(key[child_pos], key[parent_pos]);
            swap(value[child_pos], value[parent_pos]);
            heapify_down(child_pos);
        }
    }
    void heapify()
    {
        for (int i = size / 2 - 1; i >= 0; --i)
            heapify_down(i);
    }

public:
    PriorityQueue() {
        key = new int[capacity] {};
        value = new int[capacity] {};
        size = 0;
    }
    ~PriorityQueue(){
        delete [] key;
        delete [] value;
    }
    void enqueue(int data, int priority) {
        assert(size+1 <= capacity);
        value[size] = data;
        key[size++] = priority;
        heapify_up(size - 1);
    }
    int dequeue() {
        assert(!empty());
        int ret = value[0];
        key[0] = key[--size];
        value[0] = value[size];
        heapify_down(0);
        return ret;
    }
    bool empty()
    {
        return size==0;
    }
    void display()
    {
        for (int i = 0; i < size; i++)
            cout<<value[i]<<" ";
        cout<<endl;
    }
    int getSize() 
    {
        return size;
    }
};

class KthNumberProcessor{
    int k;
    MaxHeap heap;
    int next_value = INT_MAX;

public:
    KthNumberProcessor(int k): k{k} 
    {
    }
    int next(int new_num)
    {
        if(new_num < next_value)
            heap.push(new_num);

        while (heap.getSize() > k) {
            heap.pop();
        }
        
        next_value = heap.top();
        return next_value;
    }
};

// https://leetcode.com/problems/kth-largest-element-in-a-stream/
class KthLargest {
    priority_queue <int, vector<int>, greater<int>> mn_heap;
    int k;
public:
    KthLargest(int k, vector<int>& nums) {
        this->k = k;

        std::sort(nums.begin(), nums.end(), std::greater<>());

        for (int i = 0; i < (int) nums.size() && mn_heap.size() < k; i++)
            mn_heap.push(nums[i]);
    }
    

    int add(int val) {
        if (mn_heap.size() < k)
            mn_heap.push(val);
        
        else if (val > mn_heap.top()) {
            mn_heap.pop();
            mn_heap.push(val);
        }
        return mn_heap.top();
    }
};

// https://leetcode.com/problems/last-stone-weight/
class Solution1046 {
public:
    int lastStoneWeight(vector<int>& stones) {
        priority_queue<int> mx_heap;

        for (auto s : stones)
            mx_heap.push(s);

        while (mx_heap.size() > 0) {
            int y = mx_heap.top();
            mx_heap.pop();
            
            if (mx_heap.empty())
                return y;
            
            int x = mx_heap.top();
            mx_heap.pop();

            if (y > x)
                mx_heap.push(y - x);
        }
        return 0;
    }
};

// https://leetcode.com/problems/k-closest-points-to-origin/
class Solution973 {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        
        priority_queue <pair<int, vector<int>>, vector<pair<int, vector<int>>>, greater<pair<int, vector<int>>>> mn_heap;
        
        for (auto p : points) {
            int d = p[0]*p[0] + p[1]*p[1];
            mn_heap.push({d, p});
        }

        vector<vector<int>> res;

        for (int i = 0; i < k; i++) {
            res.push_back(mn_heap.top().second);
            mn_heap.pop();
        }
        return res;
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
    // hw1 p5

    // int arr[] = {1,8,5,7,6};
    int arr[] = {2, 5, 12, 7, 6, 22, 14, 19, 10, 17, 8, 37, 25, 30};
    heap.heap_sort(arr,14);
    heap.display();
    for (int i = 0; i <14;i++)
        cout<<arr[i]<<" ";
    cout<<endl;

    // heap.display();
    // heap.sort();
    // heap.display();

    // hw2 p1  UNCOMMENT FOR TEST!

    /*
    KthNumberProcessor kthp(4);
    cout<<"insert for Kth Number Processor\n";
    int num;
    while (cin>>num) {
        cout<<kthp.next(num)<<"\n";
    }
    */

   vector<int> v703 = {4,5,8,2};
   KthLargest kl(3, v703);

    
    return 0;
}


