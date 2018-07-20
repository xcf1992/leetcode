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
#include <set>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

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
        if (segment == "" || (segment.size() > 1 && segment[0] == '0')) {
            return false;
        }
        
        int value = 0;
        for (int i = 0; i < segment.size(); i++) {
            if (!isdigit(segment[i])) {
                return false;
            }
            value = value * 10 + (segment[i] - '0');
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
        if (length == 0 || length > 4) {
            return false;
        }
        
        for (char c : segment) {
            if (isdigit(c)) {
                continue;
            }
            if (c >= 'a' && c <= 'f') {
                continue;
            }
            if (c >= 'A' && c <= 'F') {
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


int main() {
    Solution s;
    vector<string> v({"ahjpjau","ja","ahbwzgqnuk","tnmlanowax"});
    vector<int> va({4,5,8,2});
    vector<int> vb({3,2});
    vector<string> v2({"a","cd"});
    vector<char> chars({'a','a','a','a','a','b','b','c'});
    
    vector<vector<int>> matrix1({{0,0,1,1}, {1,0,1,0}, {1,1,0,0}});
    vector<vector<char>> matrix2({
        {'1','1','1','1','1','1','1','1'},
        {'1','1','1','1','1','1','1','0'},
        {'1','1','1','1','1','1','1','0'},
        {'1','1','1','1','1','0','0','0'},
        {'0','1','1','1','1','0','0','0'}
    });
    
    vector<pair<int, int>> fuxk;
    fuxk.push_back(make_pair(0,1));
    fuxk.push_back(make_pair(0,2));
    //fuxk.push_back(make_pair(1,3));
    //fuxk.push_back(make_pair(0,4));
    //fuxk.push_back(make_pair(5,4));
    //fuxk.push_back(make_pair(6,4));
    //fuxk.push_back(make_pair(6,7));
    
    cout << s.validIPAddress(":2001:008:85a3::0:8A2E:0370:7334:") << endl;
    return 0;
}
