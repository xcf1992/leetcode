#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

bool noSwap(vector<int> &num, int start, int end) {
        for (int i = start; i != end; i++) {
            if (num.at(i) == num.at(end)) {
                return true;
            }
        }
        
        return false;
    }

void generate(vector <vector <int>> &results, vector <int> &num, int level) {
        if ( level == num.size()) {
            results.push_back(num);
            return;
        }
        else {
            for ( int i = level; i != num.size(); i++) {
                if (!noSwap(num, level, i)) {
                    swap(num.at(i), num.at(level));
                    generate(results, num, level + 1);
                    swap(num.at(i), num.at(level));
                }
            }
        }
        return;
    }

vector<vector<int> > permuteUnique(vector<int> &num) {
        sort(num.begin(), num.end());
        vector <vector <int>> results;
        results.clear();
        generate(results, num, 0);
        return results;
    }

int main() {
	vector<int> num;
	num.push_back(1);
	num.push_back(2);
	num.push_back(1);
	num.push_back(2);
	vector<vector<int>> results = permuteUnique(num);
	return 0;
}