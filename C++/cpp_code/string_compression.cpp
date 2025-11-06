/*
443. String Compression

Given an array of characters, compress it in-place.
The length after compression must always be smaller than or equal to the original array.
Every element of the array should be a character (not int) of length 1.
After you are done modifying the input array in-place, return the new length of the array.

Follow up:
Could you solve it using only O(1) extra space?

Example 1:
Input:
["a","a","b","b","c","c","c"]
Output:
Return 6, and the first 6 characters of the input array should be: ["a","2","b","2","c","3"]
Explanation:
"aa" is replaced by "a2". "bb" is replaced by "b2". "ccc" is replaced by "c3".

Example 2:
Input:
["a"]
Output:
Return 1, and the first 1 characters of the input array should be: ["a"]
Explanation:
Nothing is replaced.

Example 3:
Input:
["a","b","b","b","b","b","b","b","b","b","b","b","b"]
Output:
Return 4, and the first 4 characters of the input array should be: ["a","b","1","2"].
Explanation:
Since the character "a" does not repeat, it is not compressed. "bbbbbbbbbbbb" is replaced by "b12".
Notice each digit has it's own entry in the array.

Note:
All characters have an ASCII value in [35, 126].
1 <= len(chars) <= 1000.
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
    void update(vector<char>& chars, int count, int& start) {
        if (count == 1) {
            return;
        }

        for (char c : to_string(count)) {
            chars[start] = c;
            start += 1;
        }
    }

public:
    int compress(vector<char>& chars) {
        int n = chars.size();
        if (n <= 1) {
            return n;
        }

        int start = 0;
        int count = 0;
        for (int end = 0; end < n; ++end) {
            if (chars[end] == chars[start]) {
                count += 1;
                continue;
            }

            start += 1;
            update(chars, count, start);
            count = 1;
            chars[start] = chars[end];
        }

        start += 1;
        update(chars, count, start);
        return start;
    }
};