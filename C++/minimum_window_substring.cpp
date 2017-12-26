#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

string minWindow(string S, string T) {
        if (S.size() < T.size()) {
            return "";
        }
        
        unordered_map<char, int> needed;
        needed.clear();
        for (int i = 0; i != T.size(); i++) {
            if (needed.find(T.at(i)) == needed.end()) {
				pair<char, int> fuck(T.at(i), 1);
                needed.insert(fuck);
            }
            else {
                needed.at(T.at(i)) += 1;
            }
        }
        
        int window = S.size() + 1;
        int wBegin = 0;
        int wEnd = 0;
        int count = 0;
        char c;
        unordered_map<char, int> found;
        found.clear();
        for (int begin = 0, end = 0; end != S.size(); end++) {
            c = S.at(end);
            if (needed.find(c) != needed.end()) {
                if (found.find(c) == found.end()) {
					pair<char, int> fuck1(c, 1);
                    found.insert(fuck1);
                }
                else {
                    found.at(c) += 1;
                }
                
                if (found.at(c) <= needed.at(c)) {
                    count++;
                }
                
                if (count == T.size()) {
                    while (needed.find(S.at(begin)) == needed.end() ||
                           found.at(S.at(begin)) > needed.at(S.at(begin))) {
                        if (found.at(S.at(begin)) > needed.at(S.at(begin))) {
                            found.at(S.at(begin)) -= 1;
                        }
                        begin++;
                    }
                    
                    int length = end - begin + 1;
                    if (length < window) {
                        window = length;
                        wBegin = begin;
                        wEnd = end;
                    }
                }
            }
        }
        
        if (window > S.size()) {
            return "";
        }
        else {
            return S.substr(wBegin, window);
        }
    }

int main() {
	string s = "ab";
	string t = "b";
	minWindow(s, t);
	return 0;
}