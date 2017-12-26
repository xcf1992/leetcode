#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

string getPermutation(int n, int k) {
        vector<int> pos;
        int total = 1;
        for (int i = 0; i != n; i++) {
            pos.push_back(i + 1);
            total *= i + 1;
        }
        
        string result;
        result.clear();
        
        for (int i = 0; i != n; i++) {
            total = total / (n;
            int time = ((k - 1) / total) + 1;
            int digit;
            int j = 0;
            int x = 0;
            while (x < n) {
                if (pos.at(x) != 0) {
                    j++;
                    if (j == time) {
                        digit = pos.at(x);
                        pos.at(x) = 0;
                        x = n;
                    }
                }
                x++;
            }
            result += '0' + digit;
            k -= (time - 1) * total;
        }
        
        return result;
    }

int main() {
	getPermutation(2, 1);
}