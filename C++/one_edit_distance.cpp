#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue>
using namespace std;

class Solution {
public:
    bool isOneEditDistance(string s, string t) {
		int m = s.size();
		int n = t.size();
        if (s.empty()) {
            if (t.size() == 1) {
                return true;
            }
            return false;
        }
        if (t.empty()) {
            if (s.size() == 1) {
                return true;
            }
            return false;
        }
		if (m - n > 1 || n - m > 1) {
            return false;
        }
        
        bool first = true;
        if (s.size() == t.size()) {
            for (int i = 0; i < s.size(); i++) {
                if (s[i] != t[i]) {
                    if (first) {
                        first = false;
                    }
                    else {
                        return false;
                    }
                }
            }
            if (!first) {
                return true;
            }
            return false;
        }
        
        if (s.size() < t.size()) {
            string temp = s;
            s = t;
            t = temp;
        }
        
        int i = 0;
        int j = 0;
        while (i < s.size() && j < t.size()) {
            if (s[i] == t[j]) {
                i++;
                j++;
            }
            else {
                i++;
            }
        }
        
        if (j == t.size()) {
            return true;
        }
        return false;
    }
};

int main() {
	Solution s;
	string a = "a";
	string b = "ba";
	s.isOneEditDistance(a, b);
	return 0;
}