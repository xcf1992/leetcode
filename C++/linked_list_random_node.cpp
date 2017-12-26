#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
using namespace std;


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(nullptr) {}
 * };
 */
class Solution {
private:
    ListNode* start = nullptr;
public:
    /** @param head The linked list's head.
        Note that the head is guaranteed to be not null, so it contains at least one node. */
    Solution(ListNode* head) {
        start = head;
    }

    /** Returns a random node's value. */
    int getRandom() {
        int result = start->val;
        ListNode* current = start -> next;

        int i = 2;
        while (current) {
            if (rand() % i == 0) {
                result = current -> val;
            }
            i++;
            current = current -> next;
        }

        return result;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(head);
 * int param_1 = obj.getRandom();
 */

int main() {
    Solution s;
    return 0;
}