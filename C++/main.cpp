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

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    char nextGreatestLetter(vector<char>& letters, char target) {
        if (target >= letters.back()) {
            return letters.front();
        }
        
        if (letters.front() > target) {
            return letters.front();
        }
        int start = 0;
        int end = letters.size() - 1;
        while (start < end) {
            int mid = start + (end - start) >> 1;
            if (letters[mid] <= target) {
                start = mid + 1;
            }
            else {
                end = mid;
            }
        }
        return letters[end];
    }
};

int main() {
    Solution s;
    vector<char> v{'e','e','e','e','e','e','n','n','n','n'};
    s.nextGreatestLetter(v, 'e');
}
