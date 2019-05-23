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
#include <numeric>
using namespace std;

class Solution {
private:
    int compare(string ver1, string ver2) {
        if (ver1 == ver2) {
            return 0;
        }

        int len1 = ver1.size();
        int idx1 = 0;
        while (idx1 < len1 and ver1[idx1] == '0') {
            idx1 += 1;
        }

        int len2 = ver2.size();
        int idx2 = 0;
        while (idx2 < len2 and ver2[idx2] == '0') {
            idx2 += 1;
        }

        while (idx1 < len1 and idx2 < len2) {
            if (ver1[idx1] < ver2[idx2]) {
                return -1;
            }
            if (ver1[idx1] > ver2[idx2]) {
                return 1;
            }
            idx1 += 1;
            idx2 += 1;
        }

        if (idx1 == len1) {
            return -1;
        }
        return 1;
    }
public:
    int compareVersion(string version1, string version2) {
        if (version1 == version2) {
            return 0;
        }

        if (version1.empty()) {
            return -1;
        }

        if (version2.empty()) {
            return 1;
        }

        size_t pos1 = version1.find('.');
        string subVer1 = pos1 == string::npos ? version1 : version1.substr(0, pos1);

        size_t pos2 = version2.find('.');
        string subVer2 = pos2 == string::npos ? version2 : version2.substr(0, pos2);

        int result = compare(subVer1, subVer2);
        if (result != 0) {
            return result;
        }

        version1 = pos1 == string::npos ? "" : version1.substr(pos1 + 1);
        version2 = pos2 == string::npos ? "" : version2.substr(pos2 + 1);
        return compareVersion(version1, version2);
    }
};
int main() {
    int x = stoi("001");
    Solution s;
    vector<int> temp({1,10,100,1000});
    s.compareVersion("01", "1");
}
