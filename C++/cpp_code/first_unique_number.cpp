/*
1429. First Unique Number
https://leetcode.com/problems/first-unique-number/

You have a queue of integers, you need to retrieve the first unique integer in the queue.
Implement the FirstUnique class:

FirstUnique(int[] nums)
Initializes the object with the numbers in the queue.

int showFirstUnique()
returns the value of the first unique integer of the queue,
and returns -1 if there is no such integer.

void add(int value)
insert value to the queue.

Example 1:
Input:
["FirstUnique","showFirstUnique","add","showFirstUnique","add","showFirstUnique","add","showFirstUnique"]
[[[2,3,5]],[],[5],[],[2],[],[3],[]]
Output:
[null,2,null,2,null,3,null,-1]
Explanation:
FirstUnique firstUnique = new FirstUnique([2,3,5]);
firstUnique.showFirstUnique(); // return 2
firstUnique.add(5);            // the queue is now [2,3,5,5]
firstUnique.showFirstUnique(); // return 2
firstUnique.add(2);            // the queue is now [2,3,5,5,2]
firstUnique.showFirstUnique(); // return 3
firstUnique.add(3);            // the queue is now [2,3,5,5,2,3]
firstUnique.showFirstUnique(); // return -1

Example 2:
Input:
["FirstUnique","showFirstUnique","add","add","add","add","add","showFirstUnique"]
[[[7,7,7,7,7,7]],[],[7],[3],[3],[7],[17],[]]
Output:
[null,-1,null,null,null,null,null,17]
Explanation:
FirstUnique firstUnique = new FirstUnique([7,7,7,7,7,7]);
firstUnique.showFirstUnique(); // return -1
firstUnique.add(7);            // the queue is now [7,7,7,7,7,7,7]
firstUnique.add(3);            // the queue is now [7,7,7,7,7,7,7,3]
firstUnique.add(3);            // the queue is now [7,7,7,7,7,7,7,3,3]
firstUnique.add(7);            // the queue is now [7,7,7,7,7,7,7,3,3,7]
firstUnique.add(17);           // the queue is now [7,7,7,7,7,7,7,3,3,7,17]
firstUnique.showFirstUnique(); // return 17

Example 3:
Input:
["FirstUnique","showFirstUnique","add","showFirstUnique"]
[[[809]],[],[809],[]]
Output:
[null,809,null,-1]
Explanation:
FirstUnique firstUnique = new FirstUnique([809]);
firstUnique.showFirstUnique(); // return 809
firstUnique.add(809);          // the queue is now [809,809]
firstUnique.showFirstUnique(); // return -1

Constraints:
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^8
1 <= value <= 10^8
At most 50000 calls will be made to showFirstUnique and add.
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>
#include <map>
#include <set>
#include <numeric>
#include "extra_data_types.hpp"
using namespace std;

class FirstUnique {
private:
    queue<int> uniques;
    unordered_set<int> uniqueSet;
    unordered_set<int> occurence;

public:
    FirstUnique(vector<int>& nums) {
        for (int num : nums) {
            add(num);
        }
    }

    int showFirstUnique() {
        while (!uniques.empty() and uniqueSet.find(uniques.front()) == uniqueSet.end()) {
            uniques.pop();
        }
        return uniques.empty() ? -1 : uniques.front();
    }

    void add(int value) {
        if (occurence.find(value) != occurence.end()) {
            uniqueSet.erase(value);
            return;
        }

        occurence.insert(value);
        if (uniqueSet.find(value) != uniqueSet.end()) {
            uniqueSet.erase(value);
            return;
        }

        uniqueSet.insert(value);
        uniques.push(value);
    }
};

/**
Your FirstUnique object will be instantiated and called as such:
FirstUnique* obj = new FirstUnique(nums);
int param_1 = obj->showFirstUnique();
obj->add(value);
*/