/*
Assumption
1. Given an API we can call, API takes a String from "1111" ~ "6666".
returns how many number is a match, correct position and value
2. Use this api to guess a number with as fewer API calls as possible

Approach:
1. So, we can first wrap the socket connection to a Connection class, then we will
use it to call the server.
2. We can first guess "1111", this way, we know how many 1 in the result.
we guess "2222" and we can know how many 2 in the result. and
so on. After this, for example, we know 1,2,2,4 are in the result, but we do not
know the order yet.
3. To get the order, we first fill an char array with the not exist
number, let's say 3. [3,3,3,3]. Then replace with [1,3,3,3], [3,1,3,3], [3,3,1,3] and
call api again ,we will know the position of 1. We do the same for the rest.

Time: at most 12 times of API calls
6+3+2+1 = 12
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
using namespace std;

class Solution {
private:
    int getMatchedCount(string target, string guess) {
        int result = 0;
        for (int i = 0; i < target.size(); ++i) {
            result += target[i] == guess[i] ? 1 : 0;
        }
        return result;
    }

public:
    string guestNumber(string target) {
        int n = target.size();
        vector<int> count(10, 0);
        string noMatched = "";
        for (int i = 0; i <= 9; ++i) {
            int matched = getMatchedCount(target, string(4, '0' + i));
            count[i] = matched;
            if (count[i] == 0 and noMatched == "") {
                noMatched = string(4, '0' + i);
            }
        }

        string result = noMatched;
        for (int i = 0; i <= 9; ++i)
            if (count[i] != 0) {
                string temp = result;
                int curMatched = getMatchedCount(target, temp);
                for (int k = 0; k < temp.size() and count[i] > 0; ++k) {
                    temp[k] = '0' + i;
                    int cur = getMatchedCount(target, temp);
                    if (cur == curMatched + 1) {
                        count[i] -= 1;
                        curMatched = cur;
                    } else {
                        temp[k] = result[k];
                    }
                }
                result = temp;
            }
        return result;
    }
};