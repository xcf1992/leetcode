#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

void getAllResults(int &results, vector<int> &result, int level, int n) {
        if (level == n) {
            bool flag = true;
            for (int i = 0; i != n && flag; i++) {
                for (int j = i + 1; j != n; j++) {
                    if (j - i == abs(result.at(j) - result.at(i))) {
                        flag = false;
                        break;
                    }
                }
            }
            
            if (flag) {
                results++;
            }
        }
        
        for (int i = level; i != n; i++) {
            swap(result.at(level), result.at(i));
            getAllResults(results, result, level + 1, n);
            swap(result.at(level), result.at(i));
        }
        
        return;
    }

int totalNQueens(int n) {
        int results = 0;
        vector<int> result;
        result.clear();
        
        getAllResults(results, result, 0, n);
        
        return results;
    }
    
int main() {
	int num = totalNQueens(8);
	return 0;
}
    