#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
#include <map>
#include <set>
#include <numeric>
#include "extra_data_types.hpp"
using namespace std;

class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        vector<vector<string>> result;
        unordered_set<string> visited;
        unordered_set<string> dict(wordList.begin(), wordList.end());
        queue<vector<string>> bfs;

        int len = 1;
        int minLen = INT_MAX;
        bfs.push({beginWord});
        visited.insert(beginWord);
        while (!bfs.empty()) {
            vector<string> ladder = bfs.front();
            bfs.pop();

            //"visited" records all the visited nodes on this level
            //these words will never be visited again after this level
            //and should be removed from wordList. This is guaranteed
            // by the shortest path.
            if (ladder.size() > len) { //reach a new level
                if (ladder.size() > minLen) {
                    break;
                }
                len = ladder.size();
            }

            string curWord = ladder.back();
            for (int i = 0; i < curWord.size(); ++i) {
                string nextWord = curWord;
                for (char c = 'a'; c <= 'z'; ++c) {
                    if (c == curWord[i]) {
                        continue;
                    }
                    nextWord[i] = c;
                    if (dict.find(nextWord) != dict.end() and visited.find(nextWord) == visited.end()) {
                        vector<string> newLadder = ladder;
                        newLadder.push_back(nextWord);
                        if (nextWord == endWord) {
                            minLen = len;
                            result.push_back(newLadder);
                        }
                        else {
                            bfs.push(newLadder);
                            visited.insert(nextWord);
                        }
                    }
                }
            }
        }
        return result;
    }
};

int main() {
    Solution s;
    vector<int> temp({6,2,4});
    vector<int> temp1({1,3,3,3,2});
    vector<vector<int>> matrix({
        {0,1},
        {1,2},
        {2,1},
        {1,0},
        {0,2},
        {0,0},
        {1,1}
    });
    vector<vector<int>> matrix2({
        {1,2,2,3,5},
        {3,2,3,4,4},
        {2,4,5,3,1},
        {6,7,1,4,5},
        {5,1,1,2,4}
    });
    vector<string> words({"hot","dot","dog","lot","log","cog"});
    TreeNode* r1 = new TreeNode(0);
    TreeNode* r2 = new TreeNode(1);
    TreeNode* r3 = new TreeNode(3);
    r1 -> left = r2;
    s.findLadders("hit", "cog", words);
}
