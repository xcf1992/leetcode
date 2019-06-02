/*
395. Longest Substring with At Least K Repeating Characters

Find the length of the longest substring T of a given string (consists of lowercase letters only) such that every character in T appears no less than k times.

Example 1:

Input:
s = "aaabb", k = 3

Output:
3

The longest substring is "aaa", as 'a' is repeated 3 times.
Example 2:

Input:
s = "ababbc", k = 2

Output:
5

The longest substring is "ababb", as 'a' is repeated 2 times and 'b' is repeated 3 times.
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

/*
in the first pass I record counts of every character in a hashmap
in the second pass I locate the first character that appear less than k times in the string. this character is definitely not included in the result, and that separates the string into two parts.
keep doing this recursively and the maximum of the left/right part is the answer.
*/
class Solution {
private:
    int find(string s, int k, int start, int end) {
        unordered_map<char, int> count;
        for (int i = start; i < end; i++) {
            count[s[i]] += 1;
        }
        
        int result = 0;
        int left = start;
        while (left < end) {
            while (left < end && count[s[left]] < k) {
                left += 1;
            }
            
            int right = left;
            while (right < end && count[s[right]] >= k) {
                right += 1;
            }
            
            if (left == start && right == end) {
                return right - left;
            }
            result = max(result, find(s, k, left, right));
            left = right;
        }
        return result;
    }
public:
    int longestSubstring(string s, int k) {
        return find(s, k, 0, s.size());
    }
};
