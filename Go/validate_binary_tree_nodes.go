/*
1361. Validate Binary Tree Nodes
https://leetcode.com/problems/validate-binary-tree-nodes/

You have n binary tree nodes numbered from 0 to n - 1
where node i has two children leftChild[i] and rightChild[i],
return true if and only if all the given nodes form exactly one valid binary tree.

If node i has no left child then leftChild[i] will equal -1,
similarly for the right child.
Note that the nodes have no values and that we only use the node numbers in this problem.

Example 1:
			0
	1			2
			3
Input: n = 4, leftChild = [1,-1,3,-1], rightChild = [2,-1,-1,-1]
Output: true

Example 2:
		0
	1		2
		3
Input: n = 4, leftChild = [1,-1,3,-1], rightChild = [2,3,-1,-1]
Output: false

Example 3:
		0
	1
Input: n = 2, leftChild = [1,0], rightChild = [-1,-1]
Output: false

Example 4:
	0					3
1		2			4		5
Input: n = 6, leftChild = [1,-1,-1,4,-1,-1], rightChild = [2,-1,-1,5,-1,-1]
Output: false

Constraints:
1 <= n <= 10^4
leftChild.length == rightChild.length == n
-1 <= leftChild[i], rightChild[i] <= n - 1
*/
package main

import (
	"math"
)

func find(parent []int, cur int) int {
	if cur != parent[cur] {
		parent[cur] = find(parent, parent[cur])
	}
	return parent[cur]
}

func validateBinaryTreeNodes(n int, leftChild []int, rightChild []int) bool {
	var parent []int = make([]int, n, n)
    for i := range parent {
		parent[i] = i
	}

    for i := range parent {
		var p int = find(parent, i)
		if leftChild[i] != -1 {
			var lp int = find(parent, leftChild[i])
			if p != lp {
				parent[lp] = p
			} else {
				return false
			}
		}
		if rightChild[i] != -1 {
			var rp int = find(parent, rightChild[i])
			if p != rp {
				parent[rp] = p
			} else {
				return false
			}
		}
	}

	var count int = 0
    for i, root := range parent {
		if i == root {
			count++
		}
	}

	if count == 1 {
		return true
	}
	return false
}
