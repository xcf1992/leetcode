/*
 641. Design Circular Deque
 Design your implementation of the circular double-ended queue (deque).
 Your implementation should support following operations:

 MyCircularDeque(k): Constructor, set the size of the deque to be k.
 insertFront(): Adds an item at the front of Deque. Return true if the operation is successful.
 insertLast(): Adds an item at the rear of Deque. Return true if the operation is successful.
 deleteFront(): Deletes an item from the front of Deque. Return true if the operation is successful.
 deleteLast(): Deletes an item from the rear of Deque. Return true if the operation is successful.
 getFront(): Gets the front item from the Deque. If the deque is empty, return -1.
 getRear(): Gets the last item from Deque. If the deque is empty, return -1.
 isEmpty(): Checks whether Deque is empty or not.
 isFull(): Checks whether Deque is full or not.
 Example:

 MyCircularDeque circularDeque = new MycircularDeque(3); // set the size to be 3
 circularDeque.insertLast(1);            // return true
 circularDeque.insertLast(2);            // return true
 circularDeque.insertFront(3);            // return true
 circularDeque.insertFront(4);            // return false, the queue is full
 circularDeque.getRear();                  // return 32
 circularDeque.isFull();                // return true
 circularDeque.deleteLast();            // return true
 circularDeque.insertFront(4);            // return true
 circularDeque.getFront();                // return 4


 Note:

 All values will be in the range of [1, 1000].
 The number of operations will be in the range of [1, 1000].
 Please do not use the built-in Deque library.
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

class MyCircularDeque {
private:
    vector<int> array;
    int start;
    int count;
public:
    /* Initialize your data structure here. Set the size of the deque to be k.*/
    MyCircularDeque(int k) {
        array.resize(k, 0);
        start = 0;
        count = 0;
    }

    /* Adds an item at the front of Deque. Return true if the operation is successful.*/
    bool insertFront(int value) {
        if (count == array.size()) {
            return false;
        }
        if (start == 0) {
            start = array.size() - 1;
        }
        else {
            start -= 1;
        }
        array[start] = value;
        count += 1;
        return true;
    }

    /* Adds an item at the rear of Deque. Return true if the operation is successful.*/
    bool insertLast(int value) {
        if (count == array.size()) {
            return false;
        }
        array[(start + count) % array.size()] = value;
        count += 1;
        return true;
    }

    /* Deletes an item from the front of Deque. Return true if the operation is successful.*/
    bool deleteFront() {
        if (count == 0) {
            return false;
        }
        start = (start + 1) % array.size();
        count -= 1;
        return true;
    }

    /* Deletes an item from the rear of Deque. Return true if the operation is successful.*/
    bool deleteLast() {
        if (count == 0) {
            return false;
        }
        count -= 1;
        return true;
    }

    /* Get the front item from the deque.*/
    int getFront() {
        return count == 0 ? -1 : array[start];
    }

    /* Get the last item from the deque.*/
    int getRear() {
        return count == 0 ? -1 : array[(start + count - 1) % array.size()];
    }

    /* Checks whether the circular deque is empty or not.*/
    bool isEmpty() {
        return count == 0;
    }

    /* Checks whether the circular deque is full or not.*/
    bool isFull() {
        return count == array.size();
    }
};

/*
 * Your MyCircularDeque object will be instantiated and called as such:
 * MyCircularDeque obj = new MyCircularDeque(k);
 * bool param_1 = obj.insertFront(value);
 * bool param_2 = obj.insertLast(value);
 * bool param_3 = obj.deleteFront();
 * bool param_4 = obj.deleteLast();
 * int param_5 = obj.getFront();
 * int param_6 = obj.getRear();
 * bool param_7 = obj.isEmpty();
 * bool param_8 = obj.isFull();
*/
