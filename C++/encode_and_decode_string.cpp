/*
 Design an algorithm to encode a list of strings to a string. The encoded string is then sent over the network and is decoded back to the original list of strings.
 
 Machine 1 (sender) has the function:
 
 string encode(vector<string> strs) {
 // ... your code
 return encoded_string;
 }
 Machine 2 (receiver) has the function:
 vector<string> decode(string s) {
 //... your code
 return strs;
 }
 So Machine 1 does:
 
 string encoded_string = encode(strs);
 and Machine 2 does:
 
 vector<string> strs2 = decode(encoded_string);
 strs2 in Machine 2 should be the same as strs in Machine 1.
 
 Implement the encode and decode methods.
 
 Note:
 The string may contain any possible characters out of 256 valid ascii characters. Your algorithm should be generalized enough to work on any possible characters.
 Do not use class member/global/static variables to store states. Your encode and decode algorithms should be stateless.
 Do not rely on any library method such as eval or serialize methods. You should implement your own encode/decode algorithm.
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
#include <numeric>
using namespace std;
class Codec {
public:

    // Encodes a list of strings to a single string.
    string encode(vector<string>& strs) {
        if (strs.empty()) {
            return "";
        }
        
        string result = "";
        for (string s : strs) {
            for (char c : s) {
                if (c == '#') {
                    result += "$#";
                }
                else if (c == '$') {
                    result += "$$";
                }
                else {
                    result.push_back(c);
                }
            }
            result += "#";
        }
        return result;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(string s) {
        if (s == "") {
            return {};
        }
        
        vector<string> result;
        string cur = "";
        int index = 0;
        while (index < s.size()) {
            if (s[index] == '#') {
                result.push_back(cur);
                cur = "";
                index += 1;
                continue;
            }
            
            if (s[index] == '$') {
                index += 1;
            }
            cur += s[index];
            index += 1;
        }
        return result;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.decode(codec.encode(strs));

// reason we need both start letter and end letter
// if the input list is ["", ""] and we onlly have start or end letter
// then we cannot test if there are two string or one start letter
class Codec1 {
public:
    
    // Encodes a list of strings to a single string.
    string encode(vector<string>& strs) {
        string result = "$";
        for (string str : strs) {
            result += "#";
            for (char c : str) {
                if (c == '#') {
                    result += "##";
                }
                else if (c == '$') {
                    result += "$$";
                }
                else {
                    result += c;
                }
            }
            result += "$";
        }
        return result;
    }
    
    // Decodes a single string to a list of strings.
    vector<string> decode(string s) {
        vector<string> result;
        string cur = "";
        bool met = false;
        for (int i = 0; i < s.size(); i++) {
            char letter = s[i];
            if (letter == '#') {
                if (i + 1 < s.size() && s[i + 1] == '#') {
                    cur += letter;
                    i++;
                }
                else {
                    cur = "";
                }
            }
            else if (letter == '$') {
                if (i + 1 < s.size() && s[i + 1] == '$') {
                    cur += letter;
                    i++;
                }
                else {
                    if (met) {
                        result.push_back(cur);
                    }
                    met = true;
                    cur = "";
                    i++;
                }
            }
            else {
                cur += letter;
            }
        }
        return result;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.decode(codec.encode(strs));
