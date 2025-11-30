#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>
using namespace std;

class Solution {
public:
    vector<string> findRestaurant(vector<string>& list1, vector<string>& list2) {
        unordered_map<string, int> restaurant;
        for (int i = 0; i < list1.size(); i++) {
            restaurant[list1[i]] = i;
        }

        unordered_map<int, vector<string>> result;
        int minIndex = 2000;
        for (int i = 0; i < list2.size(); i++) {
            if (restaurant.find(list2[i]) != restaurant.end()) {
                int index = i + restaurant[list2[i]];
                result[index].push_back(list2[i]);
                minIndex = min(index, minIndex);
            }
        }

        return result[minIndex];
    }
};

int main() {
    Solution s;
    return 0;
}