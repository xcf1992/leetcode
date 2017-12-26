#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstringTwoDistinct(string s) {
        if (s.size() <= 2) {
            return s.size();
        }
        
        int result = 0;
        int begin = 0;
        int end = 1;
        int distinct = 1;
        unordered_map<char, int> dict;
        dict[s[begin]] = 1;
        while (end < s.size()) {
            if (dict.find(s[end]) != dict.end()) {
                dict[s[end]]++;
                end++;
            }
            else if (distinct == 1) {
                dict[s[end]] = 1;
                end++;
                distinct++;
            }
            else if (distinct == 2) {
                result = max(result, end - begin);
                while (begin < end && distinct == 2) {
                    dict[s[begin]]--;
                    
                    if (dict[s[begin]] == 0) {
                        distinct = 1;
                        dict.erase(s[begin]);
                    }
                    
                    begin++;
                }
            }
        }
        
        return max(result, end - begin);
    }
};

int main() {
	Solution s;
	string ss = "abcc";
	return s.lengthOfLongestSubstringTwoDistinct(ss);
	return 0;
}