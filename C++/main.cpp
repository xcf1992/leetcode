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

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    double soupServings(int N) {
        vector<vector<double>> dp(N + 1, vector<double>(N + 1, 0.0));
        dp[N][N] = 1.0;
        
        queue<pair<int, int>> q;
        q.push(make_pair(N, N));
        vector<vector<bool>> visited(N + 1, vector<bool>(N + 1, false));
        while(!q.empty()) {
            int num = q.size();
            for (int i = 0; i < num; i++) {
                pair<int, int> cur = q.front();
                q.pop();
                
                int leftA = cur.first - 100 >= 0 ? cur.first - 100 : 0;
                int leftB = cur.second;
                dp[leftA][leftB] += dp[cur.first][cur.second] * 0.25;
                if (!visited[leftA][leftB] && leftA > 0) {
                    q.push(make_pair(leftA, leftB));
                }
                
                leftA = cur.first - 75 >= 0 ? cur.first - 75 : 0;
                leftB = cur.second - 25 >= 0 ? cur.second - 25 : 0;
                dp[leftA][leftB] += dp[cur.first][cur.second] * 0.25;
                if (!visited[leftA][leftB] && leftA > 0 && leftB > 0) {
                    q.push(make_pair(leftA, leftB));
                }
                
                leftA = cur.first - 50 >= 0 ? cur.first - 50 : 0;
                leftB = cur.second - 50 >= 0 ? cur.second - 50 : 0;
                dp[leftA][leftB] += dp[cur.first][cur.second] * 0.25;
                if (!visited[leftA][leftB] && leftA > 0 && leftB > 0) {
                    q.push(make_pair(leftA, leftB));
                }
                
                leftA = cur.first - 25 >= 0 ? cur.first - 25 : 0;
                leftB = cur.second - 75 >= 0 ? cur.second - 75 : 0;
                dp[leftA][leftB] += dp[cur.first][cur.second] * 0.25;
                if (!visited[leftA][leftB] && leftA > 0 && leftB > 0) {
                    q.push(make_pair(leftA, leftB));
                }
            }
            visited.clear();
        }
        
        double result = 0.0;
        for (int j = 1; j <= N; j++) {
            result += dp[0][j];
        }
        return result + 0.5 * dp[0][0];
    }
};

int main() {
    Solution s;
    vector<string> v({"ahjpjau","ja","ahbwzgqnuk","tnmlanowax"});
    vector<int> v1({0,2});
    vector<string> v2({"a","cd"});
    vector<char> chars({'a','a','a','a','a','b','b','c'});
    vector<vector<int>> matrix({{0,0,1,1}, {1,0,1,0}, {1,1,0,0}});
    vector<pair<int, int>> fuxk;
    fuxk.push_back(make_pair(4,3));
    fuxk.push_back(make_pair(2,3));
    fuxk.push_back(make_pair(2,1));
    fuxk.push_back(make_pair(5,0));
    
    s.soupServings(50);
}
