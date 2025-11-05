/*
 Design a HashSet without using any built-in hash table libraries.

 To be specific, your design should include these two functions:

 add(value): Insert a value into the HashSet.
 contains(value) : Return whether the value exists in the HashSet or not.
 remove(value): Remove a value in the HashSet. If the value does not exist in the HashSet, do nothing.

 Example:

 MyHashSet hashSet = new MyHashSet();
 hashSet.add(1);
 hashSet.add(2);
 hashSet.contains(1);    // returns true
 hashSet.contains(3);    // returns false (not found)
 hashSet.add(2);
 hashSet.contains(2);    // returns true
 hashSet.remove(2);
 hashSet.contains(2);    // returns false (already removed)

 Note:

 All values will be in the range of [1, 1000000].
 The number of operations will be in the range of [1, 10000].
 Please do not use the built-in HashSet library.
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

class MyHashSet {
private:
    vector<int> array;

public:
    /* Initialize your data structure here.*/
    MyHashSet() {
        array.resize(1000000, -1);
    }

    void add(int key) {
        array[key] = 1;
    }

    void remove(int key) {
        array[key] = -1;
    }

    /* Returns true if this set did not already contain the specified element*/
    bool contains(int key) {
        return array[key] != -1;
    }
};

/*
 * Your MyHashSet object will be instantiated and called as such:
 * MyHashSet obj = new MyHashSet();
 * obj.add(key);
 * obj.remove(key);
 * bool param_3 = obj.contains(key);
*/