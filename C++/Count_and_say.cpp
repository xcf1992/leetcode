#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

string newSay(string say) {
        vector<int> num;
        num.clear();
        
        int digit = say.at(0) - '0';
        num.push_back(1);
        num.push_back(digit);
        int pos = 0;
        
        for (unsigned int i = 1; i != say.size(); i++) {
            int newDigit = say.at(i) - '0';
            if (newDigit == digit) {
                num.at(pos)++;
            }
            else {
                num.push_back(1);
                num.push_back(newDigit);
                digit = newDigit;
                pos += 2;
            }
        }
        
        string newSay;
        newSay.clear();
        for (unsigned int i = 0; i != num.size(); i++) {
            char c = (char) (num.at(i) + '0');
            newSay.push_back(c);
        }
        
        return newSay;
    }

string countAndSay(int n) {
        if (n <= 0) {
            return string();
        }
        
        string say = "1";
        for (unsigned int i = 0; i != n; i++) {
            say = newSay(say);
        }
        
        return say;
    }
    
int main() {
	cout << countAndSay(1) << endl;
	return 0;
}
    