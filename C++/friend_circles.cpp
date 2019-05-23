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

//https://leetcode.com/problems/friend-circles/discuss/101336/Java-solution-Union-Find
class Solution {
private:
    int find(int num, vector<int>& friends) {
        while (friends[num] != num) {
            friends[num] = friends[friends[num]];
            num = friends[num];
        }
        return friends[num];
    }
    
    void unin(int num1, int num2, vector<int>& friends, vector<int>& count) {
        int f1 = find(num1, friends);
        int f2 = find(num2, friends);
        if (f1 == f2) {
            return;
        }
        
        if (count[f1] > count[f2]) {
            friends[f2] = f1;
            count[f1] += count[f2];
        }
        else {
            friends[f1] = f2;
            count[f2] += count[f1];
        }
    }
public:
    int findCircleNum(vector<vector<int>>& M) {
        int n = M.size();
        vector<int> friends(n, -1);
        for (int i = 0; i < n; ++i) {
            friends[i] = i;
        }
        vector<int> count(n, 1);
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (M[i][j]) {
                    unin(i, j, friends, count);
                }
            }
        }
        
        int result = 0;
        for (int i = 0; i < n; ++i) {
            if (friends[i] == i) {
                result += 1;
            }
        }
        return result;
    }
};

class Solution1 {
private:
    void visit(vector<vector<int>>& M, vector<bool>& visited, int start) {
        visited[start] = true;
        for (int i = 0; i < M[0].size(); i++) {
            if (!visited[i] && M[start][i]) {
                visit(M, visited, i);
            }
        }
    }

public:
    int findCircleNum(vector<vector<int>>& M) {
        vector<bool> visited(M.size(), false);
        int result = 0;
        for (int i = 0; i < M.size(); i++) {
            if (!visited[i]) {
                visited[i] = true;
                result += 1;
                for (int j = 0; j < M[0].size(); j++) {
                    if (!visited[j] && M[i][j]) {
                        visit(M, visited, j);
                    }
                }
            }
        }
        return result;
    }
};

int main() {
    Solution s;
    return 0;
}
