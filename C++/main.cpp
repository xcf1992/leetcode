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
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

struct Tuple {
    int node;
    int bitMask;
    int cost;
    
    Tuple(int n, int b, int c) {
        node = n;
        bitMask = b;
        cost = c;
    }
};

struct TupleHash {
    size_t operator()(const Tuple& tuple) {
        return 97 * tuple.bitMask + 71 * tuple.node;
    }
};

struct TupleComp {
    bool operator()(const Tuple& a, const Tuple& b) {
        return a.node == b.node && a.bitMask == b.bitMask;
    }
};

class Node {
public:
    int val;
    Node* next;
    
    Node() {}
    
    Node(int _val, Node* _next) {
        val = _val;
        next = _next;
    }
};

class Solution {
public:
    string makePalindromic(string s) {
        for (int i = 0, j = (int)s.length() - 1; i < j; i++, j--)
            s[j] = s[i];
        return s;
    }
    
    string nearestPalindromic(string n) {
        if (n == "0")
            return "1";
        
        long long orgVal = stoll(n);
        
        // candidate #1 (ex: 123xx -> 12321, 123xxx -> 123321)
        string res = makePalindromic(n);
        long long resVal = stoll(res);
        long long diff = abs(resVal - orgVal);
        
        long long scale = (long long)pow(10, (int)n.length() / 2);
        
        // candidate #2 (ex: 123xx -> 12221, 123xxx -> 122221, 100xx -> 9999)
        int x = (orgVal / scale) * scale;
        string smaller = makePalindromic(to_string((orgVal / scale) * scale - 1));
        // candidate #3 (ex: 123xx -> 12421, 123xxx -> 124421, 99xx -> 10001)
        string bigger = makePalindromic(to_string((orgVal / scale) * scale + scale));
        
        long long smallerVal = stoll(smaller);
        if (diff == 0 || abs(orgVal - smallerVal) <= diff) {
            res = smaller;
            diff = abs(orgVal - smallerVal);
        }
        
        long long biggerVal = stoll(bigger);
        if (abs(orgVal - biggerVal) < diff)
            res = bigger;
        
        return res;
    }
};

class AutocompleteSystem {
private:
    struct TrieNode {
        int time;
        unordered_map<char, TrieNode*> next;
        TrieNode() {
            time = 0;
        }
    };
    
    TrieNode* root;
    TrieNode* cur;
    string sentence;
    
    struct Compare {
        bool operator() (pair<string, int>& p1, pair<string, int>& p2){
            return p1.second == p2.second ? p1.first < p2.first : p1.second > p2.second;
        }
    };
    priority_queue<pair<string, int>, vector<pair<string, int>>, Compare> pq;
    
    void buildTrie(string s, int time) {
        TrieNode* node = root;
        for (char c : s) {
            if (!node -> next[c]) {
                node -> next[c] = new TrieNode();
            }
            node = node -> next[c];
        }
        node -> time += time;
    }
    
    void dfs(string& s, TrieNode* node) {
        if (node -> time) {
            pq.push({s, node -> time});
            while (pq.size() > 3) {
                pq.pop();
            }
        }
        
        for (auto& nex : node -> next) {
            s.push_back(nex.first);
            dfs(s, nex.second);
            s.pop_back();
        }
    }
    
    void reset() {
        cur = root;
        sentence = "";
    }
public:
    AutocompleteSystem(vector<string> sentences, vector<int> times) {
        root = new TrieNode();
        reset();
        for (int i = 0; i < sentence.size(); i++) {
            buildTrie(sentences[i], times[i]);
        }
    }
    
    vector<string> input(char c) {
        if (c == '#') {
            buildTrie(sentence, 1);
            reset();
            return {};
        }
        
        sentence.push_back(c);
        cur = cur -> next[c];
        if (!cur) {
            cur = new TrieNode();
        }
        
        dfs(sentence, cur);
        vector<string> result;
        while (!pq.empty()) {
            result.push_back(pq.top().first);
            pq.pop();
        }
        reverse(result.begin(), result.end());
        return result;
    }
};

int main() {
    AutocompleteSystem autoC({"i love you","island","iroman","i love leetcode"}, {5,3,2,2});
    autoC.input('i');
    
    Solution s;
    vector<string> v({"ahjpjau","ja","ahbwzgqnuk","tnmlanowax"});
    vector<int> va({4,5,8,2});
    vector<int> vb({3,2});
    vector<string> v2({"a","cd"});
    vector<char> chars({'a','a','a','a','a','b','b','c'});
    
    vector<vector<int>> matrix1({{1,2}, {0}, {0}});
    vector<vector<char>> matrix2({
        {'1','1','1','1','1','1','1','1'},
        {'1','1','1','1','1','1','1','0'},
        {'1','1','1','1','1','1','1','0'},
        {'1','1','1','1','1','0','0','0'},
        {'0','1','1','1','1','0','0','0'}
    });
    
    vector<pair<int, int>> fuxk;
    fuxk.push_back(make_pair(0,1));
    fuxk.push_back(make_pair(0,2));
    //fuxk.push_back(make_pair(1,3));
    //fuxk.push_back(make_pair(0,4));
    //fuxk.push_back(make_pair(5,4));
    //fuxk.push_back(make_pair(6,4));
    //fuxk.push_back(make_pair(6,7));
    
    /*Node* n1 = new Node(3, nullptr);
    Node* n2 = new Node(5, nullptr);
    Node* n3 = new Node(1, nullptr);
    n1 -> next = n2;
    n2 -> next = n3;
    n3 -> next = n1;*/
    
    cout << s.nearestPalindromic("1001") << endl;
    return 0;
}
