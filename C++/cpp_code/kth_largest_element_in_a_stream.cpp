/*
703. Kth Largest Element in a Stream
https://leetcode.com/problems/kth-largest-element-in-a-stream/

Design a class to find the kth largest element in a stream.
Note that it is the kth largest element in the sorted order,
not the kth distinct element.

Your KthLargest class will have a constructor which accepts an integer k and an integer array nums,
which contains initial elements from the stream.
For each call to the method KthLargest.add,
return the element representing the kth largest element in the stream.

Example:
int k = 3;
int[] arr = [4,5,8,2];
KthLargest kthLargest = new KthLargest(3, arr);
kthLargest.add(3);   // returns 4
kthLargest.add(5);   // returns 5
kthLargest.add(10);  // returns 5
kthLargest.add(9);   // returns 8
kthLargest.add(4);   // returns 8
Note:
You may assume that nums' length ≥ k-1 and k ≥ 1.
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
#include <set>
using namespace std;

class KthLargest {
    priority_queue<int, vector<int>, greater<int>> minHeap;
    int K;

public:
    KthLargest(int k, vector<int> nums) {
        K = k;
        for (int num : nums) {
            minHeap.push(num);
            if (minHeap.size() > K) {
                minHeap.pop();
            }
        }
    }

    int add(int val) {
        minHeap.push(val);
        if (minHeap.size() > K) {
            minHeap.pop();
        }
        return minHeap.top();
    }
};

/*
Your KthLargest object will be instantiated and called as such:
KthLargest obj = new KthLargest(k, nums);
int param_1 = obj.add(val);
*/