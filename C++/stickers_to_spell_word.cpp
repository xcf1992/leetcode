/*
 691. Stickers to Spell Word
 We are given N different types of stickers. Each sticker has a lowercase English word on it.

 You would like to spell out the given target string by cutting individual letters from your collection of stickers and rearranging them.

 You can use each sticker more than once if you want, and you have infinite quantities of each sticker.

 What is the minimum number of stickers that you need to spell out the target? If the task is impossible, return -1.

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
