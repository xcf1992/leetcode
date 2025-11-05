/*
535. Encode and Decode TinyURL
Note: This is a companion problem to the System Design problem: Design TinyURL.
TinyURL is a URL shortening service where you enter a URL such as https://leetcode.com/problems/design-tinyurl
and it returns a short URL such as http://tinyurl.com/4e9iAk.

Design the encode and decode methods for the TinyURL service.
There is no restriction on how your encode/decode algorithm should work.
You just need to ensure that a URL can be encoded to a tiny URL and the tiny URL can be decoded to the original URL.
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
#include <stdlib.h>
#include <time.h>
using namespace std;

class Solution {
private:
    int length = 3;
    unordered_map<string, string> short2Long;
    unordered_map<string, string> long2Short;

    string generateRandomString(string longUrl) {
        srand(time(nullptr));
        string shortUrl = "";
        for (int i = 0; i < length; i++) {
            shortUrl.push_back('\0' + rand() % 128);
        }
        return shortUrl;
    }

public:
    // Encodes a URL to a shortened URL.
    string encode(string longUrl) {
        if (long2Short.find(longUrl) != long2Short.end()) {
            return long2Short[longUrl];
        }

        string shortUrl = "";
        do {
            shortUrl = generateRandomString(longUrl);
        } while (short2Long.find(shortUrl) != short2Long.end());

        short2Long["http://tinyurl.com/" + shortUrl] = longUrl;
        long2Short[longUrl] = "http://tinyurl.com/" + shortUrl;
        return "http://tinyurl.com/" + shortUrl;
    }

    // Decodes a shortened URL to its original URL.
    string decode(string shortUrl) {
        return short2Long[shortUrl];
    }
};

// Your Solution object will be instantiated and called as such:
// Solution solution;
// solution.decode(solution.encode(url));