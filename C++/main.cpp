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
    bool isEqual(vector<int>& A, int s1, int e1, int s2, int e2, int s3, int e3) {
        int num1 = getNum(A, s1, e1);
        int num2 = getNum(A, s2, e2);
        int num3 = getNum(A, s3, e3);
        return num1 == num2 and num1 == num3;
    }
    
    int getNum(vector<int>& A, int start, int end) {
        int num = 0;
        for (int i = start; i <= end; i++) {
            num = num * 2 + A[i];
        }
        return num;
    }
public:
    vector<int> threeEqualParts(vector<int> A) {
        int total = 0;
        for (int a : A) {
            total += a;
        }
        
        if (total % 3 != 0) {
            return {-1, -1};
        }
        int n = A.size();
        int ones = total / 3;
        if (ones == 0) {
            return {0, n - 1};
        }
        
        int count = 0;
        int s1 = -1, e1 = -1, s2 = -1, e2 = -1, s3 = -1, e3 = -1;
        for (int i = 0; i < n; i++) {
            if (A[i] == 1) {
                count += 1;
                
                if (count == 1) {
                    s1 = i;
                }
                if (count == ones) {
                    e1 = i;
                }
                if (count == ones + 1) {
                    s2 = i;
                }
                if (count == 2 * ones) {
                    e2 = i;
                }
                if (count == 2 * ones + 1) {
                    s3 = i;
                }
                if (count == 3 * ones) {
                    e3 = i;
                }
            }
        }
        
        if (!isEqual(A, s1, e1, s2, e2, s3, e3)) {
            return {-1, -1};
        }
        
        int gap1 = s2 - e1 - 1;
        int gap2 = s3 - e2 - 1;
        int gap3 = n - e3 - 1;
        if (gap1 < gap3 or gap2 < gap3) {
            return {-1, -1};
        }
        return {e1 + gap3, e2 + gap3 - 1};
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
    
    s.threeEqualParts({1,0,1,0,1});
    return 0;
}
