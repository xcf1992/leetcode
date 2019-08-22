/*
691. Stickers to Spell Word
We are given N different types of stickers.
Each sticker has a lowercase English word on it.

You would like to spell out the given target string
by cutting individual letters from your collection of stickers and rearranging them.

You can use each sticker more than once if you want,
and you have infinite quantities of each sticker.

What is the minimum number of stickers that you need to spell out the target?
If the task is impossible, return -1.

Example 1:

Input:

["with", "example", "science"], "thehat"
Output:

3
Explanation:

We can use 2 "with" stickers, and 1 "example" sticker.
After cutting and rearrange the letters of those stickers, we can form the target "thehat".
Also, this is the minimum number of stickers necessary to form the target string.
Example 2:

Input:

["notice", "possible"], "basicbasic"
Output:

-1
Explanation:

We can't form the target "basicbasic" from cutting letters from the given stickers.
Note:

stickers has length in the range [1, 50].
stickers consists of lowercase English words (without apostrophes).
target has length in the range [1, 15], and consists of lowercase English letters.
In all test cases, all words were chosen randomly from the 1000 most common US English words, and the target was chosen as a concatenation of two random words.
The time limit may be more challenging than usual. It is expected that a 50 sticker test case can be solved within 35ms on average.
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
#include <set>
#include <numeric>
using namespace std;

class Solution {
private:
    int getNextState(string& sticker, string& target, int curState) {
        int nextState = curState;
        for (char c : sticker) {
            for (int i = 0; i < target.size(); ++i) {
                if (target[i] == c and ((nextState >> i) & 1) == 0) {
                    nextState |= 1 << i;
                    break; // if we fit current letter into one slot of target, we should break and check next letter from current sticker
                }
            }
        }
        return nextState;
    }
public:
    int minStickers(vector<string>& stickers, string target) {
        int n = target.size();
        vector<int> dp(1 << n, -1);
        dp[0] = 0;
        for (int state = 0; state < (1 << n); ++state) if (dp[state] != -1) {
            for (string& sticker : stickers) {
                int nextState = getNextState(sticker, target, state);
                if (dp[nextState] == -1 or dp[nextState] > dp[state] + 1) {
                    dp[nextState] = dp[state] + 1;
                }
            }
        }
        return dp[(1 << n) - 1];
    }
};

class Solution1 { // another way to write the solution, same idea from 1125. Smallest Sufficient Team
private:
    int getNextState(string& sticker, string& target, int curState) {
        int nextState = curState;
        for (char c : sticker) {
            for (int i = 0; i < target.size(); ++i) {
                if (target[i] == c and ((nextState >> i) & 1) == 0) {
                    nextState |= 1 << i;
                    break; // if we fit current letter into one slot of target, we should break and check next letter from current sticker
                }
            }
        }
        return nextState;
    }
public:
    int minStickers(vector<string>& stickers, string target) {
        int n = target.size();
        map<int, int> dp;
        dp[0] = 0;
        for (string& sticker : stickers) {
            for (auto it = dp.begin(); it != dp.end(); ++it) {
                int state = it -> first;
                int nextState = getNextState(sticker, target, state);
                if (dp.find(nextState) == dp.end() or dp[nextState] > dp[state] + 1) {
                    dp[nextState] = dp[state] + 1;
                }
            }
        }
        return dp.find((1 << n) - 1) == dp.end() ? -1 : dp[(1 << n) - 1];
    }
};

class Solution2 { // TLE
public:
    int minStickers(vector<string>& stickers, string target) {
        int n = stickers.size();
        vector<vector<int>> dic(n, vector<int>(26, 0));
        for (int i = 0; i < n; i++) {
            string& sticker = stickers[i];
            for (int j = 0; j < sticker.size(); j++) {
                dic[i][sticker[j] - 'a'] += 1;
            }
        }

        vector<int> tar(26, 0);
        for (char c : target) {
            tar[c - 'a'] += 1;
        }

        unordered_set<string> visited;
        queue<vector<int>> bfs;
        bfs.push(tar);
        int result = 0;
        vector<int> spelled(26, 0);
        while (!bfs.empty()) {
            int curSize = bfs.size();
            result += 1;
            for (int i = 0; i < curSize; i++) {
                for (int j = 0; j < dic.size(); j++) {
                    vector<int> temp = bfs.front();
                    string s = "";
                    for (int k = 0; k < 26; k++) {
                        if (dic[j][k] >= temp[k]) {
                            temp[k] = 0;
                        }
                        else {
                            temp[k] -= dic[j][k];
                        }
                        s += to_string(temp[k]) + "#";
                    }
                    if (temp == spelled) {
                        return result;
                    }
                    if (temp != bfs.front() and visited.find(s) == visited.end()) {
                        bfs.push(temp);
                        visited.insert(s);
                    }
                }
                bfs.pop();
            }
        }
        return -1;
    }
};
