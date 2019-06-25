/*
 913. Cat and Mouse
 A game on an undirected graph is played by two players, Mouse and Cat, who alternate turns.

 The graph is given as follows: graph[a] is a list of all nodes b such that ab is an edge of the graph.

 Mouse starts at node 1 and goes first, Cat starts at node 2 and goes second, and there is a Hole at node 0.

 During each player's turn, they must travel along one edge of the graph that meets where they are.  For example, if the Mouse is at node 1, it must travel to any node in graph[1].

 Additionally, it is not allowed for the Cat to travel to the Hole (node 0.)

 Then, the game can end in 3 ways:

 If ever the Cat occupies the same node as the Mouse, the Cat wins.
 If ever the Mouse reaches the Hole, the Mouse wins.
 If ever a position is repeated (ie. the players are in the same position as a previous turn, and it is the same player's turn to move), the game is a draw.
 Given a graph, and assuming both players play optimally, return 1 if the game is won by Mouse, 2 if the game is won by Cat, and 0 if the game is a draw.



 Example 1:

 Input: [[2,5],[3],[0,4,5],[1,4,5],[2,3],[0,2,3]]
 Output: 0
 Explanation:
 4---3---1
 |   |
 2---5
 \ /
 0


 Note:

 3 <= graph.length <= 50
 It is guaranteed that graph[1] is non-empty.
 It is guaranteed that graph[2] contains a non-zero element.
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
#include <numeric>
using namespace std;

/*
 Intuition

 The state of the game can be represented as (m, c, t)
 where m is the location of the mouse,
 c is the location of the cat,
 and t is 1 if it is the mouse's move, else 2.

 Let's call these states nodes.
 These states form a directed graph: the player whose turn it is has various moves which can be considered as outgoing edges from this node to other nodes.

 Some of these nodes are already resolved:
 if the mouse is at the hole (m = 0), then the mouse wins;
 if the cat is where the mouse is (c = m), then the cat wins.

 Let's say that nodes will either be colored MOUSE, CAT, or DRAW depending on which player is assured victory.
 As in a standard minimax algorithm, the Mouse player will prefer MOUSE nodes first, DRAW nodes second, and CAT nodes last,
 and the Cat player prefers these nodes in the opposite order.

 Algorithm

 We will color each node marked DRAW according to the following rule.
 (We'll suppose the node has node.turn = Mouse: the other case is similar.)

 ("Immediate coloring"): If there is a child that is colored MOUSE, then this node will also be colored MOUSE.

 ("Eventual coloring"): If all children are colored CAT, then this node will also be colored CAT.

 We will repeatedly do this kind of coloring until no node satisfies the above conditions.
 To perform this coloring efficiently, we will use a queue and perform a bottom-up percolation:

 Enqueue any node initially colored (because the Mouse is at the Hole, or the Cat is at the Mouse.)

 For every node in the queue, for each parent of that node:
 Do an immediate coloring of parent if you can.

 If you can't, then decrement the side-count of the number of children marked DRAW.
 If it becomes zero, then do an "eventual coloring" of this parent.

 All parents that were colored in this manner get enqueued to the queue.

 Proof of Correctness

 Our proof is similar to a proof that minimax works.

 Say we cannot color any nodes any more, and say from any node colored CAT or MOUSE we need at most K moves to win.
 If say, some node marked DRAW is actually a win for Mouse,
 it must have been with >K moves.
 Then, a path along optimal play (that tries to prolong the loss as long as possible)
 must arrive at a node colored MOUSE (as eventually the Mouse reaches the Hole.)
 Thus, there must have been some transition DRAW -> MOUSE along this path.

 If this transition occurred at a node with node.turn = Mouse,
 then it breaks our immediate coloring rule.
 If it occured with node.turn = Cat,
 and all children of node have color MOUSE, then it breaks our eventual coloring rule.
 If some child has color CAT, then it breaks our immediate coloring rule.
 Thus, in this case node will have some child with DRAW,
 which breaks our optimal play assumption,
 as moving to this child ends the game in > K moves, whereas moving to the colored neighbor ends the game in <= K moves.

 Time Complexity: O(N^3) where NN is the number of nodes in the graph.
 There are O(N^2) states, and each state has an outdegree of NN, as there are at most NN different moves.
 Space Complexity: O(N^2)
 */
class Solution {
private:
    int DRAW = 0;
    int MOUSE = 1;
    int CAT = 2;

    vector<vector<int>> parents(vector<vector<int>>& graph, int mouse, int cat, int turn) {
        vector<vector<int>> next;
        // current turn is 2 which is cat, previouse is a mouse move lead to current node
        if (turn == 2) {
            // get all pos that a mouse can move to current position
            for (int m : graph[mouse]) {
                next.push_back({m, cat, 1});
            }
            return next;
        }

        // previous is a cat move
        for (int c : graph[cat]) {
            // cat cannot from hole 0
            if (c > 0) {
                next.push_back({mouse, c, 2});
            }
        }
        return next;
    }
public:
    int catMouseGame(vector<vector<int>>& graph) {
        int N = graph.size();
        // color: {mouse pos, cat pos, move} move = 1 means is now mosue move; 2 means is now cat move
        vector<vector<vector<int>>> color = vector<vector<vector<int>>>(50, vector<vector<int>>(50, vector<int>(3, 0)));
        // degree the number of neutral children of this current node
        vector<vector<vector<int>>> degree = vector<vector<vector<int>>>(50, vector<vector<int>>(50, vector<int>(3, 0)));

        for (int m = 0; m < N; m++) {
            for (int c = 0; c < N; c++) {
                degree[m][c][1] = graph[m].size();
                degree[m][c][2] = graph[c].size();
                for (int x : graph[c]) {
                    if (x == 0) {
                        // cat cannot move to hole 0, so 0 is not its child when it is cat's move
                        degree[m][c][2] -= 1;
                        break;
                    }
                }
            }
        }

        queue<vector<int>> q;
        for (int i = 0; i < N; i++) {
            for (int t = 1; t <= 2; t++) {
                // when mouse is at hole 0 is a mouse win
                color[0][i][t] = MOUSE;
                q.push({0, i, t, MOUSE});
                if (i > 0) {
                    // when mouse and cat are at the same position is a cat win
                    color[i][i][t] = CAT;
                    q.push({i, i, t, CAT});
                }
            }
        }

        while (!q.empty()) {
            vector<int> cur = q.front();
            q.pop();
            int i = cur[0]; // mouse
            int j = cur[1]; // cat
            int t = cur[2]; // turn
            int c = cur[3]; // who wins 1 mouse 2 cat
            for (vector<int>& parent : parents(graph, i, j, t)) {
                int i2 = parent[0]; // mouse
                int j2 = parent[1]; // cat
                int t2 = parent[2]; // turn
                //if this parent is not colored yet
                if (color[i2][j2][t2] == DRAW) {
                    // cause they will always do the optimal option, when there is a child is mouse win then if current move is mouse
                    // mouse will pick this move then cat will not vice versera
                    if (t2 == c) {
                        color[i2][j2][t2] = c;
                        q.push({i2, j2, t2, c});
                    }
                    else {
                        // cur node is not a win option for this parent, reduce one for possible win options
                        degree[i2][j2][t2]--;
                        if (degree[i2][j2][t2] == 0) {
                            // if no win option existed, mark this parent as fail
                            color[i2][j2][t2] = 3 - t2;
                            q.push({i2, j2, t2, 3 - t2});
                        }
                    }
                }
            }
        }
        return color[1][2][1];
    }
};
