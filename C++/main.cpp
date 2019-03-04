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
using namespace std;

class Solution {
private:
    void merge(int length, int K, int& result, vector<int>& stones) {
        int sum = 0;
        int start = stones.size() - length;
        for (int i = 0; i < K; i++) {
            sum += stones[start + i];
        }

        result += sum;
        if (length == K) {
            return;
        }

        length -= K - 1;
        auto it = lower_bound(stones.begin(), stones.end(), sum);
        stones.insert(it, sum);
        merge(length, K, result, stones);
        return;
    }
public:
    int mergeStones(vector<int> stones, int K) {
        int n = stones.size();
        if (n < K or n % (K - 1) != 1) {
            return -1;
        }
        int result = 0;
        sort(stones.begin(), stones.end());
        merge(stones.size(), K, result, stones);
        return result;
    }
};

int main() {
    Solution s;
    s.mergeStones({1,2,3,4,5,6,7,8,9}, 3);
    return 0;
}
