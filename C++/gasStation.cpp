#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
        if (gas.size() != cost.size()) {
            return -1;
        }
        if (gas.empty()) {
            return -1;
        }
        
        vector<int> diff(gas.size());
        int total = 0;
        for (int i = 0; i != gas.size(); i++) {
            diff.at(i) = gas.at(i) - cost.at(i);
            total += diff.at(i);
        }
        if (total < 0) {
            return -1;
        }
        
        int start = 0;
        int sum = 0;
        for (int i = 0; i != diff.size(); i++) {
            sum += diff.at(i);
            if (sum < 0) {
                sum = 0;
                start = i + 1;
            }
            else {
                sum += diff.at(i);
            }
        }
        
        return start;
    }

int main() {
	vector<int> gas;
	gas.push_back(1);
	gas.push_back(2);
	gas.push_back(3);
	gas.push_back(3);
	vector<int> cost;
	cost.push_back(2);
	cost.push_back(1);
	cost.push_back(5);
	cost.push_back(1);

	int result = canCompleteCircuit(gas, cost);
	return 0;
}