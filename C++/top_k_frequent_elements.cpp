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


class Solution {
private:
    struct myCmp {
        bool operator()(const pair<int, int> &myPair1, const pair<int, int> &myPair2) {
            return myPair1.first < myPair2.first;
        }
        
    };
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        std::vector<int> result;

        unordered_map<int, int> frequency;
        for (int i = 0; i < nums.size(); i++) {
            frequency[nums[i]] += 1;
        }

        priority_queue<pair<int, int>, vector<pair<int, int> >, myCmp> pq;
        for (auto& it : frequency) {
            pq.push(make_pair(it.second, it.first));
        }

        while (!pq.empty() && result.size() < k) {
            auto& p = pq.top();
            result.push_back(p.second);
            pq.pop();
        }
        
        return result;
    }
};

int main() {
    Solution s;
    return 0;
}