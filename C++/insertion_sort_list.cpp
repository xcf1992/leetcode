/*
 147. Insertion Sort List

 Sort a linked list using insertion sort.


 A graphical example of insertion sort. The partial sorted list (black) initially contains only the first element in the list.
 With each iteration one element (red) is removed from the input data and inserted in-place into the sorted list


 Algorithm of Insertion Sort:

 Insertion sort iterates, consuming one input element each repetition, and growing a sorted output list.
 At each iteration, insertion sort removes one element from the input data, finds the location it belongs within the sorted list, and inserts it there.
 It repeats until no input elements remain.

 Example 1:

 Input: 4->2->1->3
 Output: 1->2->3->4
 Example 2:

 Input: -1->5->3->4->0
 Output: -1->0->3->4->5

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
#include <numeric>
#include "extra_data_types.hpp"
using namespace std;

class Solution {
public:
    ListNode *insertionSortList(ListNode *head) {
        if (head == nullptr or head -> next == nullptr) {
            return head;
        }

        ListNode* dummy = new ListNode(-1);
        dummy -> next = head;
        ListNode* cur = head -> next;
        head -> next = nullptr;
        while (cur != nullptr) {
            ListNode* pre = dummy;
            ListNode* aft = dummy -> next;

            while (aft != nullptr and aft -> val <= cur -> val) {
                pre = aft;
                aft = aft -> next;
            }
            pre -> next = cur;
            cur = cur -> next;
            pre -> next -> next = aft;
        }

        return dummy->next;
    }
};
