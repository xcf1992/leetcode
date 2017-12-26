#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

vector<int> findSubstring(string S, vector<string> &L) {
        int length = L.size() * L.front().size();
        vector<int> result;
        result.clear();
        if (length > S.size()) {
            return result;
        }
        
        unordered_map<string, int> needed;
        needed.clear();
        unordered_map<string, int> found;
        found.clear();
        for (int i = 0; i != L.size(); i++) {
            if (needed.find(L.at(i)) == needed.end()) {
				pair<string, int> fuck(L.at(i), 1);
                needed.insert(fuck);
            }
            else {
                needed.at(L.at(i)) += 1;
            }
        }
        
        int word = L.front().size();
        int words = L.size();
        for (int i = 0; i + length <= S.size(); i++) {
            int count = 0;
            
            for (int j = 0; j != words; j++) {
                string oneWord = S.substr(i + j * word, word);
                if (needed.find(oneWord) == needed.end()) {
                    break;
                }
                else {
                    if (found.find(oneWord) == found.end()) {
						pair<string, int> fuck1(oneWord, 1);
                        found.insert(fuck1);
                    }
                    else {
                        found.at(oneWord) += 1;
                    }
                    if (found.at(oneWord) <= needed.at(oneWord)) {
                        count++;;
                    }
                    else {
                        break;
                    }
                }
            }
            
            if (count == words) {
                result.push_back(i);
            }
        }
        
        return result;
    }

int main() {
	string S = "barfoothefoobarman";
	vector<string> L;
	L.push_back("foo");
	L.push_back("bar");
	findSubstring(S, L);
	return 0;
}