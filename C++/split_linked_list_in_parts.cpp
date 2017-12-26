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
using namespace std;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    vector<ListNode*> splitListToParts(ListNode* root, int k) {
        vector<ListNode *> result(k, nullptr);
        
        int length = 0;
        ListNode* cur = root;
        while (cur != nullptr) {
            length += 1;
            cur = cur -> next;
        }
        
        cur = root;
        int segment = length / k;
        int extra = length % k;
        int index = 0;
        ListNode* fake = nullptr;
        while (cur != nullptr) {
            int temp = segment;
            result[index++] = cur;
            while (cur != nullptr && temp != 0) {
                temp -= 1;
                fake = cur;
                cur = cur -> next;
            }
            
            if (cur != nullptr && extra != 0) {
                fake = cur;
                cur = cur -> next;
                extra -= 1;
            }
            fake -> next = nullptr;
        }
        return result;
    }
};
