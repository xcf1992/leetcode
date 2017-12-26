#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    int calculateMinimumHP(vector<vector<int> > &dungeon) {
        if (dungeon.empty()) {
            return 0;
        }
        
        int m = dungeon.size();
        int n = dungeon[0].size();
        vector<int> row(n, 0);
        vector<vector<int>> dp(m, row);
        int result = dungeon[0][0];
		vector<int> direction;
		int i = 0;
		int j = 0;
        for (i = 0; i < m; i++) {
            for (j = 0; j < n; j++) {
                if (i == 0 && j == 0) {
                    dp[i][j] = dungeon[i][j];
                }
                else if (i == 0) {
                    dp[i][j] = dp[i][j - 1] + dungeon[i][j];
                }
                else if (j == 0) {
                    dp[i][j] = dp[i - 1][j] + dungeon[i][j];
                }
                else {
					dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + dungeon[i][j];
                }
            }
        }
        
		i = 0;
		j = 0;
		int cur = 0;
		result = dp[0][0];
		while (i < m - 1 && j < n - 1) {
            if (i == m - 1) {
                j++;
            }
            else if (j == n - 1) {
                i++;
            }
            else {
				if (dp[i + 1][j] > dp[i][j + 1]) {
					i++;
				}
				else {
					j++;
				}
            }

			cur = dp[i][j];
			result = min(result, cur);
		}
        if (result < 0) {
            return 0 - result + 1;
        }
        return 1;
    }
};

int main() {
	Solution s;
	vector<vector<int>> dungeon;
	vector<int> row;
	row.push_back(0);
	row.push_back(-3);
	dungeon.push_back(row);
	//row[0] = 1;
	//row[1] = -1;
	//dungeon.push_back(row);
	s.calculateMinimumHP(dungeon);
	return 0;
}