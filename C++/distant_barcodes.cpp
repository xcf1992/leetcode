/*
1054. Distant Barcodes

In a warehouse, there is a row of barcodes, where the i-th barcode is barcodes[i].

Rearrange the barcodes so that no two adjacent barcodes are equal.
You may return any answer, and it is guaranteed an answer exists.

Example 1:

Input: [1,1,1,2,2,2]
Output: [2,1,2,1,2,1]
Example 2:

Input: [1,1,1,1,2,2,3,3]
Output: [1,3,1,3,2,1,2,1]


Note:

1 <= barcodes.length <= 10000
1 <= barcodes[i] <= 10000
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
#include <set>
#include <numeric>
using namespace std;
/*
faster solution
Intuition
In the worst case, we can have (N + 1) / 2 occurrences of the same barcode.
This barcode needs to be placed in [0, 2, 4 ...] positions to avoid the repetition.

Solution
Count occurrences of each barcode using a hash map
Use a set to sort barcodes by their number of occurrences
Starting from most frequent, fill even positions with barcodes
Then fill odd positions with remaining barcodes
*/
class Solution {
public:
    vector<int> rearrangeBarcodes(vector<int>& barcodes) {
        vector<int> count(10001, 0);
        int max_cnt = 0;
        int max_num = 0;
        for (auto num : barcodes) {
            max_cnt = max(max_cnt, ++count[num]);
            max_num = max_cnt == count[num] ? num : max_num;
        }

        int pos = 0;
        for (int i = 0; i <= 10000; ++i) {
            int num = i == 0 ? max_num : i;
            while (count[num] > 0) {
                barcodes[pos] = num;
                pos = pos + 2 < barcodes.size() ? pos + 2 : 1;
                count[num] -= 1;
            }
        }
        return barcodes;
    }
};

struct myComp {
    bool operator()(pair<int, int>& a, pair<int, int>& b) {
        return a.second < b.second or (a.second == b.second and a < b);
    }
};

class Solution1 {
public:
    vector<int> rearrangeBarcodes(vector<int>& barcodes) {
        unordered_map<int, int> count;
        for (int code : barcodes) {
            count[code] += 1;
        }

        priority_queue<pair<int, int>, vector<pair<int, int>>, myComp> pq;
        for (auto& it : count) {
            pq.push({it.first, it.second});
        }

        vector<int> result;
        while (!pq.empty()) {
            int code1 = pq.top().first;
            int count1 = pq.top().second;
            pq.pop();

            result.push_back(code1);
            if (!pq.empty()) {
                int code2 = pq.top().first;
                int count2 = pq.top().second;
                pq.pop();

                result.push_back(code2);
                if (count2 - 1 > 0) {
                    pq.push({code2, count2 - 1});
                }
            }
            if (count1 - 1 > 0) {
                pq.push({code1, count1 - 1});
            }
        }
        return result;
    }
};
