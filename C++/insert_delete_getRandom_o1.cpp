#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
using namespace std;

class RandomizedSet {
private:
    unordered_map<int, int> indices;
    vector<int> nums;
public:
    /** Initialize your data structure here. */
    RandomizedSet() {
        srand((int) time(0));
    }

    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        if (indices.find(val) == indices.end()) {
            indices.insert({val, nums.size()});
            nums.push_back(val);
            return true;
        }
        return false;
    }

    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        auto it = indices.find(val);
        if (it == indices.end()) {
            return false;
        }

        int index = it -> second;
        nums[index] = nums.back();
        indices.find(nums[index]) -> second = index;

        nums.pop_back();
        indices.erase(it);
        return true;
    }

    /** Get a random element from the set. */
    int getRandom() {
        int pos = rand() % nums.size();
        return nums[pos];
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet obj = new RandomizedSet();
 * bool param_1 = obj.insert(val);
 * bool param_2 = obj.remove(val);
 * int param_3 = obj.getRandom();
 */