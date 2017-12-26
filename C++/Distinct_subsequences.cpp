#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

int numDistinct(string S, string T) {
        if (S.empty() || T.empty() || S.size() < T.size()) {
            return 0;
        }

        vector<int> row(T.size() + 1, 0);
        vector<vector<int>> dp(S.size() + 1, row);

        for (int i = 0; i <= S.size(); i++) {
            dp.at(i).at(0) = 1;
        }

        for (int i = 1; i <= S.size(); i++) {
            for (int j = 1; j <= T.size(); j++) {
                dp.at(i).at(j) = dp.at(i - 1).at(j);  
                
				if (S.at(i-1) == T.at(j-1)) {
                    dp.at(i).at(j) += dp.at(i - 1).at(j - 1);  
                }
            }
        }
        return dp.back().back();
    }

int main() {
	string s = "rabbbit";
	string t = "rabbit";
	numDistinct(s, t);
	return 0;
}