#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maximumGap(vector<int> &num) {
        if (num.size() < 2) {
            return 0;
        }
        
        int maxN = num[0];
        int minN = num[0];
        for (int i = 1; i < num.size(); i++) {
            maxN = max(maxN, num[i]);
            minN = min(minN, num[i]);
        }
        
        int gap = ceil((double)(maxN - minN) / (num.size() - 1));
        int bucketNum = (int)ceil(((double)(maxN - minN)) / gap);
        vector<int> maxA(bucketNum, INT_MIN);
        vector<int> minA(bucketNum, INT_MAX);
        vector<int> used(bucketNum, 0);
        
        for (int i = 0; i < num.size(); i++) {
            int k = (num[i] - minN) / gap;
            maxA[k] = max(maxA[k], num[i]);
            minA[k] = min(minA[k], num[i]);
            used[k] = 1;
        }
        
        int result = INT_MIN;
        int previous = minN;
        for (int i = 0; i < maxA.size(); i++) {
            if (used[i] == 0) {
                continue;
            }
            result = max(result, minA[i] - previous);
            previous = maxA[i];
        }
        result = max(result, maxN - maxA[bucketNum - 1]);
        return result;
    }
};

int main() {
	Solution s;
	int a[] = {1,1,1,1,1,5,5,5,5,5};
	vector<int> num;
	for (int i = 0; i <= 9; i++) {
		num.push_back(a[i]);
	}
	s.maximumGap(num);
	return 0;
}