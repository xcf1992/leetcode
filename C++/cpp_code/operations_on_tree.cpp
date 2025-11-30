/*
https://leetcode.com/problems/operations-on-tree/description/?envType=problem-list-v2&envId=tree
1993. Operations on Tree

You are given a tree with n nodes numbered from 0 to n - 1 in the form of a parent array parent where parent[i] is the
parent of the ith node. The root of the tree is node 0, so parent[0] = -1 since it has no parent. You want to design a
data structure that allows users to lock, unlock, and upgrade nodes in the tree.

The data structure should support the following functions:

Lock: Locks the given node for the given user and prevents other users from locking the same node. You may only lock a
node using this function if the node is unlocked. Unlock: Unlocks the given node for the given user. You may only unlock
a node using this function if it is currently locked by the same user. Upgrade: Locks the given node for the given user
and unlocks all of its descendants regardless of who locked it. You may only upgrade a node if all 3 conditions are
true: The node is unlocked, It has at least one locked descendant (by any user), and It does not have any locked
ancestors. Implement the LockingTree class:

LockingTree(int[] parent) initializes the data structure with the parent array.
lock(int num, int user) returns true if it is possible for the user with id user to lock the node num, or false
otherwise. If it is possible, the node num will become locked by the user with id user. unlock(int num, int user)
returns true if it is possible for the user with id user to unlock the node num, or false otherwise. If it is possible,
the node num will become unlocked. upgrade(int num, int user) returns true if it is possible for the user with id user
to upgrade the node num, or false otherwise. If it is possible, the node num will be upgraded.


Example 1:


Input
["LockingTree", "lock", "unlock", "unlock", "lock", "upgrade", "lock"]
[[[-1, 0, 0, 1, 1, 2, 2]], [2, 2], [2, 3], [2, 2], [4, 5], [0, 1], [0, 1]]
Output
[null, true, false, true, true, true, false]

Explanation
LockingTree lockingTree = new LockingTree([-1, 0, 0, 1, 1, 2, 2]);
lockingTree.lock(2, 2);    // return true because node 2 is unlocked.
                           // Node 2 will now be locked by user 2.
lockingTree.unlock(2, 3);  // return false because user 3 cannot unlock a node locked by user 2.
lockingTree.unlock(2, 2);  // return true because node 2 was previously locked by user 2.
                           // Node 2 will now be unlocked.
lockingTree.lock(4, 5);    // return true because node 4 is unlocked.
                           // Node 4 will now be locked by user 5.
lockingTree.upgrade(0, 1); // return true because node 0 is unlocked and has at least one locked descendant (node 4).
                           // Node 0 will now be locked by user 1 and node 4 will now be unlocked.
lockingTree.lock(0, 1);    // return false because node 0 is already locked.


Constraints:

n == parent.length
2 <= n <= 2000
0 <= parent[i] <= n - 1 for i != 0
parent[0] == -1
0 <= num <= n - 1
1 <= user <= 104
parent represents a valid tree.
At most 2000 calls in total will be made to lock, unlock, and upgrade.
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
#include <climits>
#include <map>
using namespace std;

class LockingTree {
private:
    int n;
    unordered_map<int, vector<int>> children;
    vector<vector<int>> node;

public:
    LockingTree(vector<int>& parent) {
        n = parent.size();
        node.resize(n, vector<int>(2, -1));

        node[0][0] = -1;  // the root
        for (int i = 0; i < n; i++) {
            node[i][0] = parent[i];
            children[parent[i]].push_back(i);
        }
    }

    bool lock(int num, int user) {
        if (node[num][1] != -1) {
            return false;
        }
        node[num][1] = user;
        return true;
    }

    bool unlock(int num, int user) {
        if (node[num][1] != user) {
            return false;
        }
        node[num][1] = -1;
        return true;
    }

    bool upgrade(int num, int user) {
        if (node[num][1] != -1) {
            return false;
        }

        bool child_locked = false;
        check_children_locked(num, child_locked);
        if (!child_locked) {
            return false;
        }

        if (check_parent_locked(node[num][0])) {
            return false;
        }

        unlock_children(num);
        node[num][1] = user;
        return true;
    }

private:
    void check_children_locked(int cur, bool& locked) {
        if (children.find(cur) == children.end() || children[cur].size() == 0) {
            return;
        }

        for (int& child : children[cur]) {
            if (node[child][1] != -1) {
                locked = true;
                return;
            }
            check_children_locked(child, locked);
        }
    }

    bool check_parent_locked(int cur) {
        if (cur == -1) {
            return false;
        }

        if (node[cur][1] != -1) {
            return true;
        }

        return check_parent_locked(node[cur][0]);
    }

    void unlock_children(int cur) {
        if (children.find(cur) == children.end() || children[cur].size() == 0) {
            return;
        }

        for (int& child : children[cur]) {
            node[child][1] = -1;
            unlock_children(child);
        }
    }
};

/**
 * Your LockingTree object will be instantiated and called as such:
 * LockingTree* obj = new LockingTree(parent);
 * bool param_1 = obj->lock(num,user);
 * bool param_2 = obj->unlock(num,user);
 * bool param_3 = obj->upgrade(num,user);
 */