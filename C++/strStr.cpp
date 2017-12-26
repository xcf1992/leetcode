#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

char *strStr(char *haystack, char *needle) {
        if (haystack == nullptr) {
            return nullptr;
        }
        if (*needle == '\0') {
            return haystack;
        }

        int i = 0;
        int j = 0;
        while (haystack[i] && needle[j]) {
            if (haystack[i] == needle[j]) {
                i++;
                j++;
                if (needle[j] == '\0') {
                    return haystack + (i - j);
                }
            }
            else {
                j = 0;
                i = i - j + 1;
            }
        }

        return nullptr;
    }

int main() {
	char* s1 = "mississippi";
	char* s2 = "issip";
	//strStr(s1, s2);
	string s = "xcf";
	string sub = s.substr(0, 0);
	return 0;
}