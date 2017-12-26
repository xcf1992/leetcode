#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    bool isPalindrome(string s) {
        if (s.size() <= 1) {
            return true;
        }
        
        int start = 0;
        int end = s.size() - 1;
        while (start < end) {
            if ((s[start] <= 'z' && s[start] >= 'a') || (s[start] <= 'Z' && s[start] >= 'A')) {
                if ((s[end] <= 'z' && s[end] >= 'a') || (s[end] <= 'Z' && s[end] >= 'A')) {
                    if (s[start] - 'a' == s[end] - 'a' || 
                        s[start] - 'a' == s[end] - 'A' ||
                        s[start] - 'A' == s[end] - 'A' ||
                        s[start] - 'a' == s[end] - 'a') {
                        start++;
                        end--;
                    }
                    else {
                        return false;
                    }
                }
                else {
                    end--;
                }
            }
            else {
                start++;
            }
        }
        
        return true;
    }
};

int main() {
	string s = "Bab";
	Solution so;
	so.isPalindrome(s);
	return 0;
}