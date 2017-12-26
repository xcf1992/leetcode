#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

bool isMatch(const char *s, const char *p) {
        if (s == nullptr) {
            return p == nullptr;
        }
        if (p == nullptr) {
            return false;
        }

        if (*p == '\0') {
            return *s == '\0';
        }

        if (*(p + 1) != '*') {
            if (*s == '\0') {
                return false;
            }
            if (*p == *s || *p == '.') {
                return isMatch(s + 1, p + 1);
            }
            return false;
        }
        else {
            while (*s != '\0' && (*p == *s || *p == '.')) {
                if (isMatch(s, p + 2)) {
                    return true;
                }
                s++;
            }
            return isMatch(s, p + 2);
        }
    }

int main() {
	char *s = "";
	char *p = "*";
	bool b = isMatch(s, p);
	if (b) {
		cout << "true" << endl;
	}
	else {
		cout << " false" << endl;
	}
	cout << b << endl;
	return 0;
}