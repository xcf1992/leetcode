#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;


class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {
        if (numerator == 0) {
            return "0";
        }
        if (numerator == denominator) {
            return "1";
        }

        bool negative = false;
        long long quotient = 0;
		long long dmt = denominator;
		long long rest = numerator;
        if (rest > 0) {
            if (dmt < 0) {
                dmt = 0 - dmt;
                negative = true;
            }
        }
        else {
            rest = 0 - rest;
            if (dmt > 0) {
                negative = true;
            }
            else {
                dmt = 0 - dmt;
            }
        }
        
        
        string result = "";
        if (rest > dmt) {
            quotient = rest / dmt;
            rest = rest % dmt;
            
            result = to_string(quotient);
            if (rest == 0) {
                if (negative) {
                    result = "-" + result;
                }
                return result;
            }
        }
        else {
            result += "0";
        }
        result += ".";
        
        int i = result.size();
        unordered_map<int, int> restNum;
        while (restNum.find(rest) == restNum.end()) {
            restNum[rest] = i++;
            rest *= 10;
			result = result + to_string(rest / dmt);
            rest = rest % dmt;
            if (rest == 0) {
				if (negative) {
					return "-" + result;
				}
				return result;
			}
        }
        
		string recur = result.substr(restNum[rest]);
		result = result.substr(0, restNum[rest]) + "(" + recur + ")";
		if (negative) {
			return "-" + result;
		}
		return result;
    }
};

int main() {
	Solution s;
	s.fractionToDecimal(-2147483648, 1);
	return 0;
}