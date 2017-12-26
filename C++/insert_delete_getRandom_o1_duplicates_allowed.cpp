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

class RandomizedCollection {
    unordered_map<int, vector<int>> indices;
    vector<pair<int, int>> nums;
public:
    /** Initialize your data structure here. */
    RandomizedCollection() {
        srand((int) time(0));
    }

    /** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */
    bool insert(int val) {
        bool find = indices.find(val) == indices.end();
        indices[val].push_back(nums.size());
        nums.push_back({val, indices[val].size() - 1});
        return find;
    }

    /** Removes a value from the collection. Returns true if the collection contained the specified element. */
    bool remove(int val) {
        bool find = indices.find(val) != indices.end();
        if (find) {
            pair<int, int> last = nums.back();
            indices[last.first][last.second] = indices[val].back();
            nums[indices[val].back()] = last;
            indices[val].pop_back();

            if (indices[val].empty()) {
                indices.erase(val);
            }
            nums.pop_back();
        }
        return find;
    }

    /** Get a random element from the collection. */
    int getRandom() {
        return nums[rand() % nums.size()].first;
    }
};

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection obj = new RandomizedCollection();
 * bool param_1 = obj.insert(val);
 * bool param_2 = obj.remove(val);
 * int param_3 = obj.getRandom();
 */