/*
 605. Can Place Flowers
 Suppose you have a long flowerbed in which some of the plots are planted and some are not.
 However, flowers cannot be planted in adjacent plots - they would compete for water and both would die.

 Given a flowerbed (represented as an array containing 0 and 1,
 where 0 means empty and 1 means not empty),
 and a number n, return if n new flowers can be planted in it without violating the no-adjacent-flowers rule.

 Example 1:
 Input: flowerbed = [1,0,0,0,1], n = 1
 Output: True
 Example 2:
 Input: flowerbed = [1,0,0,0,1], n = 2
 Output: False
 Note:
 The input array won't violate no-adjacent-flowers rule.
 The input array size is in the range of [1, 20000].
 n is a non-negative integer which won't exceed the input array size.
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
#include <set>
using namespace std;

class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        if (n == 0) {
            return true;
        }

        if (n > (flowerbed.size() + 1) / 2) {
            return false;
        }

        for (int i = 0; i < flowerbed.size(); i++) if (flowerbed[i] == 0) {
            if ((i == 0 or flowerbed[i - 1] == 0) and (i == flowerbed.size() - 1 or flowerbed[i + 1] == 0)) {
                flowerbed[i] = 1;
                n -= 1;
                if (n == 0) {
                    return true;
                }
            }
        }
        return false;
    }
};

class Solution1 {
private:
    bool placeFlower(vector<int>& bed, int flower, int start) {
        if (flower <= 0) {
            return true;
        }

        if (start >= bed.size()) {
            return false;
        }

        for (int i = start; i < bed.size(); i++) {
            if (bed[i] == 0) {
                if ((i - 1 < 0 || bed[i - 1] == 0) && (i + 1 >= bed.size() || bed[i + 1] == 0)) {
                    bed[i] = 1;
                    if (placeFlower(bed, flower - 1, i + 1)) {
                        return true;
                    }
                    bed[i] = 0;
                }
            }
        }

        return false;
    }
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        if (n == 0) {
            return true;
        }

        if (n > (flowerbed.size() + 1) / 2) {
            return false;
        }
        return placeFlower(flowerbed, n, 0);
    }
};

