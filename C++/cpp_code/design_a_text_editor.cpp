/*
https://leetcode.com/problems/design-a-text-editor/description/
2296. Design a Text Editor

Design a text editor with a cursor that can do the following:

Add text to where the cursor is.
Delete text from where the cursor is (simulating the backspace key).
Move the cursor either left or right.
When deleting text, only characters to the left of the cursor will be deleted. The cursor will also remain within the
actual text and cannot be moved beyond it. More formally, we have that 0 <= cursor.position <= currentText.length always
holds.

Implement the TextEditor class:

TextEditor() Initializes the object with empty text.
void addText(string text) Appends text to where the cursor is. The cursor ends to the right of text.
int deleteText(int k) Deletes k characters to the left of the cursor. Returns the number of characters actually deleted.
string cursorLeft(int k) Moves the cursor to the left k times. Returns the last min(10, len) characters to the left of
the cursor, where len is the number of characters to the left of the cursor. string cursorRight(int k) Moves the cursor
to the right k times. Returns the last min(10, len) characters to the left of the cursor, where len is the number of
characters to the left of the cursor.


Example 1:

Input
["TextEditor", "addText", "deleteText", "addText", "cursorRight", "cursorLeft", "deleteText", "cursorLeft",
"cursorRight"]
[[], ["leetcode"], [4], ["practice"], [3], [8], [10], [2], [6]]
Output
[null, null, 4, null, "etpractice", "leet", 4, "", "practi"]

Explanation
TextEditor textEditor = new TextEditor(); // The current text is "|". (The '|' character represents the cursor)
textEditor.addText("leetcode"); // The current text is "leetcode|".
textEditor.deleteText(4); // return 4
                          // The current text is "leet|".
                          // 4 characters were deleted.
textEditor.addText("practice"); // The current text is "leetpractice|".
textEditor.cursorRight(3); // return "etpractice"
                           // The current text is "leetpractice|".
                           // The cursor cannot be moved beyond the actual text and thus did not move.
                           // "etpractice" is the last 10 characters to the left of the cursor.
textEditor.cursorLeft(8); // return "leet"
                          // The current text is "leet|practice".
                          // "leet" is the last min(10, 4) = 4 characters to the left of the cursor.
textEditor.deleteText(10); // return 4
                           // The current text is "|practice".
                           // Only 4 characters were deleted.
textEditor.cursorLeft(2); // return ""
                          // The current text is "|practice".
                          // The cursor cannot be moved beyond the actual text and thus did not move.
                          // "" is the last min(10, 0) = 0 characters to the left of the cursor.
textEditor.cursorRight(6); // return "practi"
                           // The current text is "practi|ce".
                           // "practi" is the last min(10, 6) = 6 characters to the left of the cursor.


Constraints:

1 <= text.length, k <= 40
text consists of lowercase English letters.
At most 2 * 104 calls in total will be made to addText, deleteText, cursorLeft and cursorRight.


Follow-up: Could you find a solution with time complexity of O(k) per call?
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <deque>
#include <climits>
using namespace std;

class TextEditor {
private:
    deque<char> prefix;
    deque<char> suffix;
public:
    TextEditor() {
    }

    void addText(string text) {
        for (char c : text) {
            prefix.push_back(c);
        }
    }

    int deleteText(int k) {
        int n = prefix.size();
        int cnt = min(n, k);
        for (int i = 0; i < cnt; i++) {
            prefix.pop_back();
        }
        return cnt;
    }

    string cursorLeft(int k) {
        int n = prefix.size();
        int cnt = min(n, k);
        for (int i = 0; i < cnt; i++) {
            char c = prefix.back();
            prefix.pop_back();
            suffix.push_front(c);
        }
        return get_current_text();
    }

    string cursorRight(int k) {
        int n = suffix.size();
        int cnt = min(n, k);
        for (int i = 0; i < cnt; i++) {
            char c = suffix.front();
            suffix.pop_front();
            prefix.push_back(c);
        }
        return get_current_text();
    }
private:
    string get_current_text() {
        size_t n = prefix.size();
        size_t len = min((size_t)10, n);
        string rst(len, ' ');
        int prefix_idx = n - 1;
        int rst_idx = len - 1;
        for (int i = 0; i < len; i++) {
            rst[rst_idx] = prefix[prefix_idx];
            rst_idx -= 1;
            prefix_idx -= 1;
        }
        return rst;
    }
};

/**
 * Your TextEditor object will be instantiated and called as such:
 * TextEditor* obj = new TextEditor();
 * obj->addText(text);
 * int param_2 = obj->deleteText(k);
 * string param_3 = obj->cursorLeft(k);
 * string param_4 = obj->cursorRight(k);
 */