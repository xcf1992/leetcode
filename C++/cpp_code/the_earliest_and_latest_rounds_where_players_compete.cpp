/*
https://leetcode.com/problems/the-earliest-and-latest-rounds-where-players-compete/description/
1900. The Earliest and Latest Rounds Where Players Compete

There is a tournament where n players are participating. The players are standing in a single row and are numbered from
1 to n based on their initial standing position (player 1 is the first player in the row, player 2 is the second player
in the row, etc.).

The tournament consists of multiple rounds (starting from round number 1). In each round, the ith player from the front
of the row competes against the ith player from the end of the row, and the winner advances to the next round. When the
number of players is odd for the current round, the player in the middle automatically advances to the next round.

For example, if the row consists of players 1, 2, 4, 6, 7
Player 1 competes against player 7.
Player 2 competes against player 6.
Player 4 automatically advances to the next round.
After each round is over, the winners are lined back up in the row based on the original ordering assigned to them
initially (ascending order).

The players numbered firstPlayer and secondPlayer are the best in the tournament. They can win against any other player
before they compete against each other. If any two other players compete against each other, either of them might win,
and thus you may choose the outcome of this round.

Given the integers n, firstPlayer, and secondPlayer, return an integer array containing two values, the earliest
possible round number and the latest possible round number in which these two players will compete against each other,
respectively.



Example 1:

Input: n = 11, firstPlayer = 2, secondPlayer = 4
Output: [3,4]
Explanation:
One possible scenario which leads to the earliest round number:
First round: 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
Second round: 2, 3, 4, 5, 6, 11
Third round: 2, 3, 4
One possible scenario which leads to the latest round number:
First round: 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
Second round: 1, 2, 3, 4, 5, 6
Third round: 1, 2, 4
Fourth round: 2, 4
Example 2:

Input: n = 5, firstPlayer = 1, secondPlayer = 5
Output: [1,1]
Explanation: The players numbered 1 and 5 compete in the first round.
There is no way to make them compete in any other round.


Constraints:

2 <= n <= 28
1 <= firstPlayer < secondPlayer <= n
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
/*
Intuition
I thought: when do two players meet in a tournament like this?

Since players face the one mirrored from the other side (i.e., first vs last, second vs second last, etc.), I realized
that if firstPlayer + secondPlayer == n + 1, then they meet in the first round — so we just return {1, 1}.

If not, we simulate further rounds recursively. But instead of trying every possible combination, I can reduce the
problem by compressing positions of the remaining players in the next round and checking all possible positions the
players could move to.

This recursive structure helps me explore all scenarios efficiently and find both the earliest and latest rounds they
might meet.

Approach
Start with the given positions firstPlayer and secondPlayer.

If they are mirrored (like 2 vs 9 in 10 players), return {1, 1}.

Otherwise:

Compress the players to the next round (only winners go).
Mirror the problem if the players are closer to the right than the left (for symmetry).
Use recursion to simulate all possible positions they could end up in during the next round.

From all those outcomes, find the minimum and maximum rounds they meet.

Return {minRound, maxRound}.

Complexity
Time Complexity: O(n³)
We recurse on reducing n, and the nested loops try all combinations of positioning, making the solution efficient up to
n = 20.

Space Complexity: O(1)
We only use function stack memory (no memoization or large structures).
-=-=-
💡 Intuition
Imagine there's a single-elimination tournament where players face off in pairs from opposite ends: first vs last,
second vs second-last, etc. The winners move to the next round, and this continues until there's one winner. Among all
these players, firstPlayer and secondPlayer are the strongest — they can beat everyone else. The only uncertainty in
this setup comes from how other weaker players play — since they can win or lose arbitrarily, we must consider all
possible match outcomes for them. Our goal is to find out the earliest and latest round where firstPlayer and
secondPlayer can potentially face each other. To solve this, we use recursive simulation: we simulate all the ways the
two players can progress through rounds given they never lose, and for each configuration, we update the earliest and
latest possible round when they might meet. We reduce the problem to smaller tournaments each time by calculating new
positions in the next round, depending on how many matches happened before. This continues until the two players are
scheduled to meet, at which point we return that round. We also exploit symmetry to reduce unnecessary work — always
keeping the smaller-numbered player on the left side.

📜🔢 Approach
Step 1 Understand the Game Format

This is a single-elimination tournament.
In each round
The first player competes with last, second with second-last
If there's an odd number of players
The middle player automatically advances.
The players firstPlayer and secondPlayer are the strongest
They never lose unless they face each other.
Step 2 Handle Base Case — Do They Meet in This Round?

In every round
check if firstPlayer and secondPlayer are facing each other.
They face each other if firstPlayer + secondPlayer == n + 1
They're paired from opposite ends.
If yes:
return {1, 1}
They meet in round 1 — both earliest and latest.
Step 3 Normalize the Players’ Position

To make things easier, always keep smaller-numbered player on left.
So set
p1 = min(firstPlayer, secondPlayer)
p2 = max(firstPlayer, secondPlayer).
Step 4 Divide Players into Zones

Now, imagine the current lineup of players:
a = number of players before p1
b = number of players between p1 & p2
c = number of players after p2
Step 5 Simulate All Valid Matchups

Since all players,
except p1 and p2 can win or lose arbitrarily, you simulate all combinations of players who can advance from zones a, b,
c. For each configuration of survivors from current, recursively calculate: What round p1 and p2 will meet in the next
reduced round tournament size becomes (n + 1) / 2. You map p1 and p2's new positions in the next round based on how many
other matches happen before them. Step 6 Track the Minimum and Maximum Rounds

In each recursive simulation:
Keep track of the minimum round, earliest time they could meet.
Also track maximum round, latest time they could possibly meet.
Add +1 to each recursive result, since you move one round deeper.
Step 7 Return the Final Answer

After exploring all combinations
Return {minRound, maxRound}
the earliest & latest round two strong players could face off.
*/
class Solution {
public:
    vector<int> earliestAndLatest(int n, int firstPlayer, int secondPlayer) {
        int left = min(firstPlayer, secondPlayer);
        int right = max(firstPlayer, secondPlayer);
        if (left + right == n + 1) {
            return vector<int>{1, 1};
        }

        if (n == 3 || n == 4) {
            return vector<int>{2, 2};
        }

        // Mirror for symmetry if closer to right
        if (left - 1 > n - right) {
            int temp = n + 1 - left;
            left = n + 1 - right;
            right = temp;
        }

        int next_round_cnt = (n + 1) / 2;
        int min_cnt = INT_MAX;
        int max_cnt = INT_MIN;

        if (right * 2 <= n + 1) {  // two people in the same half
            int prev_left = left - 1;
            int between_left_right = right - left - 1;
            for (int i = 0; i <= prev_left; i++) {
                // i the number of people win before left
                for (int j = 0; j <= between_left_right; j++) {
                    // j the number of people win between left and right
                    vector<int> next_round_rst = earliestAndLatest(next_round_cnt, i + 1, i + j + 2);
                    min_cnt = min(min_cnt, next_round_rst[0] + 1);
                    max_cnt = max(max_cnt, next_round_rst[1] + 1);
                }
            }
        } else {
            int prev_left = left - 1;
            int mirrored_right = n + 1 - right;
            int between_left_mirrored_right = mirrored_right - left - 1;
            int inner_gap = right - mirrored_right - 1;
            for (int i = 0; i <= prev_left; i++) {
                for (int j = 0; j <= between_left_mirrored_right; j++) {
                    vector<int> next_round_rst =
                            earliestAndLatest(next_round_cnt, i + 1, i + 1 + j + (inner_gap + 1) / 2 + 1);
                    min_cnt = min(min_cnt, next_round_rst[0] + 1);
                    max_cnt = max(max_cnt, next_round_rst[1] + 1);
                }
            }
        }
        return {min_cnt, max_cnt};
    }
};
/*
1. What does "Two Users in the Same Half" mean?In this problem, the tournament works by "folding" the array of players.
The first player plays the last, the second plays the second to last, and so on.Pairing Logic: If there are $N$ players,
player at index $k$ plays against player at index $N - k + 1$.The "Half" Line: Because of this pairing, the array is
effectively split into two halves.Left Half: Positions $1$ to $N/2$.Right Half: Positions $N/2 + 1$ to $N$.If both your
players (let's call them $P1$ and $P2$) are in the Left Half, it means neither of them is playing against the other in
this round.$P1$ is playing against someone from the far right.$P2$ is playing against someone else from the far right.

The Setup
Imagine the players are arranged like this in the current round:

[ Region A ] P1 [ Region B ] P2 ...

Region A (preLeft): The group of players standing before P1.

Region B (midGap): The group of players standing between P1 and P2.

For P1 and P2 to continue to the next round, they must win their matches (we assume they win because we are tracking
their journey). However, for the players in Region A and Region B, we don't know who wins. Some might win, some might
lose.

The Variables in the Loop
i: The number of players from Region A who win and advance.

j: The number of players from Region B who win and advance.

-=-=

2. Explanation of Case 2: Players in Opposite HalvesThis block handles the scenario where Player 1 is Left and Player 2
is Right, but they are not playing each other yet.The Geometry of the FoldLet's visualize the array and the "Gaps"
between the players.Assume $N=8$, Player 1 is at 2, Player 2 is at 6.P1 is Left.P2 is Right.Mirrored Position: P2 is at
6, so his opponent is at position $3$ (calculated as $N + 1 - P2$).The array is divided into three distinct regions
(Gaps) based on the fold:Region A (preLeft): Players before P1.Region B (midGap): Players between P1 and P2's opponent
(the Mirror).Region C (innerGap): Players strictly inside the fold (between P2's opponent and P2).Visualizing the
GroupsPlaintextIndices:  1      2      3      4      5      6      7      8 Players: [A]   [P1]   [B]    [ C ]  [ C ]
[P2]   [Opp]  [Opp] Matches: 1 plays 8  (Region A vs Region A's opponents) 2 plays 7  (P1 vs P1's opponent) 3 plays 6
(Region B vs Region B's opponents... WAIT, 3 is P2's Mirror!) Correction on the visual:P2 is at 6. His opponent (Mirror)
is at 3.Region A (preLeft): Index 1.Region B (midGap): Indices between P1(2) and Mirror(3). (Empty in this case).Region
C (innerGap): Indices strictly between Mirror(3) and P2(6). Indices 4 and 5.The Logic of the Next Round PositionsWe need
to calculate where P1 and P2 land in the next round (which will be size 4).New P1 Position (pos1):P1's new rank depends
only on how many people before him survive.Loop i: The number of survivors from Region A.pos1 = i + 1New P2 Position
(pos2):P2 is essentially moving from the Right side to the Left side (because the array folds). His new position is
determined by how many "stacks" of players end up ahead of him.Stack 1: Survivors from Region A (i).Stack 2: P1 (Takes 1
slot).Stack 3: Survivors from Region B (j).Stack 4: Survivors from Region C (innerGap).Note: Players in the innerGap
(the very center) play each other. Therefore, exactly half of them advance. We don't need a loop for them; the count is
fixed at (innerGap + 1) / 2.The formula used in the code is:pos2 = i + j + 1 + (innerGap + 1) / 2 + 1i = Survivors
before P1.j = Survivors between P1 and P2's mirror.1 = Space for P1.(innerGap + 1) / 2 = The winners of the "inner fold"
matches.1 = Space for P2.(Note: Depending on whether P1 is "Outer" (closer to edge) or "Inner" (closer to center), P2
might end up before or after the Inner Gap winners. The code's formula assumes a specific fold order usually consistent
with standard tournament indexing).
 */