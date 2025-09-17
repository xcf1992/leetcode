/*
1358. Number of Substrings Containing All Three Characters
https://leetcode.com/problems/number-of-substrings-containing-all-three-characters/

Given a string s consisting only of characters a, b and c.
Return the number of substrings containing at least one occurrence of all these characters a, b and c.

Example 1:
Input: s = "abcabc"
Output: 10
Explanation: The substrings containing at least one occurrence of the characters a, b and c are "abc", "abca", "abcab", "abcabc", "bca", "bcab", "bcabc", "cab", "cabc" and "abc" (again).

Example 2:
Input: s = "aaacb"
Output: 3
Explanation: The substrings containing at least one occurrence of the characters a, b and c are "aaacb", "aacb" and "acb".

Example 3:
Input: s = "abc"
Output: 1

Constraints:
3 <= s.length <= 5 x 10^4
s only consists of a, b or c characters.
*/
package main

import (
	"fmt"
)

func minOf(vars ...int) int {
	min := vars[0]
	for _, i := range vars {
		if min > i {
			min = i
		}
	}
	return min
}

/*
last will record the position of last occurrence.
If the ending index of substring is i,
the starting position should be on the left of min(last),
in order to have all 3 different letters.
And in this case, the starting index can be in range [0, min(last)],
min(last) + 1 in total.
*/
func numberOfSubstrings(s string) int {
	var result int = 0
	var lastIndex = []int{-1, -1, -1}
	var n int = len(s)
	for i := 0; i < n; i++ {
		lastIndex[s[i]-'a'] = i
		result += minOf(lastIndex[0], lastIndex[1], lastIndex[2]) + 1
	}
	return result
}
