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
public:
    int magicalString(int n) {
        string s1 = "122";
        string s2 = "12";

        while (s1.size() < n) {
            s2.push_back(s1[s2.size()]);
            if (s2.back() == '1') {
                s1 += s1.back() == '1' ? '2' : '1';
            }
            else if (s2.back() == '2') {
                s1 += s1.back() == '1' ? "22" : "11";
            }
        }

        string magicalString = s1.substr(0, n);
        return count(magicalString.begin(), magicalString.end(), '1');
    }
};