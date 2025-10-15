/*
421. Maximum XOR of Two Numbers in an Array
https://leetcode.com/problems/maximum-xor-of-two-numbers-in-an-array/

Given a non-empty array of numbers, a0, a1, a2, … , an-1, where 0 ≤ ai < 231.
Find the maximum result of ai XOR aj, where 0 ≤ i, j < n.
Could you do this in O(n) runtime?

Example:
Input: [3, 10, 5, 25, 2, 8]
Output: 28
Explanation: The maximum result is 5 ^ 25 = 28.
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
using namespace std;
/*
https://leetcode.com/problems/maximum-xor-of-two-numbers-in-an-array/discuss/130427/()-92
因为二进制元素只有0,1。考虑使用二叉树来构建前缀树。

根节点为符号位0
从高位到低位依次构建
左子树为1节点，又子树为0节点
[3,10,5,25,2,8] 按照以上规则构建如下图（省略高位0）

那么这颗树包含了数组中所有的数字，从根节点到叶子节点的一条路径表示数组中的一个十进制数的二进制编码。

找最大异或值
对于25 (0000 0000 0000 0000 0000 0000 0001 1001) 而言，从第31-6位（都是正数，不考虑符号位），都为0,，且数组中的数字31-6位都为0，因此最大异或结果31-6位只能为0。
当前使得异或结果最大的数x为0000 0000 0000 0000 0000 0000 000? ????
当前指针curNode指向第图中根节点。
从第5位开始：
5 1 x的第5位为0，则结果最大。应选择右分支，curNode = curNode->right
4 1 x的第4位为0，则结果最大。应选择右分支，curNode = curNode->right
3 0 x的第3位为1，则结果最大。应选择左分支，curNode = curNode->left
2 0 x的第2位为1，则结果最大。应选择左分支，但树中左分支为null，只能选择右分支curNode = curNode->right 于是x的第2位为0。
1 1 x的第1位为0，则结果最大。应选择右分支，但树中右分支为null，只能选择左分支curNode = curNode->left 于是x的第1位为1。
找到的x为5（00101）。
*/
struct TrieNode {
    int val;
    TrieNode* left;
    TrieNode* right;
    TrieNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

class Solution {
private:
    void insert(TrieNode* root, int num) {
        TrieNode* cur = root;
        for (int i = 31; i >= 0; --i) {
            int bit = num & (1 << i);
            if (bit == 0) {
                if (cur -> right == nullptr) {
                    cur -> right = new TrieNode(0);
                }
                cur = cur -> right;
            }
            else {
                if (cur -> left == nullptr) {
                    cur -> left = new TrieNode(1);
                }
                cur = cur -> left;
            }
        }
    }

    /*
    * we set the return value bit by bit from the most significant bit to the least
    * for each bit if we can find a number with different bit value of cur num,
    * we set that bit to 1 of return value
    * otherwise we set it to be 0
    * and we will move curNode accordingly
    */
    int find(TrieNode* root, int num) {
        TrieNode* curNode = root;
        int curValue = 0;
        for (int i = 31; i >= 0; --i) {
            int bit = num & (1 << i);
            if (curNode -> left and curNode -> right) {
                if (bit == 0) {
                    curNode = curNode -> left;
                }
                else {
                    curNode = curNode -> right;
                }
            }
            else {
                curNode = curNode -> left ? curNode -> left : curNode -> right;
            }
            curValue |= bit ^ (curNode -> val << i);
        }
        return curValue;
    }
public:
    int findMaximumXOR(vector<int>& nums) {
        TrieNode* root = new TrieNode(0);
        for (int num : nums) {
            insert(root, num);
        }

        int result = 0;
        for (int num : nums) {
            result = max(result, find(root, num));
        }
        return result;
    }
};

class Solution1 {
public:
    int findMaximumXOR(vector<int>& nums) {
        int result = 0;
        int mask = 0;
        for (int i = 31; i >= 0; i--) {
            unordered_set<int> values;
            mask |= (1 << i);
            for (int num : nums) {
                values.insert(mask & num);
            }

            int temp = result | (1 << i);
            for (int value : values) {
                if (values.find(temp ^ value) != values.end()) {
                    result = temp;
                    break;
                }
            }
        }
        return result;
    }
};
