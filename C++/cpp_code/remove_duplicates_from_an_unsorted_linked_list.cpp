/*
https://leetcode.com/problems/remove-duplicates-from-an-unsorted-linked-list/description/
1836. Remove Duplicates From an Unsorted Linked List

Given the head of a linked list, find all the values that appear more than once in the list and delete the nodes that
have any of those values.

Return the linked list after the deletions.



Example 1:


Input: head = [1,2,3,2]
Output: [1,3]
Explanation: 2 appears twice in the linked list, so all 2's should be deleted. After deleting all 2's, we are left with
[1,3]. Example 2:


Input: head = [2,1,1,2]
Output: []
Explanation: 2 and 1 both appear twice. All the elements should be deleted.
Example 3:


Input: head = [3,2,2,1,3,2,4]
Output: [1,4]
Explanation: 3 appears twice and 2 appears three times. After deleting all 3's and 2's, we are left with [1,4].


Constraints:

The number of nodes in the list is in the range [1, 105]
1 <= Node.val <= 105
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
#include <map>
#include <set>
#include <numeric>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {
    }
    ListNode(int x) : val(x), next(nullptr) {
    }
    ListNode(int x, ListNode* next) : val(x), next(next) {
    }
};

class Solution {
public:
    ListNode* deleteDuplicatesUnsorted(ListNode* head) {
        if (head == nullptr) {
            return head;
        }

        unordered_map<int, int> cnt;
        ListNode* cur = head;
        while (cur != nullptr) {
            cnt[cur->val]++;
            cur = cur->next;
        }

        ListNode* dummy = new ListNode(-1);
        ListNode* prev = dummy;
        cur = head;
        while (cur != nullptr) {
            ListNode* nxt = cur->next;
            cur->next = nullptr;
            if (cnt[cur->val] == 1) {
                prev->next = cur;
                prev = cur;
            }
            cur = nxt;
        }
        return dummy -> next;
    }
};