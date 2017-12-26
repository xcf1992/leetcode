#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    bool isIsomorphic(string s, string t) {
        if (s == t) {
            return true;
        }
        if (s.size() != t.size()) {
            return false;
        }
        
        unordered_map<char, char> iso;
        for (int i = 0; i < s.size(); i++) {
            if (iso.find(s[i]) == iso.end()) {
                iso[s[i]] = t[i];
            }
            else {
                if (iso[s[i]] != t[i]) {
                    return false;
                }
            }
        }
        
        return true;
    }
};

int main() {
	Solution s;
	s.isIsomorphic("aa", "ab");
	return 0;
}