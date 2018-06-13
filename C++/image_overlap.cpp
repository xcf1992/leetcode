/*
 Two images A and B are given, represented as binary, square matrices of the same size.  (A binary matrix has only 0s and 1s as values.)
 
 We translate one image however we choose (sliding it left, right, up, or down any number of units), and place it on top of the other image.  After, the overlap of this translation is the number of positions that have a 1 in both images.
 
 (Note also that a translation does not include any kind of rotation.)
 
 What is the largest possible overlap?
 
 Example 1:
 
 Input: A = [[1,1,0],
 [0,1,0],
 [0,1,0]]
 B = [[0,0,0],
 [0,1,1],
 [0,0,1]]
 Output: 3
 Explanation: We slide A to right by 1 unit and down by 1 unit.
 Notes:
 
 1 <= A.length = A[0].length = B.length = B[0].length <= 30
 0 <= A[i][j], B[i][j] <= 1
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
using namespace std;

class Solution {
public:
    int largestOverlap(vector<vector<int>>& A, vector<vector<int>>& B) {
        int num = A.size();
        vector<int> a;
        vector<int> b;
        
        for (int i = 0; i < num; i++) {
            for (int j = 0; j < num; j++) {
                if (A[i][j] == 1) {
                    a.push_back(i * 100 + j);
                }
                
                if (B[i][j] == 1) {
                    b.push_back(i * 100 + j);
                }
            }
        }
        
        unordered_map<int, int> count;
        for (int ait : a) {
            for (int bit : b) {
                count[ait - bit] += 1;
            }
        }
        
        int result = 0;
        for (auto& c : count) {
            result = max(result, c.second);
        }
        return result;
    }
};
