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
using namespace std;

struct myComp {
    bool operator() (pair<int, int>& p1, pair<int, int>& p2) {
        return p1.first < p2.first || (p1.first == p2.first && p1.second > p2.second);
    }
};

class Solution {
public:
    vector<pair<int, int>> getSkyline(vector<vector<int>> buildings) {
        set<int> points;
        for (vector<int>& building : buildings) {
            points.insert(building[0]);
            points.insert(building[1]);
        }
        
        vector<pair<int, int>> skyline;
        int lastHeight = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, myComp> pq;
        int cur = 0;
        for (int point : points) {
            while (cur != buildings.size() and buildings[cur][0] <= point) {
                pq.push(make_pair(buildings[cur][1], buildings[cur][2]));
                cur += 1;
            }
            
            while (!pq.empty() && pq.top().first <= point) {
                pq.pop();
            }
            
            int height = 0;
            if (!pq.empty()) {
                height = pq.top().second;
            }
            
            if (height != lastHeight) {
                lastHeight = height;
                skyline.push_back(make_pair(point, height));
            }
        }
        return skyline;
    }
};

int main() {
    Solution s;
    vector<string> v({"ahjpjau","ja","ahbwzgqnuk","tnmlanowax"});
    vector<int> va({4,5,8,2});
    vector<int> vb({3,2});
    vector<string> v2({"a","cd"});
    vector<char> chars({'a','a','a','a','a','b','b','c'});
    
    vector<vector<int>> matrix1({{1,2}, {0}, {0}});
    vector<vector<char>> matrix2({
        {'1','1','1','1','1','1','1','1'},
        {'1','1','1','1','1','1','1','0'},
        {'1','1','1','1','1','1','1','0'},
        {'1','1','1','1','1','0','0','0'},
        {'0','1','1','1','1','0','0','0'}
    });
    
    s.getSkyline({{2,9,10},{3,7,15},{5,12,12},{15,20,10},{19,24,8}});
    return 0;
}
