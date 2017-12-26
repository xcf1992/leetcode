#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

int main() {
	string s1 = "09999";
	string s2 = "1";
	if (s1 > s2) {
		cout << "s1 > s2" << endl;
	}
	else {
		cout << "s1 < s2" << endl;
	}
	return 0;
}