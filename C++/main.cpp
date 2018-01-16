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
private:
    int pick(unordered_map<int, int> counts) {
        int result = 0;
        for (pair<int, int> count : counts) {
            if (count.second != 0) {
                int num = count.first;
                int times = count.second;
                int value = num * times;
                int temp1 = counts[num - 1];
                int temp2 = counts[num + 1];
                
                counts[num] = 0;
                counts[num - 1] = 0;
                counts[num + 1] = 0;
                
                value += pick(counts);
                result = max(result, value);
                
                counts[num] = times;
                counts[num - 1] = temp1;
                counts[num + 1] = temp2;
            }
        }
        return result;
    }
public:
    int deleteAndEarn(vector<int>& nums) {
        unordered_map<int, int> counts;
        for (int num : nums) {
            counts[num] += 1;
        }
        
        return pick(counts);
    }
};

int main() {
    Solution s;
    vector<int>v{12,32,93,17,100,72,40,71,37,92,58,34,29,78,11,84,77,90,92,35,12,5,27,92,91,23,65,91,85,14,42,28,80,85,38,71,62,82,66,3,33,33,55,60,48,78,63,11,20,51,78,42,37,21,100,13,60,57,91,53,49,15,45,19,51,2,96,22,32,2,46,62,58,11,29,6,74,38,70,97,4,22,76,19,1,90,63,55,64,44,90,51,36,16,65,95,64,59,53,93};
    cout << s.deleteAndEarn(v) << endl;
}
