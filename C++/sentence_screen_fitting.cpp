/*
 418. Sentence Screen Fitting
 Given a rows x cols screen and a sentence represented by a list of non-empty words,
 find how many times the given sentence can be fitted on the screen.

 Note:

 A word cannot be split into two lines.
 The order of words in the sentence must remain unchanged.
 Two consecutive words in a line must be separated by a single space.
 Total words in the sentence won't exceed 100.
 Length of each word is greater than 0 and won't exceed 10.
 1 ≤ rows, cols ≤ 20,000.
 Example 1:

 Input:
 rows = 2, cols = 8, sentence = ["hello", "world"]

 Output:
 1

 Explanation:
 hello---
 world---

 The character '-' signifies an empty space on the screen.
 Example 2:

 Input:
 rows = 3, cols = 6, sentence = ["a", "bcd", "e"]

 Output:
 2

 Explanation:
 a-bcd-
 e-a---
 bcd-e-

 The character '-' signifies an empty space on the screen.
 Example 3:

 Input:
 rows = 4, cols = 5, sentence = ["I", "had", "apple", "pie"]

 Output:
 1

 Explanation:
 I-had
 apple
 pie-I
 had--

 The character '-' signifies an empty space on the screen.
 */
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
#include <set>
#include <numeric>
using namespace std;

/*
 I use num to represent how many words can be put in the screen.
 we use a map count to record for each line how many words cnt can be put when starting with word i.
 So when we scan each line of the screen, we first get the starting word should be put on this line.
 If this starting words is already in the map, then just read it; otherwise, create a new entry in this map.
 */
class Solution {
public:
    int wordsTyping(vector<string>& sentence, int rows, int cols) {
        unordered_map<int, int> count;
        int n = sentence.size();
        int num = 0;
        for (int i = 0; i < rows; i++) {
            int cur = num % n;
            if (count.find(cur) == count.end()) {
                int length = 0;
                int word = cur;
                while (length + sentence[word].size() <= cols) {
                    length += sentence[word].size() + 1;
                    count[cur] += 1;
                    word = (word + 1) % n;
                }
            }
            num += count[cur];
        }
        return num / n;
    }
};

// time limit exceed
class Solution1 {
public:
    int wordsTyping(vector<string>& sentence, int rows, int cols) {
        int result = 0;
        int i = 0;
        int j = 0;
        int cur = 0;
        while (i < rows) {
            if (j + sentence[cur].size() - 1 < cols) {
                j += sentence[cur].size() + 1;
                if (j >= cols) {
                    j = 0;
                    i += 1;
                }
                if (cur == sentence.size() - 1) {
                    result += 1;
                }
                cur = (cur + 1) % sentence.size();
            }
            else {
                i += 1;
                j = 0;
            }
        }
        return result;
    }
};
