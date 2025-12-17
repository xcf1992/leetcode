/*
https://leetcode.com/problems/minimum-pair-removal-to-sort-array-ii/description/
3510. Minimum Pair Removal to Sort Array II

Given an array nums, you can perform the following operation any number of times:

Select the adjacent pair with the minimum sum in nums. If multiple such pairs exist, choose the leftmost one.
Replace the pair with their sum.
Return the minimum number of operations needed to make the array non-decreasing.

An array is said to be non-decreasing if each element is greater than or equal to its previous element (if it exists).



Example 1:

Input: nums = [5,2,3,1]

Output: 2

Explanation:

The pair (3,1) has the minimum sum of 4. After replacement, nums = [5,2,4].
The pair (2,4) has the minimum sum of 6. After replacement, nums = [5,6].
The array nums became non-decreasing in two operations.

Example 2:

Input: nums = [1,2,2]

Output: 0

Explanation:

The array nums is already sorted.



Constraints:

1 <= nums.length <= 105
-109 <= nums[i] <= 109
*/
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>
#include <set>
using namespace std;

class Node {
public:
    Node* prev_;
    Node* next_;
    long long val_;
    int idx_;  // original index

    Node(Node* p, Node* n, long long v, int idx) : prev_(p), next_(n), val_(v), idx_(idx) {
    }
};

struct MergePair {
    long long sum_;  // sum of the adjacent nodes
    int left_idx_;   // for tie-breaking: lower leftIndex means leftmost candidate
    Node* left_node_;
    Node* right_node_;
};

struct CompareMergePair {
    bool operator()(const MergePair& a, const MergePair& b) const {
        if (a.sum_ != b.sum_) {
            return a.sum_ > b.sum_;        // min-heap: lower sum comes first.
        }
        return a.left_idx_ > b.left_idx_;  // if equal, the leftmost one wins.
    }
};

class Solution {
public:
    int minimumPairRemoval(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) {
            return 0;
        }

        // Build the doubly linked list.
        Node* head = nullptr;
        Node* prev = nullptr;
        for (int i = 0; i < n; i++) {
            Node* node = new Node(prev, nullptr, static_cast<long long>(nums[i]), i);
            if (prev != nullptr) {
                prev->next_ = node;
            } else {
                head = node;
            }
            prev = node;
        }

        // Priority queue for candidate merge pairs.
        priority_queue<MergePair, vector<MergePair>, CompareMergePair> pq;
        unordered_set<Node*> invalid;  // nodes that have already been merged.
        int cnt = 0;                   // count of adjacent non-decreasing pairs
        for (Node* cur = head; cur && cur->next_; cur = cur->next_) {
            if (cur->val_ <= cur->next_->val_) {
                cnt++;
            }
            pq.push({cur->val_ + cur->next_->val_, cur->idx_, cur, cur->next_});
        }

        int merges = 0;
        for (; merges < n - 1; merges++) {
            int target = n - merges - 1;
            if (cnt == target) {
                return merges;
            }

            MergePair cand;
            bool found = false;
            while (!pq.empty()) {
                cand = pq.top();
                pq.pop();
                if (cand.left_node_ == nullptr || cand.right_node_ == nullptr)
                    continue;
                if (cand.left_node_->next_ != cand.right_node_)
                    continue;
                if (invalid.count(cand.left_node_) || invalid.count(cand.right_node_))
                    continue;
                found = true;
                break;
            }
            if (!found)
                return n - 1;

            Node* leftNode = cand.left_node_;
            Node* rightNode = cand.right_node_;
            Node* leftOfLeft = leftNode->prev_;
            Node* rightOfRight = rightNode->next_;

            if (leftOfLeft && leftOfLeft->val_ <= leftNode->val_)
                cnt--;
            if (leftNode->val_ <= rightNode->val_)
                cnt--;
            if (rightOfRight && rightNode->val_ <= rightOfRight->val_)
                cnt--;

            int newIndex = leftNode->idx_;
            long long mergedVal = leftNode->val_ + rightNode->val_;
            Node* mergedNode = new Node(leftOfLeft, rightOfRight, mergedVal, newIndex);

            if (leftOfLeft)
                leftOfLeft->next_ = mergedNode;
            else
                head = mergedNode;
            if (rightOfRight)
                rightOfRight->prev_ = mergedNode;

            if (leftOfLeft && leftOfLeft->val_ <= mergedNode->val_)
                cnt++;
            if (rightOfRight && mergedNode->val_ <= rightOfRight->val_)
                cnt++;

            invalid.insert(leftNode);
            invalid.insert(rightNode);
            leftNode->prev_ = leftNode->next_ = nullptr;
            rightNode->prev_ = rightNode->next_ = nullptr;

            // Instead of rebuilding entire PQ (which incurred TLE),
            // we use lazy invalidation: simply push the new adjacent candidates.
            if (leftOfLeft) {
                long long s = leftOfLeft->val_ + mergedNode->val_;
                pq.push({s, leftOfLeft->idx_, leftOfLeft, mergedNode});
            }
            if (rightOfRight) {
                long long s = mergedNode->val_ + rightOfRight->val_;
                pq.push({s, mergedNode->idx_, mergedNode, rightOfRight});
            }
        }
        return n - 1;
    }
};
