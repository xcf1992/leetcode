/*
 Implement function ToLowerCase() that has a string parameter str, and returns the same string in lowercase.
*/

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
#include <set>
using namespace std;

class Solution {
public:
    string toLowerCase(string str) {
        for (int i = 0; i < str.size(); i++) {
            if (str[i] >= 'A' and str[i] <= 'Z') {
                str[i] = 'a' + (str[i] - 'A');
            }
        }
        return str;
    }
};