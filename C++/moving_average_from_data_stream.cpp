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


class MovingAverage {
private:
    queue<int> window;
    int sum;
    int length;

public:
    /** Initialize your data structure here. */
    MovingAverage(int size) {
        sum = 0;
        length = size;
    }
    
    double next(int val) {
        if (window.size() < length) {
            window.push(val);
            sum += val;
            return sum / (double) window.size();
        }

        sum -= window.front();
        window.pop();
        sum += val;
        window.push(val);
        return sum / (double) length;
    }
};

/**
 * Your MovingAverage object will be instantiated and called as such:
 * MovingAverage obj = new MovingAverage(size);
 * double param_1 = obj.next(val);
 */

int main() {
    Solution s;
    return 0;
}