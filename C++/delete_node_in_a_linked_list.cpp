#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
#include "extra_data_types.hpp"
using namespace std;

class Solution {
public:
    void deleteNode(ListNode* node) {
        if (node == nullptr) {
            return;
        }

        ListNode* nextNode = node -> next;
        node -> val = nextNode -> val;
        node -> next = nextNode -> next;
        delete(nextNode);
        nextNode = nullptr;

        return;
    }
};

int main() {
    Solution s;
    return 0;
}