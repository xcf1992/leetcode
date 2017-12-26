#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

/*string addBinary(string a, string b) {
        if (a.size() == 0) {
            return b;
        }
        if (b.size() == 0) {
            return a;
        }
        
        string result = "";
        int min = a.size();
        if (min > b.size()) {
            min = b.size();
        }
        
        int flag = 0;
        int aPos = a.size() - 1;
        int bPos = b.size() - 1;
        for (int i = 0; i != min; i++) {
            int aDigit = a.at(aPos - i) - '0';
            int bDigit = b.at(bPos - i) - '0';
            int digit = aDigit + bDigit + flag;
            
            flag = digit / 2;
            char cur = digit % 2 + '0';
            result = cur + result;
        }
        
        if (min < a.size()) {
            aPos = a.size() - 1;
            for (int i = min; i != a.size(); i++) {
                int aDigit = a.at(aPos - i) - '0';
                int digit = aDigit + flag;
                flag = digit / 2;
                char cur = digit % 2 + '0';
                result = cur + result;
            }
        }
        else if (min < b.size()) {
            bPos = b.size() - 1;
            for (int i = min; i != b.size(); i++) {
                int bDigit = b.at(bPos - i) - '0';
                int digit = bDigit + flag;
                flag = digit / 2;
                char cur = digit % 2 + '0';
                result = cur + result;
            }
        }
        
        if (flag == 1) {
            result = "1" + result;
        }
        
        return result;
    }
	*/
string addBinary(string a, string b) {
        if (a.empty()) {
            return b;
        }
        
        if (b.empty()) {
            return a;
        }
        
        if (a.size() < b.size()) {
            string temp = a;
            a = b;
            b = temp;
        }
        
        string result;
        int m = a.size();
        int n = b.size();
        int flag = 0;
        for (int i = 0; i < n; i++) {
            int digit = (flag + (a[m - 1 - i] - '0') + (b[n - 1 - i] - '0')) % 2;
            flag = (flag + (a[m - 1 - i] - '0') + (b[n - 1 - i] - '0')) / 2;
            result = (digit + "0") + result;
        }
        for (int i = n; i < m; i++) {
            int digit = (flag + (a[m - 1 - i] - '0')) % 2;
            flag = (flag + (a[m - 1 - i] - '0')) / 2;
            result = (digit + "0") + result;
        }
        if (flag) {
            result = "1" + result;
        }
        
        return result;
    }

int main() {
	string a = "111";
	string b = "1111";
	cout << addBinary(a, b) << endl;
}