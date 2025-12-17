/*
https://leetcode.com/problems/longest-common-prefix-between-adjacent-strings-after-removals/description/
3598. Longest Common Prefix Between Adjacent Strings After Removals

You are given an array of strings words. For each index i in the range [0, words.length - 1], perform the following
steps:

Remove the element at index i from the words array.
Compute the length of the longest common prefix among all adjacent pairs in the modified array.
Return an array answer, where answer[i] is the length of the longest common prefix between the adjacent pairs after
removing the element at index i. If no adjacent pairs remain or if none share a common prefix, then answer[i] should be
0.



Example 1:

Input: words = ["jump","run","run","jump","run"]

Output: [3,0,0,3,3]

Explanation:

Removing index 0:
words becomes ["run", "run", "jump", "run"]
Longest adjacent pair is ["run", "run"] having a common prefix "run" (length 3)
Removing index 1:
words becomes ["jump", "run", "jump", "run"]
No adjacent pairs share a common prefix (length 0)
Removing index 2:
words becomes ["jump", "run", "jump", "run"]
No adjacent pairs share a common prefix (length 0)
Removing index 3:
words becomes ["jump", "run", "run", "run"]
Longest adjacent pair is ["run", "run"] having a common prefix "run" (length 3)
Removing index 4:
words becomes ["jump", "run", "run", "jump"]
Longest adjacent pair is ["run", "run"] having a common prefix "run" (length 3)
Example 2:

Input: words = ["dog","racer","car"]

Output: [0,0,0]

Explanation:

Removing any index results in an answer of 0.


Constraints:

1 <= words.length <= 105
1 <= words[i].length <= 104
words[i] consists of lowercase English letters.
The sum of words[i].length is smaller than or equal 105.
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
#include <climits>
using namespace std;

class Solution {
private:
    int common_prefix_len(string& word1, string& word2, unordered_map<string, unordered_map<string, int>>& memo) {
        if (memo.find(word1) != memo.end() && memo[word1].find(word2) != memo[word1].end()) {
            return memo[word1][word2];
        }

        int n1 = word1.length();
        int n2 = word2.length();
        int rst = 0;
        for (int i = 0, j = 0; i < n1 && j < n2; i++, j++) {
            if (word1[i] != word2[j]) {
                break;
            }
            rst += 1;
        }
        memo[word1][word2] = rst;
        return rst;
    }

public:
    vector<int> longestCommonPrefix(vector<string>& words) {
        int n = words.size();
        if (n <= 2) {
            return vector<int>(n, 0);
        }

        vector<int> longest_prefix_len_forward(n, 0);
        vector<int> longest_prefix_len_backward(n, 0);
        unordered_map<string, unordered_map<string, int>> memo;
        for (int i = 1; i < n; i++) {
            longest_prefix_len_forward[i] =
                    max(longest_prefix_len_forward[i - 1], common_prefix_len(words[i - 1], words[i], memo));
            longest_prefix_len_backward[n - 1 - i] =
                    max(longest_prefix_len_backward[n - i], common_prefix_len(words[n - 1 - i], words[n - i], memo));
        }

        vector<int> rst(n, 0);
        rst[0] = longest_prefix_len_backward[1];
        rst[n - 1] = longest_prefix_len_forward[n - 2];
        for (int i = 1; i <= n - 2; i++) {
            rst[i] = max(longest_prefix_len_forward[i - 1], longest_prefix_len_backward[i + 1]);
            rst[i] = max(rst[i], common_prefix_len(words[i - 1], words[i + 1], memo));
        }
        return rst;
    }
};