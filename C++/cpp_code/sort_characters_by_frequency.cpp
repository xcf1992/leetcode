/*
451. Sort Characters By Frequency

Given a string, sort it in decreasing order based on the frequency of characters.

Example 1:
Input:
"tree"
Output:
"eert"
Explanation:
'e' appears twice while 'r' and 't' both appear once.
So 'e' must appear before both 'r' and 't'. Therefore "eetr" is also a valid answer.

Example 2:
Input:
"cccaaa"
Output:
"cccaaa"
Explanation:
Both 'c' and 'a' appear three times, so "aaaccc" is also a valid answer.
Note that "cacaca" is incorrect, as the same characters must be together.

Example 3:
Input:
"Aabb"
Output:
"bbAa"
Explanation:
"bbaA" is also a valid answer, but "Aabb" is incorrect.
Note that 'A' and 'a' are treated as two different characters.
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
    // buscket sort O(n)
public:
    string frequencySort(string s) {
        unordered_map<char, int> count;
        for (auto c : s) {
            count[c] += 1;
        }

        int n = s.size();
        vector<string> bucket(n + 1, "");
        for (auto& it : count) {
            bucket[it.second] += string(it.second, it.first);
        }

        string result = "";
        for (int i = n; i > 0; --i)
            if (!bucket[i].empty()) {
                result += bucket[i];
            }
        return result;
    }
};