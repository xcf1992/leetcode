#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <unordered_set>
using namespace std;

class Solution {
public:
    vector<vector<bool>> dp;
    vector<string> results;
    vector<string> words;
    
    vector<string> wordBreak(string s, unordered_set<string> &dict) {
        if (dict.empty()) {
            return results;
        }
        
        vector<bool> row(s.size(), false);
		dp.resize(s.size(), row);
        for (int i = 0; i < s.size(); i++) {
            for (int j = i; j < s.size(); j++) {
                string word = s.substr(i, j - i + 1);
                if (dict.find(word) != dict.end()) {
                    dp[i][j] = true;
                }
            }
        }
        
        output(0, s);
        
        return results;
    }
    
    void output(int start, string s) {
        if (start >= s.size()) {
            string word;
            
            word += words[0];
            for (int i = 1; i < words.size(); i++) {
                word += ' ';
                word += words[i];
            }
            
            results.push_back(word);
            return;
        }
        
        for (int i = 0; i + start < s.size(); i++) {
            if (dp[start][start + i]) {
                string oneWord = s.substr(start, i + 1);
                words.push_back(oneWord);
                output(start + i + 1, s);
                words.pop_back();
            }
        }
        
        return;
    }
};

int main() {
	string s = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab";
	unordered_set<string> dict;
	dict.insert("a");
	dict.insert("aa");
	dict.insert("aaa");
	dict.insert("aaaa");
	dict.insert("aaaaa");
	dict.insert("aaaaaa");
	dict.insert("aaaaaaa");
	dict.insert("aaaaaaaa");
	dict.insert("aaaaaaaaa");
	dict.insert("aaaaaaaaaa");
	Solution so;
	so.wordBreak(s, dict);
	return 0;
}