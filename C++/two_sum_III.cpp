/*
170. Two Sum III - Data structure design
https://leetcode.com/problems/two-sum-iii-data-structure-design/

Design and implement a TwoSum class.
It should support the following operations: add and find.
add - Add the number to an internal data structure.
find - Find if there exists any pair of numbers which sum is equal to the value.

Example 1:
add(1); add(3); add(5);
find(4) -> true
find(7) -> false

Example 2:
add(3); add(1); add(2);
find(3) -> true
find(6) -> false
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class TwoSum {
    unordered_map<int,int> count;
public:
    /* Initialize your data structure here.*/
    TwoSum() {}

    /* Add the number to an internal data structure..*/
    void add(int number) {
        count[number] += 1;
    }

    /* Find if there exists any pair of numbers which sum is equal to the value.*/
    bool find(int value) {
        for(auto& el : count) if (count.find(value - el.first) != end(count) and (value - el.first != el.first or el.second > 1)) {
            return true;
        }
        return false;
    }
};

class TwoSum1 {
private:
    unordered_map<int, bool> num;
    unordered_map<int, bool> sumTable;

public:
    void add(int number) {
        if (num.empty()) {
            num[number] = true;
            return;
        }
        if (num.find(number) != num.end()) {
            if (sumTable.find(number * 2) == sumTable.end()) {
                sumTable[number * 2] = true;
            }
            return;
        }
        for (auto it = num.begin(); it != num.end(); it++) {
            if (sumTable.find(number + it->first) == sumTable.end()) {
                sumTable[number + it->first] = true;
            }
        }
        num[number] = true;
        return;
    }

    bool find(int value) {
        if (sumTable.find(value) == sumTable.end()) {
            return false;
        }
        return true;
    }
};
