/*
 558. Quad Tree Intersection
 A quadtree is a tree data in which each internal node has exactly four children:
 topLeft, topRight, bottomLeft and bottomRight.
 Quad trees are often used to partition a two-dimensional space by recursively subdividing it into four quadrants or
 regions.

 We want to store True/False information in our quad tree.
 The quad tree is used to represent a N * N boolean grid.
 For each node, it will be subdivided into four children nodes until the values in the region it represents are all the
 same. Each node has another two boolean attributes : isLeaf and val. isLeaf is true if and only if the node is a leaf
 node. The val attribute for a leaf node contains the value of the region it represents.

 For example, below are two quad trees A and B:

 A:
 +-------+-------+   T: true
 |       |       |   F: false
 |   T   |   T   |
 |       |       |
 +-------+-------+
 |       |       |
 |   F   |   F   |
 |       |       |
 +-------+-------+
 topLeft: T
 topRight: T
 bottomLeft: F
 bottomRight: F

 B:
 +-------+---+---+
 |       | F | F |
 |   T   +---+---+
 |       | T | T |
 +-------+---+---+
 |       |       |
 |   T   |   F   |
 |       |       |
 +-------+-------+
 topLeft: T
 topRight:
 topLeft: F
 topRight: F
 bottomLeft: T
 bottomRight: T
 bottomLeft: T
 bottomRight: F


 Your task is to implement a function that will take two quadtrees and return a quadtree that represents the logical OR
 (or union) of the two trees.

 A:                 B:                 C (A or B):
 +-------+-------+  +-------+---+---+  +-------+-------+
 |       |       |  |       | F | F |  |       |       |
 |   T   |   T   |  |  T    +---+---+  |   T   |   T   |
 |       |       |  |       | T | T |  |       |       |
 +-------+-------+  +-------+---+---+  +-------+-------+
 |       |       |  |       |       |  |       |       |
 |   F   |   F   |  |   T   |   F   |  |   T   |   F   |
 |       |       |  |       |       |  |       |       |
 +-------+-------+  +-------+-------+  +-------+-------+
 Note:

 N is guaranteened to be a power of 2.
 If you want to know more about the quad tree, you can refer to its wiki.
 The logic OR operation is define as this: "A or B" is true if A is true, or if B is true, or if both A and B are true.
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>
#include <set>
using namespace std;

class Node {
public:
    bool val;
    bool isLeaf;
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;

    Node() {
    }

    Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight, Node* _bottomLeft, Node* _bottomRight) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};

class Solution {
private:
    bool isLeaf(Node* node) {
        Node* topLeft = node->topLeft;
        Node* topRight = node->topRight;
        Node* botLeft = node->bottomLeft;
        Node* botRight = node->bottomRight;

        if (topLeft == nullptr and topRight == nullptr and botLeft == nullptr and botRight == nullptr) {
            return true;
        }

        if (topLeft->isLeaf and topRight->isLeaf and botRight->isLeaf and botLeft->isLeaf and
            ((topLeft->val and topRight->val and botLeft->val and botRight->val) or
             !(topLeft->val or topRight->val or botLeft->val or botRight->val))) {
            return true;
        }
        return false;
    }

public:
    Node* intersect(Node* quadTree1, Node* quadTree2) {
        if (quadTree1 == nullptr or quadTree1 == nullptr) {
            return quadTree1 == nullptr ? quadTree2 : quadTree1;
        }

        if (quadTree1->isLeaf) {
            return quadTree1->val ? quadTree1 : quadTree2;
        }

        if (quadTree2->isLeaf) {
            return quadTree2->val ? quadTree2 : quadTree1;
        }

        quadTree1->topLeft = intersect(quadTree1->topLeft, quadTree2->topLeft);
        quadTree1->topRight = intersect(quadTree1->topRight, quadTree2->topRight);
        quadTree1->bottomLeft = intersect(quadTree1->bottomLeft, quadTree2->bottomLeft);
        quadTree1->bottomRight = intersect(quadTree1->bottomRight, quadTree2->bottomRight);

        if (isLeaf(quadTree1)) {
            quadTree1->isLeaf = true;
            quadTree1->val = quadTree1->topLeft->val;
        }
        return quadTree1;
    }
};