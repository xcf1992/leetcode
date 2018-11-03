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
    long reverseNum(long num) {
        long result = 0;
        while (num > 0) {
            result = result * 10 + num % 10;
            num /= 10;
        }
        return result;
    }
    
    bool isPalindrome(long num) {
        return num == reverseNum(num);
    }
    
    int MAGIC = 1e5;
    
public:
    int superpalindromesInRange(string L, string R) {
        long left = stol(L);
        long right = stol(R);
        int result = 0;
        
        for (int i = 1; i < MAGIC; i++) {
            string numStr = to_string(i);
            string reverseNum = numStr;
            reverse(reverseNum.begin(), reverseNum.end());
            string numStr2 = numStr + reverseNum;
            numStr += reverseNum.substr(1);
            
            long num1 = stol(numStr);
            long num2 = stol(numStr2);
            if (num1 >= left and num1 <= right and isPalindrome(num1)) {
                result += 1;
            }
            if (num2 >= left and num2 <= right and isPalindrome(num2)) {
                result += 1;
            }
            if (num1 > right and num2 > right) {
                break;
            }
        }
        return result;
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
    
    s.superpalindromesInRange("4", "1000");
    return 0;
}
