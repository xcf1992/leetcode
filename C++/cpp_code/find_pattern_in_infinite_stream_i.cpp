/*
https://leetcode.com/problems/find-pattern-in-infinite-stream-i/description/
3023. Find Pattern in Infinite Stream I

You are given a binary array pattern and an object stream of class InfiniteStream representing a 0-indexed infinite
stream of bits.

The class InfiniteStream contains the following function:

int next(): Reads a single bit (which is either 0 or 1) from the stream and returns it.
Return the first starting index where the pattern matches the bits read from the stream. For example, if the pattern is
[1, 0], the first match is the highlighted part in the stream [0, 1, 0, 1, ...].



Example 1:

Input: stream = [1,1,1,0,1,1,1,...], pattern = [0,1]
Output: 3
Explanation: The first occurrence of the pattern [0,1] is highlighted in the stream [1,1,1,0,1,...], which starts at
index 3. Example 2:

Input: stream = [0,0,0,0,...], pattern = [0]
Output: 0
Explanation: The first occurrence of the pattern [0] is highlighted in the stream [0,...], which starts at index 0.
Example 3:

Input: stream = [1,0,1,1,0,1,1,0,1,...], pattern = [1,1,0,1]
Output: 2
Explanation: The first occurrence of the pattern [1,1,0,1] is highlighted in the stream [1,0,1,1,0,1,...], which starts
at index 2.


Constraints:

1 <= pattern.length <= 100
pattern consists only of 0 and 1.
stream consists only of 0 and 1.
The input is generated such that the pattern's start index exists in the first 105 bits of the stream.
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
#include <climits>
#include <set>
using namespace std;

/*
Definition for an infinite stream.
*/
class InfiniteStream {
public:
    InfiniteStream(vector<int> bits);
    int next();
};

/**
 * Definition for an infinite stream.
 * class InfiniteStream {
 * public:
 *     InfiniteStream(vector<int> bits);
 *     int next();
 * };
 */
class Solution {
public:
    int findPattern(InfiniteStream* stream, vector<int>& pattern) {
        const int m = pattern.size();
        vector<int> next(m);
        for (int i = 1, len = 0; i < m;) {
            if (pattern[i] == pattern[len]) {
                next[i++] = ++len;
            } else if (len == 0) {
                ++i;
            } else {
                len = next[len - 1];
            }
        }
        bool read = false;
        for (int i = 0, j = 0, c = 0;; ) {
            if (!read) {
                c = stream->next();
                read = true;
            }
            if (c == pattern[j]) {
                ++j;
                ++i;
                read = false;
                if (j == m) {
                    return i - m;
                }
            } else if (j) {
                j = next[j - 1];
            } else {
                ++i;
                read = false;
            }
        }
        return -1;


    }
};

class Solution {
// does not work if pattern size too big
public:
    int findPattern(InfiniteStream* stream, vector<int>& pattern) {
        int hash_pattern = 0;
        for (int i : pattern) {
            hash_pattern = (hash_pattern << 1) + i;
        }

        int pat_len = pattern.size();
        int hash_stream = 0;
        for (int i = 0; i < pat_len; i++) {
            hash_stream = (hash_stream << 1) + stream->next();
        }

        int rst = 0;
        int base = 1 << (pat_len - 1);
        while (true) {
            if (hash_stream == hash_pattern) {
                break;
            }

            if (hash_stream & base) {
                hash_stream ^= base;
            }
            hash_stream = (hash_stream << 1) + stream->next();
            rst += 1;
        }
        return rst;
    }
};