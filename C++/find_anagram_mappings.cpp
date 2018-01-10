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
public:
    vector<int> anagramMappings(vector<int>& A, vector<int>& B) {
        vector<int> result;
        unordered_map<int, int> pos;
        for (int i = 0; i < B.size(); i++) {
            pos[B[i]] = i;
        }
        for (int num : A) {
            result.push_back(pos[num]);
        }
        return result;
    }
};
