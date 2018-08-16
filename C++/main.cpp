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

class SnakeGame {
private:
    vector<int> snake;
    unordered_set<int> visited;
    int W;
    int H;
    int score;
    vector<pair<int, int>> f;
public:
    /** Initialize your data structure here.
     @param width - screen width
     @param height - screen height
     @param food - A list of food positions
     E.g food = [[1,1], [1,0]] means the first food is positioned at [1,1], the second is at [1,0]. */
    SnakeGame(int width, int height, vector<pair<int, int>> food) {
        W = width;
        H = height;
        score = 0;
        snake.insert(snake.begin(), 0);
        visited.insert(0);
        f = food;
    }
    
    /** Moves the snake.
     @param direction - 'U' = Up, 'L' = Left, 'R' = Right, 'D' = Down
     @return The game's score after the move. Return -1 if game over.
     Game over when snake crosses the screen boundary or bites its body. */
    int move(string direction) {
        int curH = snake.front() / W;
        int curW = snake.front() % W;
        
        if (direction == "U") {
            curH -= 1;
        }
        else if (direction == "D") {
            curH += 1;
        }
        else if (direction == "L") {
            curW -= 1;
        }
        else {
            curW += 1;
        }
        
        if (curW < 0 || curH < 0 || curW >= W || curH >= H) {
            return -1;
        }
        
        int tail = snake.back();
        visited.erase(snake.back());
        snake.pop_back();
        int next = curH * W + curW;
        if (visited.find(next) != visited.end()) {
            return -1;
        }

        snake.insert(snake.begin(), next);
        visited.insert(next);
        if (score < f.size() && curH == f[score].first && curW == f[score].second) {
            score += 1;
            snake.push_back(tail);
            visited.insert(tail);
        }
        return score;
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
    pair<int, int> f1 = make_pair(0, 1);
    pair<int, int> f2 = make_pair(0, 2);
    pair<int, int> f3 = make_pair(1, 2);
    pair<int, int> f4 = make_pair(2, 2);
    pair<int, int> f5 = make_pair(2, 1);
    pair<int, int> f6 = make_pair(2, 0);
    pair<int, int> f7 = make_pair(1, 0);
    SnakeGame s(3, 3, {f1, f2, f3, f4, f5, f6, f7});
    s.move("R");
    s.move("R");
    s.move("D");
    s.move("D");
    s.move("L");
    s.move("L");
    s.move("U");
    s.move("U");
    s.move("R");
    s.move("R");
    s.move("D");
    s.move("D");
    s.move("L");
    s.move("L");
    s.move("U");
    s.move("R");
    s.move("U");
    s.move("L");
    s.move("D");
    //cout << s.insert(n1, 0) << endl;
    return 0;
}
