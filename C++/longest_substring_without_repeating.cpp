#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

int lengthOfLongestSubstring(string s) {
        if (s.size() == 0 || s.size() == 1) {
            return s.size();
        }
        
        unordered_map<char, int> map;
        int longest = 0;
        int start = 0;
        int i = 0;
        for (i = 0; i < s.size(); i++) {
            char c = s.at(i);
            if (map.find(s.at(i)) == map.end()) {
                pair<char, int> fuck (s.at(i), i);
                map.insert(fuck);
                continue;
            }

            if (map.at(s.at(i)) < start) {
                map.at(s.at(i)) = i;
            }
            else {
                if (i - start > longest) {
                    longest = i - start;
                }
                start = map.at(s.at(i)) + 1;
                map.at(s.at(i)) = i;
            }
        }
        
        if (i - start> longest) {
            return i - start;
        }
        return longest;
    }

int main() {
    string s = "wlrbbmqbhcdarzowkkyhiddqscdxrjmowfrxsjybldbefsarcbynecdyggxxpklorellnmpapqfwkhopkmco";
    lengthOfLongestSubstring(s);
    return 0;
}