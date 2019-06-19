#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <unordered_set>
using namespace std;

void generatePath(unordered_map<string, vector<string>> &prevMap, vector<string>& path,
                      const string& word, vector<vector<string>> &results) {
        if (prevMap[word].size() == 0) {
            path.push_back(word);
            vector<string> curPath = path;
            reverse(curPath.begin(), curPath.end());
            results.push_back(curPath);
            path.pop_back();
            return;
        }
        
        path.push_back(word);
        for (int i = 0; i != prevMap[word].size(); i++) {
            generatePath(prevMap, path, prevMap[word][i], results);
        }
        path.pop_back();
        return;
    }

vector<vector<string>> findLadders(string start, string end, unordered_set<string> &dict) {
        vector<vector<string>> results;
        results.clear();
        unordered_map<string, vector<string>> prevMap;
        prevMap.clear();
        
        for (unordered_set<string>::iterator it = dict.begin(); it != dict.end(); it++) {
            prevMap[*it] = vector<string>();
        }
        
        vector<unordered_set<string>> candidates(2);
        int current = 0;
        int previous = 1;
        candidates[current].insert(start);
        
        while (true) {
            current = 1 - current;
            previous = 1 - previous;
            
            for (unordered_set<string>::iterator it = candidates[previous].begin(); 
                 it != candidates[previous].end(); it++) {
                dict.erase(*it);
            }
            candidates[current].clear();
            
            for (unordered_set<string>::iterator it = candidates[previous].begin();
                 it != candidates[previous].end(); it++) {
                string word = *it;
                for (int i = 0; i != word.size(); i++) {
					word = *it;
                    for (char c = 'a'; c <= 'z'; c++) {
                        if (word[i] != c) {
                            word[i] = c;
                            if (dict.find(word) != dict.end()) {
                                prevMap[word].push_back(*it);
                                candidates[current].insert(word);
                            }
                        }
                    }
                }
            }
            if (candidates[current].empty()) {
                return results;
            }
            if (candidates[current].find(end) != candidates[current].end()) {
                break;
            }
        }
        vector<string> path;
        generatePath(prevMap, path, end, results);
        return results;
    }

int main() {
	string start = "hot";
	string end = "dog";
	unordered_set<string> dict;
	dict.insert("hot");
	dict.insert("dot");
	dict.insert("dog");
	findLadders(start, end, dict);
	return 0;
}