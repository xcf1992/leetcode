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
    void getFactors(int index, int number, unordered_map<int, vector<int>>& factorToIndex) {
        for (int i = 2; i * i <= number; i++) {
            if (number % i == 0) {
                factorToIndex[i].push_back(index);
                while (number % i == 0) {
                    number /= i;
                }
            }
            
        }
    }
    
    int find(int index, vector<int>& parent, vector<int>& count) {
        if (parent[index] == -1) {
            return index;
        }
        count[parent[index]] += count[index];
        count[index] = 0;
        return find(parent[index], parent, count);
    }
    
    void unin(int index1, int index2, vector<int>& parent, vector<int>& count) {
        int p1 = find(index1, parent, count);
        int p2 = find(index2, parent, count);
        if (p1 != p2) {
            parent[p2] = p1;
            count[p1] += count[p2];
            count[p2] = 0;
        }
    }
public:
    int largestComponentSize(vector<int> A) {
        int n = A.size();
        unordered_map<int, vector<int>> factorToIndex;
        for (int i = 0; i < n; i++) {
            getFactors(i, A[i], factorToIndex);
        }
        
        vector<int> parent(n, -1);
        vector<int> count(n, 1);
        for (auto it = factorToIndex.begin(); it != factorToIndex.end(); it++) {
            vector<int> connectedIndex = it -> second;
            int p = connectedIndex[0];
            for (int i = 1; i < connectedIndex.size(); i++) {
                unin(p, connectedIndex[i], parent, count);
            }
        }
        
        int result = 1;
        for (int i = 0; i < n; i++) {
            result = max(result, count[find(i, parent, count)]);
        }
        return result;
    }
};

int main() {
    vector<bool> visited(10, false);
    visited[2] = true;
    visited[7] = true;
    visited[4] = true;
    visited.resize(10, false);
    visited.clear();
    Solution s;
    vector<string> v({"ahjpjau","ja","ahbwzgqnuk","tnmlanowax"});
    vector<int> va({4,5,8,2});
    vector<vector<int>> vb({{3,0}});
    vector<string> v2({"a","cd"});
    vector<char> chars({'a','a','a','a','a','b','b','c'});
    
    vector<vector<int>> matrix1({
        {1,1,1,0,1,1,1,1},
        {1,0,0,0,0,1,1,1},
        {1,1,1,0,0,0,1,1},
        {1,1,0,0,0,0,0,0},
        {1,0,0,0,0,0,0,0},
        {1,0,0,0,0,0,0,0}
    });
    vector<vector<char>> matrix2({
        {'1','1','1','1','1','1','1','1'},
        {'1','1','1','1','1','1','1','0'},
        {'1','1','1','1','1','1','1','0'},
        {'1','1','1','1','1','0','0','0'},
        {'0','1','1','1','1','0','0','0'}
    });
    vector<vector<int>> matrix3({
        {1,0},
        {0,1}
    });
    s.largestComponentSize({4,6,15,35});
    return 0;
}
