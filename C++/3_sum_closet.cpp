#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

int threeSumClosest(vector<int> &num, int target) {
        int closet;
        if (num.size() == 3) {
            return num.at(0) + num.at(1) + num.at(2);
        }
        
        sort(num.begin(), num.end());
        bool firstTime = true;
        for (int i = 0; i != num.size(); i++) {
            int forward = i + 1;
            int backward = num.size() - 1;
            
            while (forward < backward) {
                int newCloset;
                if (firstTime) {
                    closet = num.at(i) + num.at(forward) + num.at(backward);
                    newCloset = closet;
                    firstTime = false;
                    forward++;
                }
                else {
                    newCloset = num.at(i) + num.at(forward) + num.at(backward);
                    
                    if (abs(newCloset - target) < abs(closet - target)) {
                        closet = newCloset;
                    }
                }
                
                if (newCloset == target) {
                    return newCloset;
                }
                else if (newCloset < target) {
                    forward++;
                }
                else if (newCloset > target) {
                    backward--;
                }
            }
        }
        
        return closet;
    }

int main() {
	vector<int> num;
	num.push_back(-3);
	num.push_back(2);
	num.push_back(0);
	num.push_back(1);
	threeSumClosest(num, 1);
	return 0;
}