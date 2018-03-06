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

class MaxStack1 {
    stack<int> elements;
    stack<int> maxElements;
public:
    /** initialize your data structure here. */
    MaxStack1() {
        
    }
    
    void push(int x) {
        elements.push(x);
        if (maxElements.empty() || x >= maxElements.top()) {
            maxElements.push(x);
        }
        else {
            maxElements.push(maxElements.top());
        }
    }
    
    int pop() {
        int result = elements.top();
        elements.pop();
        maxElements.pop();
        return result;
    }
    
    int top() {
        return elements.top();
    }
    
    int peekMax() {
        return maxElements.top();
    }
    
    int popMax() {
        int result = maxElements.top();
        elements.pop();
        maxElements.pop();
        return result;
    }
};

int main() {
    //Solution s;
    vector<string> v({"ABD","BCE","DEF","FFF"});
    vector<int> v2({2,2,2,2,2});
    vector<char> chars({'a','a','a','a','a','b','b','c'});
    vector<vector<int>> matrix({{9,9,4},{6,7,8},{2,1,1}});
    
    MaxStack1 stack;
    stack.push(5);
    stack.push(1);
    stack.popMax();
    stack.peekMax();
}
