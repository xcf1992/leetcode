#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    int minimumTotal(vector<vector<int> > &triangle) {
        vector<int> result(triangle.back());
        if (triangle.size() <= 1) {
            return result.front();
        }
        
        for (int i = triangle.size() - 2; i >= 0; i++) {
            for (int j = 0; j < triangle[i].size(); j++) {
                result[j] = min(result[j], result[j + 1]) + triangle[i][j];
            }
        }
        
        return result[0];
    }
};

int main() {
	vector<vector<int> > triangle;
	vector<int> row;
	row.push_back(1);
	triangle.push_back(row);
	row.clear();
	row.push_back(2);
	row.push_back(3);
	triangle.push_back(row);
	Solution s;
	s.minimumTotal(triangle);
	return 0;
}