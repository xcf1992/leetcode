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
#include <sstream>
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
class VersionChecker1 {
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
    VersionChecker1(const std::string& minSupportedVersion) : minSupportedVersion(minSupportedVersion), callCount(0) {
    }

    bool isSupported(const std::string& version) {
        this->callCount++;
        return compareVersions(version, minSupportedVersion) >= 0;
    }

    int getCallCount() {
        return this->callCount;
    }
};

class Solution1 {
private:
    VersionChecker1& checker;

public:
    Solution1(VersionChecker1& checker) : checker(checker) {
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
        VersionChecker1 checker("103.3.2");
        Solution1 solution(checker);
        std::string result = solution.findEarliestSupported(versions);
        std::cout << result << std::endl;  // Expected: 103.3.2
        std::cout << "Total calls: " << checker.getCallCount() << std::endl;
    }

    static void test2() {
        std::cout << "\n===== Test 2 =====" << std::endl;
        std::vector<std::string> versions = {"1.0.0", "1.0.1", "1.1.0", "2.0.0"};
        VersionChecker1 checker("1.1.0");
        Solution1 solution(checker);
        std::string result = solution.findEarliestSupported(versions);
        std::cout << result << std::endl;  // Expected: 1.1.0
        std::cout << "Total calls: " << checker.getCallCount() << std::endl;
    }

    static void test3() {
        std::cout << "\n===== Test 3 =====" << std::endl;
        std::vector<std::string> versions = {"3.1.5",   "12.0.3",  "15.8.22",  "30.6.108", "45.2.7",
                                             "67.15.0", "89.3.45", "100.20.5", "150.0.99", "200.10.15"};
        VersionChecker1 checker("67.15.0");
        Solution1 solution(checker);
        std::string result = solution.findEarliestSupported(versions);
        std::cout << result << std::endl;  // Expected: 67.15.0
        std::cout << "Total calls: " << checker.getCallCount() << std::endl;
    }

    static void test4() {
        std::cout << "\n===== Test 4 =====" << std::endl;
        std::vector<std::string> versions = {"0.0.1", "0.0.2", "0.1.0", "1.0.0"};
        VersionChecker1 checker("0.0.1");
        Solution1 solution(checker);
        std::string result = solution.findEarliestSupported(versions);
        std::cout << result << std::endl;  // Expected: 0.0.1
        std::cout << "Total calls: " << checker.getCallCount() << std::endl;
    }

    static void test5() {
        std::cout << "\n===== Test 5 =====" << std::endl;
        std::vector<std::string> versions = {"10.0.0", "20.0.0", "30.0.0", "40.0.0", "50.0.0"};
        VersionChecker1 checker("50.0.0");
        Solution1 solution(checker);
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

int main1() {
    Solution1::main();
    return 0;
}

/*
Follow-up:
In this follow-up, you are again given a sorted ascending list of software versions in the format "MAJOR.MINOR.PATCH"
(e.g., "103.3.2"), and you have access to a function isSupported() that tells you whether a version supports a specific
feature or not.

Unlike the previous problem, where support was globally monotonic (once supported, always supported for all higher
versions), here support is not globally monotonic across the entire list. Instead, the list exhibits a hierarchical
monotonicity:

If a given "MAJOR" version group contains at least one version that supports the feature, then all subsequent "MAJOR"
version groups (if any) will also eventually have at least one supporting version. However, support is not guaranteed
for every individual version within those higher "MAJOR" groups, nor for all subsequent versions in general.

For example, if you discover that a 3.x.x version supports the feature, you can be certain that for every "MAJOR"
version greater than 3 (if any), there will at some point be a version (such as 4.x.x, 5.x.x, etc., with potentially
different MINOR or PATCH numbers) that also supports it.

The same hierarchical rule applies within "MINOR" groups of a given "MAJOR", and within "PATCH" groups of a given
"MINOR".

Your task is to find the earliest version in the list that supports the feature, while minimizing the number of calls to
isSupported API.

Implement the Solution class:

Solution(VersionChecker checker) Initializes your solution with the provided checker API.

String findEarliestSupported(List<String> versions) Returns the earliest version in versions that supports the feature,
following the rules:

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
0 ≤ "MAJOR", "MINOR", "PATCH" ≤
10
5
10
5
 , and no part will have leading zeros.
The versions list is sorted in ascending order.
Example:
Input:
["Solution", "findEarliestSupported"]
["VersionChecker(["1.0.1", "1.0.3", "1.1.0", "2.0.0"])", ["1.0.0", "1.0.1", "1.0.2", "1.0.3", "1.1.0", "2.0.0"]]

Output:
[null, "1.0.1"]

Explanation:

checker = new VersionChecker(["1.0.1", "1.0.3", "1.1.0", "2.0.0"]) // Creates a version checker that can determine
whether a given version is supported, and the list of supported versions is unknown to you. solution = new
Solution(checker); solution.findEarliestSupported(["1.0.0", "1.0.1", "1.0.2", "1.0.3", "1.1.0", "2.0.0"]); // Returns
"1.0.1", determined by making a series of isSupported calls.
 */

/**
 * External API that checks if a version supports a specific feature.
 * You should NOT directly access the supported versions set.
 */

class VersionChecker {
private:
    std::unordered_set<std::string> supportedVersions;
    int callCount;

public:
    VersionChecker(std::unordered_set<std::string> supportedVersions) {
        this->supportedVersions = supportedVersions;
        this->callCount = 0;
    }

    bool isSupported(std::string version) {
        this->callCount++;
        return supportedVersions.find(version) != supportedVersions.end();
    }

    int getCallCount() {
        return this->callCount;
    }
};

struct Version {
    int major;
    int minor;
    int patch;
    std::string original;

    Version(std::string version) {
        this->original = version;
        int pos = version.find(".");
        major = stoi(version.substr(0, pos));

        version = version.substr(pos + 1);
        pos = version.find(".");
        minor = stoi(version.substr(0, pos));

        version = version.substr(pos + 1);
        patch = stoi(version);
    }
};

class Solution {
private:
    VersionChecker* checker;
    std::vector<std::string> versions;

private:
    int binary_search_groups(vector<vector<int>>& groups) {
        int n = groups.size();
        int left = 0;
        int right = n - 1;
        int rst = n - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            vector<int> group = groups[mid];
            string ver = versions[group[1]];
            if (checker->isSupported(ver)) {
                rst = mid;
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return rst;
    }

public:
    Solution(VersionChecker* checker) {
        this->checker = checker;
        this->versions = vector<string>();
    }

    std::string findEarliestSupported(std::vector<std::string> versions) {
        this->versions = versions;
        vector<Version> all_vers;
        for (string& ver : versions) {
            all_vers.push_back(Version(ver));
        }

        vector<vector<int>> major_groups;
        int start = 0;
        int cnt = versions.size();
        for (int i = 1; i <= cnt; i++) {
            if (i == cnt || all_vers[i].major != all_vers[start].major) {
                major_groups.push_back({start, i - 1});
                if (i < cnt) {
                    start = i;
                }
            }
        }

        int major_group_idx = binary_search_groups(major_groups);
        vector<int> major_range = major_groups[major_group_idx];

        vector<vector<int>> minor_groups;
        start = major_range[0];
        int end = major_range[1];
        for (int i = start + 1; i <= end + 1; i++) {
            if (i == end + 1 || all_vers[i].minor != all_vers[start].minor) {
                minor_groups.push_back({start, i - 1});
                if (i <= end) {
                    start = i;
                }
            }
        }

        int minor_group_idx = binary_search_groups(minor_groups);
        vector<int> minor_range = minor_groups[minor_group_idx];
        int left = minor_range[0];
        int right = minor_range[1];
        int rst = right;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (checker->isSupported(versions[mid])) {
                rst = mid;
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return versions[rst];
    }

public:
    static void main() {
        test1();
        test2();
        test3();
        test4();
        test5();
        test6();
        test7();
        test8();
    }

private:
    static void test1() {
        std::cout << "===== Test 1 =====" << std::endl;
        std::vector<std::string> versions = {"1.0.0", "1.0.1", "1.0.2", "1.0.3", "1.1.0", "2.0.0"};
        std::unordered_set<std::string> supported = {"1.0.1", "1.0.3", "1.1.0", "2.0.0"};
        VersionChecker checker(supported);
        Solution solution(&checker);
        std::string result = solution.findEarliestSupported(versions);
        std::cout << result << std::endl;  // Expected: 1.0.1
        std::cout << "Total calls: " << checker.getCallCount() << std::endl;
    }

    static void test2() {
        std::cout << "\n===== Test 2 =====" << std::endl;
        std::vector<std::string> versions = {"1.10.17", "1.10.18", "1.10.19", "1.11.0", "1.11.1",
                                             "2.0.0",   "2.4.1",   "2.4.2",   "2.5.1"};
        std::unordered_set<std::string> supported = {"1.10.17", "1.10.18", "1.10.19", "1.11.1", "2.5.1"};
        VersionChecker checker(supported);
        Solution solution(&checker);
        std::string result = solution.findEarliestSupported(versions);
        std::cout << result << std::endl;  // Expected: 1.10.17
        std::cout << "Total calls: " << checker.getCallCount() << std::endl;
    }

    static void test3() {
        std::cout << "\n===== Test 3 =====" << std::endl;
        std::vector<std::string> versions = {"5.2.1",  "5.2.3",  "5.3.0",  "5.3.5",  "10.0.8",
                                             "10.1.2", "10.1.9", "15.7.3", "15.7.8", "20.5.12"};
        std::unordered_set<std::string> supported = {"5.3.0", "5.3.5", "10.1.9", "15.7.8", "20.5.12"};
        VersionChecker checker(supported);
        Solution solution(&checker);
        std::string result = solution.findEarliestSupported(versions);
        std::cout << result << std::endl;  // Expected: 5.3.0
        std::cout << "Total calls: " << checker.getCallCount() << std::endl;
    }

    static void test4() {
        std::cout << "\n===== Test 4 =====" << std::endl;
        std::vector<std::string> versions = {"3.1.5",  "3.1.9",  "3.2.0",  "7.0.1",  "7.0.3", "7.2.0",
                                             "11.0.0", "11.0.4", "11.1.0", "11.1.2", "11.3.1"};
        std::unordered_set<std::string> supported = {"7.2.0", "11.1.2", "11.3.1"};
        VersionChecker checker(supported);
        Solution solution(&checker);
        std::string result = solution.findEarliestSupported(versions);
        std::cout << result << std::endl;  // Expected: 7.2.0
        std::cout << "Total calls: " << checker.getCallCount() << std::endl;
    }

    static void test5() {
        std::cout << "\n===== Test 5 =====" << std::endl;
        std::vector<std::string> versions = {"10.0.0", "10.1.0", "20.0.0", "30.0.0", "30.1.0", "30.1.5"};
        std::unordered_set<std::string> supported = {"30.1.5"};
        VersionChecker checker(supported);
        Solution solution(&checker);
        std::string result = solution.findEarliestSupported(versions);
        std::cout << result << std::endl;  // Expected: 30.1.5
        std::cout << "Total calls: " << checker.getCallCount() << std::endl;
    }

    static void test6() {
        std::cout << "\n===== Test 6 =====" << std::endl;
        std::vector<std::string> versions = {"1.0.0", "1.0.2", "1.1.0", "1.1.5", "1.1.6", "1.2.0", "1.2.1", "2.0.0"};
        std::unordered_set<std::string> supported = {"1.1.5", "1.1.6", "1.2.1", "2.0.0"};
        VersionChecker checker(supported);
        Solution solution(&checker);
        std::string result = solution.findEarliestSupported(versions);
        std::cout << result << std::endl;  // Expected: 1.1.5
        std::cout << "Total calls: " << checker.getCallCount() << std::endl;
    }

    static void test7() {
        std::cout << "\n===== Test 7 =====" << std::endl;
        std::vector<std::string> versions = {"0.0.0", "0.0.1", "0.1.0", "1.0.0"};
        std::unordered_set<std::string> supported = {"0.0.0", "0.0.1", "0.1.0", "1.0.0"};
        VersionChecker checker(supported);
        Solution solution(&checker);
        std::string result = solution.findEarliestSupported(versions);
        std::cout << result << std::endl;  // Expected: 0.0.0
        std::cout << "Total calls: " << checker.getCallCount() << std::endl;
    }

    static void test8() {
        std::cout << "\n===== Test 8 =====" << std::endl;
        std::vector<std::string> versions = {"7.7.7"};
        std::unordered_set<std::string> supported = {"7.7.7"};
        VersionChecker checker(supported);
        Solution solution(&checker);
        std::string result = solution.findEarliestSupported(versions);
        std::cout << result << std::endl;  // Expected: 7.7.7
        std::cout << "Total calls: " << checker.getCallCount() << std::endl;
    }
};
/**
===== Test 1 =====
1.0.1
Total calls: 4

===== Test 2 =====
1.10.17
Total calls: 4

===== Test 3 =====
5.3.0
Total calls: 4

===== Test 4 =====
7.2.0
Total calls: 3

===== Test 5 =====
30.1.5
Total calls: 3

===== Test 6 =====
1.1.5
Total calls: 5

===== Test 7 =====
0.0.0
Total calls: 3

===== Test 8 =====
7.7.7
Total calls: 0
 */
int main() {
    Solution::main();
    return 0;
}