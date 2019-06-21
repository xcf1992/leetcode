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
#include <numeric>
using namespace std;

class Solution {
private:
    //function to seperate each expression
    string parse(string& s, int& start) {
        int end = start + 1, temp = start, count = 1;
        if (s[start] == '(') {
            while (count != 0) {
                if (s[end] == '(')
                    count++;
                else if (s[end] == ')')
                    count--;
                end++;
            }
        }
        else {
            while (end < s.size() && s[end] != ' ')
                end++;
        }
        start = end + 1;
        return s.substr(temp, end - temp);
    }

    int calculate(string expression, unordered_map<string, int> myMap) {
        if (expression[0] == '-' || isdigit(expression[0])) {
            return stoi(expression);
        }
        if (expression[0] != '(') {
            return myMap[expression];
        }
        //to get rid of the first '(' and the last ')'
        int n = expression.size();
        string s = expression.substr(1, n - 2);
        int start = 0;
        string word = parse(s, start);
        if (word == "let") {
            while (true) {
                string variable = parse(s,start);
                //if there is no more expression, simply evaluate the variable
                if (start > s.size()) {
                    return calculate(variable, myMap);
                }
                string temp = parse(s, start);
                myMap[variable] = calculate(temp, myMap);
            }
        }
        else if (word == "add"){
            return calculate(parse(s, start), myMap) + calculate(parse(s,start), myMap);
        }
        else if (word == "mult") {
            return calculate(parse(s, start), myMap) * calculate(parse(s,start), myMap);
        }
    }
public:
    int evaluate(string expression) {
        unordered_map<string, int> myMap;
        return calculate(expression, myMap);
    }
};

int main() {
    Solution s;
    vector<int> temp({1,3,2,4});
    vector<int> temp1({1,3,3,3,2});
    vector<vector<char>> matrix({
        {'1','0','1','0','0'},
        {'1','0','1','1','1'},
        {'1','1','1','1','1'},
        {'1','0','0','1','0'}
    });
    vector<string> words({"cat","cats","and","sand","dog"});
    s.evaluate("(add 1 2)");
}
