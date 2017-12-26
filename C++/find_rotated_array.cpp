#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int result = 0;
    int m;
    int n;
    unordered_map<string, int> pattern;
    cin >> m;
    cin >> n;
    
    for (int i = 0; i < m; i++) {
        string row1;
        string row2;
        for (int j = 0; j < n; j++) {
            char c;
            cin >> c;
            row1 = row1 + c;
            if (c == 'T') {
                row2 = row2 + 'P';
            }
            else {
                row2 = row2 + 'T';
            }
        }
        if (pattern.find(row1) == pattern.end()) {
            pattern[row1] = 1;
        }
        else {
            pattern[row1]++;
        }
        if (pattern.find(row2) == pattern.end()) {
            pattern[row2] = 1;
        }
        else {
            pattern[row2]++;
        }
    }
    
    for (unordered_map<string, int>::iterator it = pattern.begin(); it != pattern.end(); it++) {
        result = max(result, it->second);
    }
    cout << result << endl;
    return 0;
}