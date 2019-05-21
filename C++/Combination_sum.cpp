#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
    private:
    void check(vector<int>& candidates, int target, int start, vector<int> combination, vector<vector<int>>& result) {
        if (target == 0) {
            result.push_back(combination);
            return;
        }
        
        for (int i = start; i < candidates.size(); ++i) {
            if (target < candidates[i]) {
                return;
            }
            combination.push_back(candidates[i]);
            check(candidates, target - candidates[i], i, combination, result);
            combination.pop_back();
        }
    }
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<vector<int>> result;
        check(candidates, target, 0, {}, result);
        return result;
    }
};

void getResults(vector<int> &candidates, int target, int sum,
                    vector<vector<int>> &results, vector<int> &result, int level) {
        if (sum > target ||
            level >= candidates.size() ||
            target < sum + candidates.at(level)) {
            return;
        }
        
        if ((target - sum) % candidates.at(level) == 0) {
            int times = (target - sum) / candidates.at(level);
            for (int i = 0; i != times; i++) {
                result.push_back(candidates.at(level));
            }
            results.push_back(result);
            for (int i = 0; i != times; i++) {
                result.pop_back();
            }
        }
        
        getResults(candidates, target, sum, results, result, level + 1);
        int i = 0;
        while (i < (target - sum) / candidates.at(level) - 1) {
            result.push_back(candidates.at(level));
            i++;
            sum += candidates.at(level);
            
            if (level >= candidates.size() - 1 || target < sum + candidates.at(level + 1)) {
                break;
            }
            getResults(candidates, target, sum, results, result, level + 1);
        }
        for (; i > 0; i--) {
            result.pop_back();
        }
        return;
    }

vector<vector<int> > combinationSum(vector<int> &candidates, int target) {
        vector<vector<int>> results;
        results.clear();
        vector<int> result;
        result.clear();
        
        if (target == 0 || candidates.empty()) {
            return results;
        }
        
        sort(candidates.begin(), candidates.end());
        
        int sum = 0;
        getResults(candidates, target, sum, results, result, 0);
        
        return results;
    }
    
    

    

int main() {
	vector<int> num;
	num.push_back(3);
	num.push_back(2);
	num.push_back(5);
	combinationSum(num, 7);
	return 0;
}