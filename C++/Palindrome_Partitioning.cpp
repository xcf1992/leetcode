#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

/*void dfs(vector<vector<string>> &results, vector<string> result, string s, int depth,
             vector<vector<bool>> &matrix) {
        if (depth >= s.size()) {
            results.push_back(result);
            return;
        }
        
        for (int i = 0; i != s.size(); i++) {
            if (depth + i < s.size()) {
                if (matrix.at(depth).at(depth + i)) {
                    result.push_back(s.substr(depth, i + 1));
                    dfs(results, result, s, depth + i + 1, matrix);
					result.pop_back();
                }
            }
        }
    }

vector<vector<string>> partition(string s) {
        vector<vector<string>> results;
        results.clear();
        vector<string> result;
        result.clear();
		int n = s.size();
        
        if (s.size() == 0) {
            return results;
        }
        if (s.size() == 1) {
            result.push_back(s);
            results.push_back(result);
            return results;
        }
        
        vector<bool> row(n, false);
        vector<vector<bool>> matrix(n, row);
        for (int i = 0; i != n - 1; i++) {
            matrix.at(i).at(i) = true;
            if (s.at(i) == s.at(i + 1)) {
                matrix.at(i).at(i + 1) = true;
            }
        }
        matrix.back().back() = true;
        for (int j = 2; j != n; j++) {
            for (int i = 0; i != n; i++) {
                if (i + j <= n - 1) {
                    if (s.at(i) == s.at(i + j) && matrix.at(i + 1).at(i + j - 1)) {
                        matrix.at(i).at(i + j) = true;
                    }
                }
            }
        }
        
        dfs(results, result, s, 0, matrix);
        return results;
    }*/
int minCut(string s) {
		if (s.size() == 0 || s.size() == 1) {
            return 0;
        }
        
        vector<bool> row(s.size(), false);
        vector<vector<bool>> matrix(s.size(), row);
        for (int i = 0; i != s.size() - 1; i++) {
            matrix.at(i).at(i) = true;
            if (s.at(i) == s.at(i + 1)) {
                matrix.at(i).at(i + 1) = true;
            }
        }
        matrix.back().back() = true;
        for (int j = 2; j != s.size(); j++) {
            for (int i = 0; i != s.size(); i++) {
                if (i + j < s.size()) {
                    if (s.at(i) == s.at(i + j) && matrix.at(i + 1).at(i + j - 1)) {
                        matrix.at(i).at(i + j) = true;
                    }
                }
            }
        }
        
        if (matrix.at(0).back()) {
            return 0;
        }
        
        vector<int> cutNum(s.size());
        for (int i = 0; i != cutNum.size(); i++) {
            cutNum.at(i) = s.size() - i - 1;    
        }
        
        for (int i = cutNum.size() - 2; i >= 0; i--) {
            if (matrix.at(i).back()) {
                cutNum.at(i) = 0;
            }
            else {
                int min = cutNum.at(i);
                for (int j = i + 1; j < s.size(); j++) {
                    if (matrix.at(i).at(j - 1)) {
                        if (min > cutNum.at(j) + 1) {
                            min = cutNum.at(j) + 1;
                        }
                    }
                    else {
                        if (min > cutNum.at(j) + j - i) {
                            min = cutNum.at(j) + j - i;
                        }
                    }
                }
            }
        }
        
        return cutNum.at(0);
    }
int main() {
	string s = "abb";
	minCut(s);
	return 0;
}
