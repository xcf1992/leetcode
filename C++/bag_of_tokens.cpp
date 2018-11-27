/*
 You have an initial power P, an initial score of 0 points, and a bag of tokens.
 
 Each token can be used at most once, has a value token[i], and has potentially two ways to use it.
 
 If we have at least token[i] power, we may play the token face up, losing token[i] power, and gaining 1 point.
 If we have at least 1 point, we may play the token face down, gaining token[i] power, and losing 1 point.
 Return the largest number of points we can have after playing any number of tokens.
 
 
 
 Example 1:
 
 Input: tokens = [100], P = 50
 Output: 0
 Example 2:
 
 Input: tokens = [100,200], P = 150
 Output: 1
 Example 3:
 
 Input: tokens = [100,200,300,400], P = 200
 Output: 2
 
 
 Note:
 
 tokens.length <= 1000
 0 <= tokens[i] < 10000
 0 <= P < 10000
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
#include <map>
#include <numeric>
using namespace std;
// we should always use point to get most power token
// and get point from least power token
// so we need to sort the array first
// then we can get point from left and get power from right until nothing can be changed
class Solution {
public:
    int bagOfTokensScore(vector<int>& tokens, int P) {
        sort(tokens.begin(), tokens.end());
        int power = P;
        int point = 0;
        int result = 0;
        int left = 0;
        int right = tokens.size() - 1;
        while (left <= right) {
            if (power < tokens[left] and point <= 0) {
                break;
            }
            
            if (power >= tokens[left]) {
                power -= tokens[left];
                point += 1;
                result = max(result, point);
                left += 1;
            }
            else if (point > 0) {
                power += tokens[right];
                right -= 1;
                point -= 1;
            }
        }
        return result;
    }
};
