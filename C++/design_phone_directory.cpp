/*
379. Design Phone Directory
Design a Phone Directory which supports the following operations:

get: Provide a number which is not assigned to anyone.
check: Check if a number is available or not.
release: Recycle or release a number.
Example:

// Init a phone directory containing a total of 3 numbers: 0, 1, and 2.
PhoneDirectory directory = new PhoneDirectory(3);

// It can return any available phone number. Here we assume it returns 0.
directory.get();

// Assume it returns 1.
directory.get();

// The number 2 is available, so return true.
directory.check(2);

// It returns 2, the only number that is left.
directory.get();

// The number 2 is no longer available, so return false.
directory.check(2);

// Release number 2 back to the pool.
directory.release(2);

// Number 2 is available again, return true.
directory.check(2);
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
#include <stdio.h>
using namespace std;

class PhoneDirectory {
private:
    queue<int> available;
    unordered_set<int> used;
    int maxNum;
public:
    /* Initialize your data structure here
     @param maxNumbers - The maximum numbers that can be stored in the phone directory.*/
    PhoneDirectory(int maxNumbers) {
        maxNum = maxNumbers;
        for (int i = 0; i < maxNumbers; i++) {
            available.push(i);
        }
    }

    /* Provide a number which is not assigned to anyone.
     @return - Return an available number. Return -1 if none is available.*/
    int get() {
        if (available.empty()) {
            return -1;
        }
        int result = available.front();
        available.pop();
        used.insert(result);
        return result;
    }

    /* Check if a number is available or not.*/
    bool check(int number) {
        if (number < 0 or number > maxNum) {
            return false;
        }
        return used.find(number) == used.end();
    }

    /* Recycle or release a number.*/
    void release(int number) {
        if (used.find(number) == used.end()) {
            return;
        }
        used.erase(number);
        available.push(number);
    }
};
/*
 * Your PhoneDirectory object will be instantiated and called as such:
 * PhoneDirectory obj = new PhoneDirectory(maxNumbers);
 * int param_1 = obj.get();
 * bool param_2 = obj.check(number);
 * obj.release(number);
*/
