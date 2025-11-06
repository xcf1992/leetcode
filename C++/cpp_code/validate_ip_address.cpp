/*
 Write a function to check whether an input string is a valid IPv4 address or IPv6 address or neither.

 IPv4 addresses are canonically represented in dot-decimal notation, which consists of four decimal numbers, each
 ranging from 0 to 255, separated by dots ("."), e.g.,172.16.254.1;

 Besides, leading zeros in the IPv4 is invalid. For example, the address 172.16.254.01 is invalid.

 IPv6 addresses are represented as eight groups of four hexadecimal digits, each group representing 16 bits. The groups
 are separated by colons (":"). For example, the address 2001:0db8:85a3:0000:0000:8a2e:0370:7334 is a valid one. Also,
 we could omit some leading zeros among four hexadecimal digits and some low-case characters in the address to
 upper-case ones, so 2001:db8:85a3:0:0:8A2E:0370:7334 is also a valid IPv6 address(Omit leading zeros and using upper
 cases).

 However, we don't replace a consecutive group of zero value with a single empty group using two consecutive colons (::)
 to pursue simplicity. For example, 2001:0db8:85a3::8A2E:0370:7334 is an invalid IPv6 address.

 Besides, extra leading zeros in the IPv6 is also invalid. For example, the address
 02001:0db8:85a3:0000:0000:8a2e:0370:7334 is invalid.

 Note: You may assume there is no extra space or special characters in the input string.

 Example 1:
 Input: "172.16.254.1"

 Output: "IPv4"

 Explanation: This is a valid IPv4 address, return "IPv4".
 Example 2:
 Input: "2001:0db8:85a3:0:0:8A2E:0370:7334"

 Output: "IPv6"

 Explanation: This is a valid IPv6 address, return "IPv6".
 Example 3:
 Input: "256.256.256.256"

 Output: "Neither"

 Explanation: This is neither a IPv4 address nor a IPv6 address.
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
using namespace std;

class Solution {
private:
    vector<string> splitString(string& s, char delimiter) {
        string temp = s;
        vector<string> tokens;
        do {
            int pos = temp.find(delimiter);
            tokens.push_back(temp.substr(0, pos));
            temp = temp.substr(pos + 1);
        } while (temp.find(delimiter) != string::npos);
        tokens.push_back(temp);
        return tokens;
    }

    string validateIPv4(string ip) {
        vector<string> segments = splitString(ip, '.');
        if (segments.size() != 4) {
            return "Neither";
        }

        for (string segment : segments) {
            if (!validIPv4Segment(segment)) {
                return "Neither";
            }
        }
        return "IPv4";
    }

    bool validIPv4Segment(string segment) {
        if (segment == "" or (segment.size() > 1 and segment[0] == '0')) {
            return false;
        }

        int value = 0;
        for (int i = 0; i < segment.size(); i++) {
            if (!isdigit(segment[i])) {
                return false;
            }
            value = value * 10 + (segment[i] - '0');
            if (value > 255) {
                return false;
            }
        }
        return value <= 255;
    }

    string validateIPv6(string ip) {
        vector<string> segments = splitString(ip, ':');
        if (segments.size() != 8) {
            return "Neither";
        }

        for (string segment : segments) {
            if (!validIPv6Segment(segment)) {
                return "Neither";
            }
        }
        return "IPv6";
    }

    bool validIPv6Segment(string segment) {
        int length = segment.size();
        if (length == 0 or length > 4) {
            return false;
        }

        for (char c : segment) {
            if (isdigit(c)) {
                continue;
            }
            if (c >= 'a' and c <= 'f') {
                continue;
            }
            if (c >= 'A' and c <= 'F') {
                continue;
            }
            return false;
        }
        return true;
    }

public:
    string validIPAddress(string IP) {
        if (IP.find('.') != string::npos) {
            return validateIPv4(IP);
        }

        if (IP.find(':') != string::npos) {
            return validateIPv6(IP);
        }
        return "Neither";
    }
};