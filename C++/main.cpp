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
    string filter(string& email) {
        int i = 0;
        string result = "";
        bool findPlus = false;
        while (i < email.size()) {
            if (email[i] == '@') {
                break;
            }
            if (findPlus) {
                i = i + 1;
            }
            else {
                if (email[i] != '.') {
                    result += email[i];
                }
                i = i + 1;
            }
        }
        result += email.substr(i);
        return result;
    }
public:
    int numUniqueEmails(vector<string> emails) {
        unordered_set<string> result;
        for (string& email : emails) {
            result.insert(filter(email));
        }
        return result.size();
    }
};

int main() {
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
    s.numUniqueEmails({"test.email+alex@leetcode.com","test.e.mail+bob.cathy@leetcode.com","testemail+david@lee.tcode.com"});
    return 0;
}
