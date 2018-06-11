/*
 Alice has a hand of cards, given as an array of integers.
 
 Now she wants to rearrange the cards into groups so that each group is size W, and consists of W consecutive cards.
 
 Return true if and only if she can.
 
 
 
 Example 1:
 
 Input: hand = [1,2,3,6,2,3,4,7,8], W = 3
 Output: true
 Explanation: Alice's hand can be rearranged as [1,2,3],[2,3,4],[6,7,8].
 Example 2:
 
 Input: hand = [1,2,3,4,5], W = 4
 Output: false
 Explanation: Alice's hand can't be rearranged into groups of 4.
 
 
 Note:
 
 1 <= hand.length <= 10000
 0 <= hand[i] <= 10^9
 1 <= W <= hand.length
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
using namespace std;

class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int W) {
        if (hand.size() % W != 0) {
            return false;
        }
        
        map<int, int> count;
        for (int card : hand) {
            count[card] += 1;
        }
        
        for (auto c : count) {
            if (c.second > 0) {
                for (int i = 1; i < W; i++) {
                    if (count.find(c.first + i) == count.end()) {
                        return false;
                    }
                    count[c.first + i] -= c.second;
                    if (count[c.first + i] < 0) {
                        return false;
                    }
                }
            }
        }
        return true;
    }
};
