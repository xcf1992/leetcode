/*
 A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).
 
 Find all strobogrammatic numbers that are of length = n.
 
 For example,
 Given n = 2, return ["11","69","88","96"].
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
using namespace std;

class Solution {
private:
    vector<char> digit{'0', '1', '6', '8', '9'};
    unordered_map<char, char> strobogrammatic{{'9', '6'}, {'1', '1'}, {'8', '8'}, {'6', '9'}, {'0', '0'}};
    
    void dfs(int n, int pos, vector<string> &result, string &temp) {
        if (n % 2 == 1) {
            if (pos > n / 2) {
                result.push_back(temp);
                return;
            }
        }
        else {
            if (pos > n / 2 - 1) {
                result.push_back(temp);
                return;
            }
        }
        
        for (char c : digit) {
            if (pos == 0 && c == '0') {
                continue;
            }
            if (n % 2 == 1 && pos == n / 2 && (c == '6' || c == '9')) {
                continue;
            }
            
            temp[pos] = c;
            temp[n - pos - 1] = strobogrammatic[c];
            dfs(n, pos + 1, result, temp);
        }
    }
public:
    vector<string> findStrobogrammatic(int n) {
        if (n == 1) {
            return vector<string>({"0","1","8"});
        }
        vector<string> result;
        string temp(n, ' ');
        dfs(n, 0, result, temp);
        return result;
    }
};
