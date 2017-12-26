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
using namespace std;


class Solution {
public:
    bool wordPattern(string pattern, string str) {
        vector<string> st;
        string temp;
        for(auto c:str){
            if(c!=' ') temp+=c;
            else {
                st.push_back(temp);
                temp="";
            }
        }
        st.push_back(temp);
        
        if(pattern.length()!=st.size()) return false;
        
        unordered_map<char,string> mp1;
        unordered_map<string,char> mp2;
        int i=0;
        for(auto c:pattern){
            if(mp1.find(c)==mp1.end()) mp1[c]=st[i];
            else if(mp1[c]!=st[i]) return false;
            i++;
        }
        i=0;
        for(auto s:st){
            if(mp2.find(s)==mp2.end()) mp2[s]=pattern[i];
            else if(mp2[s]!=pattern[i]) return false;
            i++;
        }
        return true;
    }
};

int main() {
    Solution s;
    cout << s.wordPattern("aba", "wo cao wo");
    return 0;
}