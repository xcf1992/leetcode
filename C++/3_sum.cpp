#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;


vector<vector<int> > threeSum(vector<int> &num) {
        vector<vector<int>> results;
        results.clear();
        vector<int> result;
        
        if (num.size() <= 2 ||
            (num.size() == 3 && num[0] + num[1] + num[2] != 0)) {
            return results;
        }
        
        sort(num.begin(), num.end());
        int oldVal = num.at(0);
        for (int i = 0; i != num.size(); i++) {
            result.clear();
            result.push_back(num.at(i));
            if (i > 0 && num.at(i) == oldVal) {
                continue;
            }
            else {
                oldVal = num.at(i);
            }
            int needed = 0 - num.at(i);
            
            int forward = i + 1;
            int backward = num.size() - 1;
            
            while (forward < backward) {
                if (forward > i + 1 && 
                    num.at(forward) == num.at(forward - 1)) {
                    continue;
                }
                if (backward < num.size() - 1 && 
                    num.at(backward) == num.at(backward - 1)) {
                    continue;
                }
                
                if (num.at(forward) + num.at(backward) == needed) {
                    result.push_back(num.at(forward));
                    result.push_back(num.at(backward));
                    results.push_back(result);
                    result.pop_back();
                    result.pop_back();
                    forward++;
                }
                else if (num.at(forward) + num.at(backward) < needed) {
                    forward++;
                }
                else if (num.at(forward) + num.at(backward) > needed) {
                    backward--;
                }
            }
        }
        
        return results;
    }

int main() {
	vector<int> num(4, 0);
	threeSum(num);
	return 0;
}