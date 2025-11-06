/*
 800. Similar RGB Color
 In the following, every capital letter represents some hexadecimal digit from 0 to f.

 The red-green-blue color "#AABBCC" can be written as "#ABC" in shorthand.
 For example, "#15c" is shorthand for the color "#1155cc".

 Now, say the similarity between two colors "#ABCDEF" and "#UVWXYZ" is -(AB - UV)^2 - (CD - WX)^2 - (EF - YZ)^2.

 Given the color "#ABCDEF", return a 7 character color that is most similar to #ABCDEF,
 and has a shorthand (that is, it can be represented as some "#XYZ"

 Example 1:
 Input: color = "#09f166"
 Output: "#11ee66"
 Explanation:
 The similarity is -(0x09 - 0x11)^2 -(0xf1 - 0xee)^2 - (0x66 - 0x66)^2 = -64 -9 -0 = -73.
 This is the highest among any shorthand color.
 Note:

 color is a string of length 7.
 color is a valid RGB color: for i > 0, color[i] is a hexadecimal digit from 0 to f
 Any answer which has the same (highest) similarity as the best answer will be accepted.
 All inputs and outputs should use lowercase letters, and the output is 7 characters.
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
#include <set>
using namespace std;

/*
 Find corresponding index, i.e. value/17 or value/17+1. This is because “11” or “33” or “bb” are simply 1*17, 3*17, and
 11*17.
*/
class Solution {
private:
    string colorDigit = "0123456789abcdef";

    string getColor(string s) {
        int num = stoi(s, nullptr, 16);
        int c = num / 17;
        if (num % 17 > 8) {
            c += 1;
        }
        return string(2, colorDigit[c]);
    }

public:
    string similarRGB(string color) {
        return "#" + getColor(color.substr(1, 2)) + getColor(color.substr(3, 2)) + getColor(color.substr(5, 2));
    }
};