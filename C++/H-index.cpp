/*
 Given a string S, check if the letters can be rearranged so that two characters that are adjacent to each other are not the same.
 
 If possible, output any possible result.  If not possible, return the empty string.
 
 Example 1:
 
 Input: S = "aab"
 Output: "aba"
 Example 2:
 
 Input: S = "aaab"
 Output: ""
 Note:
 
 S will consist of lowercase letters and have length in range [1, 500].
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
public:
    int hIndex(vector<int>& citations) {
        int paper = citations.size();
        vector<int> bucket(paper + 1, 0);
        for (int citation : citations) {
            if (citation >= paper) {
                bucket[paper] += 1;
            }
            else {
                bucket[citation] += 1;
            }
        }
        
        int count = 0;
        for (int i = paper; i >= 0; i--) {
            count += bucket[i];
            if (count >= i) {
                return i;
            }
        }
        return 0;
    }
};
