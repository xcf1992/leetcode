#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    bool isMatch(const char *s, const char *p) {
        if (s == nullptr) {
            if (p == nullptr) {
                return true;
            }
            return false;
        }

        if (*s == '\0') {
            if (*p == '\0') {
                return true;
            }
            if (*p == '*') {
                while (*p == '*' && *(p + 1) == '*') {
                    p++;
                }
                if (*(p + 1) == '\0') {
                    return true;
                }
            }
            return false;
        }

        const char *sPos = s;
        const char *pPos = nullptr;
        while (*s != '\0') {
            if (*p == *s || *p == '?') {
                s++;
                p++;
            }
            else if (*p == '*') {
                sPos = s;
				p++;
                pPos = p;
            }
            else if (pPos != nullptr) {
                s = sPos;
                p = pPos + 1;
                sPos++;
            }
            else {
                return false;
            }
        }

        while (*p == '*') {
            p++;
        }
        if (*p == '\0') {
            return true;
        }
        return false;
    }
};

int main() {
	Solution s;
	char* s1 = "aa";
	char* s2 = "a*";
	s.isMatch(s1, s2);
	return 0;
}