/*
 165. Compare Version Numbers

 Compare two version numbers version1 and version2.
 If version1 > version2 return 1; if version1 < version2 return -1;otherwise return 0.

 You may assume that the version strings are non-empty and contain only digits and the . character.

 The . character does not represent a decimal point and is used to separate number sequences.

 For instance, 2.5 is not "two and a half" or "half way to version three",
 it is the fifth second-level revision of the second first-level revision.

 You may assume the default revision number for each level of a version number to be 0.
 For example, version number 3.4 has a revision number of 3 and 4 for its first and second level revision number.
 Its third and fourth level revision number are both 0.



 Example 1:

 Input: version1 = "0.1", version2 = "1.1"
 Output: -1
 Example 2:

 Input: version1 = "1.0.1", version2 = "1"
 Output: 1
 Example 3:

 Input: version1 = "7.5.2.4", version2 = "7.5.3"
 Output: -1
 Example 4:

 Input: version1 = "1.01", version2 = "1.001"
 Output: 0
 Explanation: Ignoring leading zeroes, both “01” and “001" represent the same number “1”
 Example 5:

 Input: version1 = "1.0", version2 = "1.0.0"
 Output: 0
 Explanation: The first version number does not have a third level revision number, which means its third level revision number is default to "0"


 Note:

 Version strings are composed of numeric strings separated by dots . and this numeric strings may have leading zeroes.
 Version strings do not start or end with dots, and they will not be two consecutive dots.
*/
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
        int v1 = stoi(ver1);
        int v2 = stoi(ver2);
        if (v1 > v2) {
            return 1;
        }
        if (v1 == v2) {
            return 0;
        }
        return -1;
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

        version1 = pos1 == string::npos ? "0" : version1.substr(pos1 + 1);
        version2 = pos2 == string::npos ? "0" : version2.substr(pos2 + 1);
        return compareVersion(version1, version2);
    }
};
