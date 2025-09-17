/*
1362. Closest Divisors
https://leetcode.com/problems/closest-divisors/

Given an integer num,
find the closest two integers in absolute difference
whose product equals num + 1 or num + 2.
Return the two integers in any order.

Example 1:
Input: num = 8
Output: [3,3]
Explanation: For num + 1 = 9, the closest divisors are 3 & 3, for num + 2 = 10, the closest divisors are 2 & 5, hence 3 & 3 is chosen.

Example 2:
Input: num = 123
Output: [5,25]

Example 3:
Input: num = 999
Output: [40,25]

Constraints:
1 <= num <= 10^9
*/
package main

import (
	"math"
)

func Abs(x int) int {
	if x < 0 {
		return -x
	}
	return x
}

func getClosetPairs(num int) []int {
	var result []int = []int{1, num}
	for i := 2; i * i <= num; i++ {
		if num % i == 0 {
			result[0] = i
			result[1] = num / i
		}
	}
	return result
}

func closestDivisors(num int) []int {
	var pair1 []int = getClosetPairs(num + 1)
	var pair2 []int = getClosetPairs(num + 2)
    if Abs(pair1[0] - pair1[1]) < Abs(pair2[0] - pair2[1]) {
		return pair1
	}
	return pair2
}
