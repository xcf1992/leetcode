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
private:
    vector<string> below20 = vector<string>({"One", "Two", "Three", "Four","Five","Six","Seven","Eight","Nine","Ten", "Eleven","Twelve","Thirteen","Fourteen","Fifteen","Sixteen","Seventeen","Eighteen","Nineteen"});
    vector<string> below100 = vector<string>({"Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"});
public:
    string numberToWords(int num) {
        if (num >= 1000000000) {
            return numberToWords(num / 1000000000) + " Billion " + numberToWords(num % 1000000000);
        }
        else if (num > 1000000) {
            return numberToWords(num / 1000000) + " Million " + numberToWords(num % 1000000);
        }
        else if (num >= 1000) {
            return numberToWords(num / 1000) + " Thousand " + numberToWords(num % 1000);
        }
        else if (num >= 100) {
            return numberToWords(num / 100) + " Thousand " + numberToWords(num % 100);
        }
        else if (num >= 20) {
            return below100[num / 10 - 2] + " " + below20[num % 10];
        }
        else {
            return below20[num % 20];
        }
    }
};

int main() {
    Solution s;
    vector<string> v({"ABD","BCE","DEF","FFF"});
    vector<int> v2({2,2,2,2,2});
    vector<char> chars({'a','a','a','a','a','b','b','c'});
    vector<vector<int>> matrix({{78,16,94,36},{87,93,50,22},{63,28,91,60},{64,27,41,27},{73,37,12,69},{68,30,83,31},{63,24,68,36}});
    
    s.numberToWords(323452345);
}
