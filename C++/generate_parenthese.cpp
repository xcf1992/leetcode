#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue>
using namespace std;

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> result;
        result.clear();
        
        if (n == 0) {
            return result;
        }
        
        if (n == 1) {
            string s = "()";
            result.push_back(s);
            return result;
        }
        
        string s;
        generate(result, n, n, s);
        
        return result;
    }
    
    void generate(vector<string> &result, int left, int right, string &s) {
        if (left < 0 || left > right) {
            return;
        }
        
        if (left == 0 && right == 0) {
            result.push_back(s);
            return ;
        }
        
        if (left > 0) {
            string temp = s + "(";
            generate(result, left - 1, right, temp);
        }
        if (right > left) {
            string temp = s + ")";
            generate(result, left, right - 1, temp);
        }
    }
};

class cmp {
public:
	bool operator() (const int &l, const int &r) {
		return l > r;
	}
};

int main() {
	string s1 = "a";
	string s2 = "aa";
	cout << s2.compare(s1) << endl;
	priority_queue<int, vector<int>, cmp> q;
	q.push(10);
	q.push(100);
	q.push(102);
	q.push(30);
	q.push(3);
	cout << q.top() << endl;
	return 0;
}