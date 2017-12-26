#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

 void getResults(vector<int> &candidates, int target, int sum,
                    vector<vector<int>> &results, vector<int> &result,
                    int level, vector<bool> &pickUp) {
        if (sum > target ||
            level >= candidates.size() ||
            target < sum + candidates.at(level)) {
            return;
        }
        
        if ((target - sum) == candidates.at(level)) {
            result.push_back(candidates.at(level));
            results.push_back(result);
            result.pop_back();
        }
        getResults(candidates, target, sum, results, result, level + 1, pickUp);
        
        if (level > 0 && candidates.at(level) == candidates.at(level - 1) && 
            pickUp.at(level - 1)) {
            result.push_back(candidates.at(level));
            pickUp.at(level) = true;
            sum += candidates.at(level);
        }
        if (level == 0) {
            result.push_back(candidates.at(level));
            pickUp.at(level) = true;
            sum += candidates.at(level);
        }

        if (level >= candidates.size() - 1 || 
            target < sum + candidates.at(level + 1)) {
			if (pickUp.at(level)) {
				result.pop_back();
				pickUp.at(level) = false;
			}
            return;
        }
		if (pickUp.at(level)) {
			getResults(candidates, target, sum, results, result, level + 1, pickUp);
			result.pop_back();
			pickUp.at(level) = false;
		}
        
        return;
    }

vector<vector<int> > combinationSum2(vector<int> &num, int target) {
        vector<vector<int>> results;
        results.clear();
        vector<int> result;
        result.clear();
        
        if (target == 0 || num.empty()) {
            return results;
        }
        
        sort(num.begin(), num.end());
        
        int sum = 0;
        vector<bool> pickUp(num.size(), false);
        getResults(num, target, sum, results, result, 0, pickUp);
        
        return results;
    }
    
    
int main() {
	vector<int> num;
	num.push_back(1);
	num.push_back(2);
	num.push_back(5);
	num.push_back(2);
	num.push_back(2);
	vector<vector<int>> results = combinationSum2(num, 5);
	return 0;
}