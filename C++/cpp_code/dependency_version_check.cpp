/*
https://www.hack2hire.com/companies/openai/coding-questions/6913fa95fa8a311e42671e68/practice?questionId=6913fb43fa8a311e42671e69
Dependency Version Check

A software company is managing its product releases. They maintain a list of all software versions, sorted in ascending
chronological order. A new, critical feature was supported in one of these versions, and if a version has the feature,
all subsequent versions also support it.

You are given this sorted list of version strings, versions. Each version string follows the "MAJOR.MINOR.PATCH" format
(e.g., "103.3.2"), and you must use the provided VersionChecker API to identify the first version with the feature.

You are given the VersionChecker API:


class VersionChecker {

     @param version A version string.
     @return true if the version is supported, false otherwise.

    public boolean isSupported(String version);
}
Implement the Solution class:

Solution(VersionChecker checker) Initializes your solution with the provided checker API.

String findEarliestSupported(List<String> versions) Find and return the earliest version string in the list that is
supported, following the rules:

You must use the isSupported method from VersionChecker class to check each version.
It is guaranteed that at least one version in the list is supported.
Your implementation should minimize the number of calls to isSupported.
Constraints:

1 ≤ versions.length ≤
10
5
10
5

Each version string is in the format "MAJOR.MINOR.PATCH".
0 ≤ MAJOR, MINOR, PATCH ≤
10
5
10
5
 , and no part will have leading zeros.
The versions list is sorted in ascending order.
Example:

Input:
["Solution", "findEarliestSupported"]
["VersionChecker("103.3.2")", ["101.1.2", "101.1.3", "101.2.1", "102.0.1", "103.3.2", "103.3.3"]]

Output:
[null, "103.3.2"]

Explanation:

checker = new VersionChecker("103.3.2") // Creates a version checker that can determine whether a given version is
supported, and the earliest version string is unknown to you. solution = new Solution(checker);
solution.findEarliestSupported([["101.1.2", "101.1.3", "101.2.1", "102.0.1", "103.3.2", "103.3.3"]); // Returns
"103.3.2", determined by making a series of isSupported calls.
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <set>
using namespace std;

/**
 * External API that checks if a version supports a specific feature.
 * You should NOT directly access the `minSupportedVersion`.
 */
class VersionChecker {
private:
    const std::string minSupportedVersion;
    int callCount;

    int compareVersions(const std::string& v1, const std::string& v2) {
        std::vector<std::string> parts1, parts2;

        // Split v1
        std::stringstream ss1(v1);
        std::string part;
        while (std::getline(ss1, part, '.')) {
            parts1.push_back(part);
        }

        // Split v2
        std::stringstream ss2(v2);
        while (std::getline(ss2, part, '.')) {
            parts2.push_back(part);
        }

        for (int i = 0; i < 3; i++) {
            int num1 = std::stoi(parts1[i]);
            int num2 = std::stoi(parts2[i]);
            if (num1 != num2) {
                return (num1 < num2) ? -1 : 1;
            }
        }
        return 0;
    }

public:
    VersionChecker(const std::string& minSupportedVersion) : minSupportedVersion(minSupportedVersion), callCount(0) {
    }

    bool isSupported(const std::string& version) {
        this->callCount++;
        return compareVersions(version, minSupportedVersion) >= 0;
    }

    int getCallCount() {
        return this->callCount;
    }
};

class Solution {
private:
    VersionChecker& checker;

public:
    Solution(VersionChecker& checker) : checker(checker) {
    }

    std::string findEarliestSupported(const std::vector<std::string>& versions) {
        int n = versions.size();
        int left = 0;
        int rst = n - 1;
        int right = n - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (checker.isSupported(versions[mid])) {
                rst = mid;
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return versions[rst];
    }

    static void test1() {
        std::cout << "===== Test 1 =====" << std::endl;
        std::vector<std::string> versions = {"101.1.2", "101.1.3", "101.2.1", "102.0.1", "103.3.2", "103.3.3"};
        VersionChecker checker("103.3.2");
        Solution solution(checker);
        std::string result = solution.findEarliestSupported(versions);
        std::cout << result << std::endl;  // Expected: 103.3.2
        std::cout << "Total calls: " << checker.getCallCount() << std::endl;
    }

    static void test2() {
        std::cout << "\n===== Test 2 =====" << std::endl;
        std::vector<std::string> versions = {"1.0.0", "1.0.1", "1.1.0", "2.0.0"};
        VersionChecker checker("1.1.0");
        Solution solution(checker);
        std::string result = solution.findEarliestSupported(versions);
        std::cout << result << std::endl;  // Expected: 1.1.0
        std::cout << "Total calls: " << checker.getCallCount() << std::endl;
    }

    static void test3() {
        std::cout << "\n===== Test 3 =====" << std::endl;
        std::vector<std::string> versions = {"3.1.5",   "12.0.3",  "15.8.22",  "30.6.108", "45.2.7",
                                             "67.15.0", "89.3.45", "100.20.5", "150.0.99", "200.10.15"};
        VersionChecker checker("67.15.0");
        Solution solution(checker);
        std::string result = solution.findEarliestSupported(versions);
        std::cout << result << std::endl;  // Expected: 67.15.0
        std::cout << "Total calls: " << checker.getCallCount() << std::endl;
    }

    static void test4() {
        std::cout << "\n===== Test 4 =====" << std::endl;
        std::vector<std::string> versions = {"0.0.1", "0.0.2", "0.1.0", "1.0.0"};
        VersionChecker checker("0.0.1");
        Solution solution(checker);
        std::string result = solution.findEarliestSupported(versions);
        std::cout << result << std::endl;  // Expected: 0.0.1
        std::cout << "Total calls: " << checker.getCallCount() << std::endl;
    }

    static void test5() {
        std::cout << "\n===== Test 5 =====" << std::endl;
        std::vector<std::string> versions = {"10.0.0", "20.0.0", "30.0.0", "40.0.0", "50.0.0"};
        VersionChecker checker("50.0.0");
        Solution solution(checker);
        std::string result = solution.findEarliestSupported(versions);
        std::cout << result << std::endl;  // Expected: 50.0.0
        std::cout << "Total calls: " << checker.getCallCount() << std::endl;
    }

    static void main() {
        test1();
        test2();
        test3();
        test4();
        test5();
    }
};

int main() {
    Solution::main();
    return 0;
}