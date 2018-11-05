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
    int count(vector<int>& digit, string num, int pos) {
        if (pos >= num.size()) {
            return 0;
        }
        
        int result = 0;
        int less = 0;
        for (int i = 0; i < digit.size(); i++) {
            if (digit[i] < (num[pos] - '0')) {
                less += 1;
            }
            else if (digit[i] == (num[pos] - '0')) {
                result += count(digit, num, pos + 1);
            }
            else {
                break;
            }
        }
        result += less * pow(digit.size(), num.size() - pos - 1);
        return result;
    }
public:
    int atMostNGivenDigitSet(vector<string> D, int N) {
        int length = 0;
        int temp = N;
        while (temp != 0) {
            length += 1;
            temp /= 10;
        }
        
        int result = 0;
        int n = D.size();
        for (int i = 1; i < length; i++) {
            result += n;
            n *= D.size();
        }
        
        string num = to_string(N);
        vector<int> digit;
        for (string d : D) {
            digit.push_back(stoi(d));
        }
        return result + count(digit, num, 0);
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
    
    s.atMostNGivenDigitSet({"3", "4", "9"}, 4);
    return 0;
}
