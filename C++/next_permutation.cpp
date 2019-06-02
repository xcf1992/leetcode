/*
31. Next Permutation

Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.

If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order).

The replacement must be in-place and use only constant extra memory.

Here are some examples. Inputs are in the left-hand column and its corresponding outputs are in the right-hand column.

1,2,3 → 1,3,2
3,2,1 → 1,2,3
1,1,5 → 1,5,1
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

class Solution {
public:
    void nextPermutation(vector<int> &num) {
        if (num.size() == 0 || num.size() == 1) {
            return;
        }
        
        int i;
        for (i = num.size() - 1; i > 0; i--) {
            if (num.at(i) > num.at(i - 1)) {
                break;
            }
        }
        if (i == 0) {
            reverse(num, 0);
            return;
        }
        
        int j;
        for (j = num.size() - 1; j >= 0; j--) {
            if (num.at(j) > num.at(i - 1)) {
                break;
            }
        }
        swap(num.at(i - 1), num.at(j));
        reverse(num, i);
        return;
    }
    
    void reverse(vector<int> &num, int start) {
        int end = num.size() - 1;
        while (start < end) {
            swap(num.at(start), num.at(end));
            start++;
            end--;
        }
        return;
    }
};
