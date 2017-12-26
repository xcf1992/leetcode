#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>
using namespace std;

vector<string> fullJustify(vector<string> &words, int L) {
        vector<string> result;
        result.clear();
        if (words.empty()) {
            return result;
        }
        
        
        int length = 0;
		int wordsLen = 0;
        int start = 0;
        int i = 0;
        vector<string> oneLine;
        while (start < words.size()) {
			oneLine.clear();
			length = 0;
            for (i = start; i != words.size(); i++) {
                if (length + words[i].size() > L) {
                    break;
                }
                oneLine.push_back(words[i]);
                length = length + words[i].size() + 1;
            }
            
            string line;
            line.clear();
            if (i != words.size()) {
                line += oneLine.front();
                if (oneLine.size() == 1) {
                    while (line.size() != L) {
                        line += ' ';
                    }
                }
                else {
                    int spaces = L - length + oneLine.size();
                    int temp = spaces / (oneLine.size() - 1);
					int rest = spaces % (oneLine.size() - 1);
                    for (int j = 1; j != oneLine.size(); j++) {
                        for (int k = 0; k != temp; k++) {
                            line += ' ';
                        }
						if (rest > 0) {
							line += ' ';
							rest--;
						}
                        spaces -= temp;
                        line += oneLine[j];
                    }
                }
            }
            else {
                line += oneLine[0];
                for (int j = 1; j != oneLine.size(); j++) {
                    line += ' ';
                    line += oneLine[j];
                }
                while (line.size() != L) {
                    line += ' ';
                }
            }
            
			result.push_back(line);
            start = i;
        }
        
        return result;
    }

int main() {
	vector<string> words;
	words.push_back("WAHT");
	words.push_back("must");
	words.push_back("be");
	words.push_back("shall");
	words.push_back("br.");
	//words.push_back("Text");
	//words.push_back("Justification");
	fullJustify(words, 12);
	return 0;
}