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

class ValidWordAbbr {
private:
    unordered_set<string> abbreviation;
public:
    ValidWordAbbr(vector<string> dictionary) {
        for (string word : dictionary) {
            if (word.size() <= 2) {
                abbreviation.insert(word);
            }
            else {
                abbreviation.insert(string(1, word.front()) + to_string(word.size() - 2) + string(1, word.back()));
            }
        }
    }
    
    bool isUnique(string word) {
        return abbreviation.find(word) != abbreviation.end();
    }
};


int main() {
    //Solution s;
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
    
    //cout << s.sequenceReconstruction({5,3,2,4,1}, {{5,3,2,4}, {4,1}, {1}, {3}, {2, 4}, {1,1000000000}}) << endl;
    ValidWordAbbr vadddd({"ValidWordAbbr","isUnique","isUnique","isUnique","isUnique"});
    cout << vadddd.isUnique("make");
    return 0;
}
