/*
https://leetcode.com/problems/build-binary-expression-tree-from-infix-expression/
1597. Build Binary Expression Tree From Infix Expression

A binary expression tree is a kind of binary tree used to represent arithmetic expressions. Each node of a binary
expression tree has either zero or two children. Leaf nodes (nodes with 0 children) correspond to operands (numbers),
and internal nodes (nodes with 2 children) correspond to the operators '+' (addition), '-' (subtraction), '*'
(multiplication), and '/' (division).

For each internal node with operator o, the infix expression it represents is (A o B), where A is the expression the
left subtree represents and B is the expression the right subtree represents.

You are given a string s, an infix expression containing operands, the operators described above, and parentheses '('
and ')'.

Return any valid binary expression tree, whose in-order traversal reproduces s after omitting the parenthesis from it.

Please note that order of operations applies in s. That is, expressions in parentheses are evaluated first, and
multiplication and division happen before addition and subtraction.

Operands must also appear in the same order in both s and the in-order traversal of the tree.



Example 1:


Input: s = "3*4-2*5"
Output: [-,*,*,3,4,2,5]
Explanation: The tree above is the only valid tree whose inorder traversal produces s.
Example 2:


Input: s = "2-3/(5*2)+1"
Output: [+,-,1,2,/,null,null,null,null,3,*,null,null,5,2]
Explanation: The inorder traversal of the tree above is 2-3/5*2+1 which is the same as s without the parenthesis. The
tree also produces the correct result and its operands are in the same order as they appear in s. The tree below is also
a valid binary expression tree with the same inorder traversal as s, but it not a valid answer because it does not
evaluate to the same value.

The third tree below is also not valid. Although it produces the same result and is equivalent to the above trees, its
inorder traversal does not produce s and its operands are not in the same order as s.

Example 3:

Input: s = "1+2+3+4+5"
Output: [+,+,5,+,4,null,null,+,3,null,null,1,2]
Explanation: The tree [+,+,5,+,+,null,null,1,2,3,4] is also one of many other valid trees.


Constraints:

1 <= s.length <= 100
s consists of digits and the characters '(', ')', '+', '-', '*', and '/'.
Operands in s are exactly 1 digit.
It is guaranteed that s is a valid expression.
*/
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

struct Node {
    char val;
    Node* left;
    Node* right;

    Node() : val(' '), left(nullptr), right(nullptr) {
    }

    Node(char x) : val(x), left(nullptr), right(nullptr) {
    }

    Node(char x, Node* left, Node* right) : val(x), left(left), right(right) {
    }
};

// https://runestone.academy/ns/books/published/pythonds/BasicDS/InfixPrefixandPostfixExpressions.html
class Solution {
private:
    void infix_to_postfix(vector<char>& infix, vector<char>& postfix) {
        unordered_map<char, int> prec;
        prec['*'] = 3;
        prec['/'] = 3;
        prec['+'] = 2;
        prec['-'] = 2;
        prec['('] = 1;
        stack<char> op_stk;
        for (char& c : infix) {
            if (isdigit(c)) {
                postfix.push_back(c);
            } else if (c == '(') {
                op_stk.push(c);
            } else if (c == ')') {
                char op = op_stk.top();
                while (op != '(') {
                    postfix.push_back(op);
                    op_stk.pop();
                    op = op_stk.top();
                }
                op_stk.pop();
            } else {
                while (!op_stk.empty() && prec[op_stk.top()] >= prec[c]) {
                    postfix.push_back(op_stk.top());
                    op_stk.pop();
                }
                op_stk.push(c);
            }
        }

        while (!op_stk.empty()) {
            postfix.push_back(op_stk.top());
            op_stk.pop();
        }
    }

    Node* build_tree(vector<char>& post_fix) {
        stack<Node*> stk;
        for (char& c : post_fix) {
            if (isdigit(c)) {
                stk.push(new Node(c));
                continue;
            }

            Node* r = stk.top();
            stk.pop();
            Node* l = stk.top();
            stk.pop();
            stk.push(new Node(c, l, r));
        }
        return stk.top();
    }

public:
    Node* expTree(string s) {
        vector<char> infix;
        for (char c : s) {
            infix.push_back(c);
        }

        vector<char> postfix;
        infix_to_postfix(infix, postfix);
        return build_tree(postfix);
    }
};
