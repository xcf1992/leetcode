#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

string multiply(string num1, string num2) {
        if (num1.empty() || num2.empty()) {
            return "0";
        }
        if (num1.front() == '0' || num2.front() == '0') {
            return "0";
        }
        
        if (num1.size() < num2.size()) {
            swap(num1, num2);
        }
        
        vector<int> n1;
        for (int i = 0; i < num1.size(); i++) {
            n1.push_back(num1[i] - '0');
        }
        
        vector<int> n2;
        for (int i = 0; i != num2.size(); i++) {
            n2.push_back(num2[i] - '0');
        } 

        vector<int> r(n1.size(), 0);
        for (int i = n2.size() - 1; i >= 0; i--) {
            vector<int> temp(n1.size() + n2.size() - 1 - i, 0);
            for (int j = n1.size() - 1; j >= 0; j--) {
               temp[j] = n2[i] * n1[j];
            }
                
            int end1 = temp.size() - 1;
            int end2 = r.size() - 1;
            for (int m = 0; m != r.size(); m++) {
                temp[end1 - m] = temp[end1 - m] + r[end2 - m];
            }
            
            r.resize(temp.size() + 1, 0);
            end1 = temp.size() - 1;
            end2 = r.size() - 1;
            int flag = 0;
            for (int n = 0; n != temp.size(); n++) {
                r[end2 - n] = (temp[end1 - n] + flag) % 10;
                flag = (temp[end1 - n] + flag) / 10;
            }
            r[0] = flag;
        }
        
        string result;
        for (int i = 0; i != r.size(); i++) {
            if (i == 0 && r[i] != 0) {
                result += '0' + r.at(i);
            }
            else {
                result += '0' + r.at(i);
            }
        }
        
        return result;
    }

int main() {
	string s1 = "1";
	string s2 = "1";
	multiply(s1, s2);
	return 0;
}