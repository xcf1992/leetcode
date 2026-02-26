/*
https://www.hack2hire.com/companies/reddit/coding-questions/6941be40b9d646bec48c68cb/practice?questionId=6941be52b9d646bec48c68cc
Design Tennis Game

A tennis scoring system is needed to track a single game played between two players, A and B. Points are awarded one at
a time to a player, and the score must be tracked according to real tennis rules, including "deuce", "advantage", and
game-winning logic. Scores must be accessible in both numeric and standard tennis notation.

Implement the TennisGame class:

TennisGame() Initializes a new game. Both players start at 0 points, and there is no winner.
void pointTo(char player) Awards one point to the given player ('A' or 'B'). If the game has already finished (i.e.,
there is a winner), further calls to this method must have no effect. String getScore() Returns the current numeric
score as a string in the format "A:B", representing player A and B's points.

When both players have at least 3 points, and their scores are equal, the output must be clamped to "3:3" regardless of
the actual internal points. For example, internal scores of 4:4 or 5:5 must be reported as "3:3". char getWinner()
Returns 'A' or 'B' if that player has won the game, or '#' if no winner yet.

A player wins if they have at least 4 points and lead the opponent by at least 2 points.

Constraints:

All calls to pointTo use valid player values ('A' or 'B').
The game state is guaranteed to be valid per tennis rules.
0 ≤ both players' point totals throughout the game.
Example

Input:
["TennisGame", "getScore", "pointTo", "getScore", "pointTo", "getScore", "pointTo", "getScore", "pointTo", "getScore",
"getWinner", "pointTo", "getScore", "getWinner"]
[[], [], ['A'], [], ['B'], [], ['A'], [], ['A'], [], [], ['A'], [], []]

Output:
[null, "0:0", null, "1:0", null, "1:1", null, "2:1", null, "3:1", "#", null, "4:1", "A"]

Explanation:

TennisGame game = new TennisGame();
game.getScore(); // Return "0:0".
game.pointTo('A');
game.getScore(); // Return "1:0".
game.pointTo('B');
game.getScore(); // Return "1:1".
game.pointTo('A');
game.getScore(); // Return "2:1".
game.pointTo('A');
game.getScore(); // Return "3:1".
game.getWinner(); // Return "#", since no winner yet.
game.pointTo('A');
game.getScore(); // Return "4:1".
game.getWinner(); // Return "A".

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

class TennisGame1 {
private:
    int point_a_;
    int point_b_;
    bool finished_;
    char winner_;

public:
    TennisGame() {
        point_a_ = 0;
        point_b_ = 0;
        finished_ = false;
        winner_ = '#';
    }

    void pointTo(char player) {
        if (finished_) {
            return;
        }

        if (player == 'A') {
            point_a_ += 1;
            if (point_a_ >= 4 && point_a_ - point_b_ >= 2) {
                winner_ = player;
                finished_ = true;
            }
        } else {
            point_b_ += 1;
            if (point_b_ >= 4 && point_b_ - point_a_ >= 2) {
                winner_ = player;
                finished_ = true;
            }
        }

        if (point_a_ >= 3 && point_b_ >= 3 && point_a_ == point_b_) {
            point_a_ = 3;
            point_b_ = 3;
        }
    }

    string getScore() {
        if (point_a_ >= 3 && point_b_ >= 3 && point_a_ == point_b_) {
            return "3:3";
        }
        return to_string(point_a_) + ":" + to_string(point_b_);
    }

    char getWinner() {
        return winner_;
    }
};

/*Follow-up:
Extending the tennis scoring system, you are now required to model a tennis set composed of multiple games between two
players, 'A' and 'B'. The set follows a best of 5 rule: the first player to win 3 games wins the set.

Each game follows traditional tennis scoring rules as described in the previous question. Your implementation must
manage the flow of games within the set, track scores, and enforce the winning and termination conditions.

Implement the TennisSet class:

TennisSet() Initializes a new tennis set. Both players start with 0 game wins, and the first game is automatically
started.

void pointTo(char player) Adds one point to the current game for the given player ('A' or 'B').

If the current game ends, the winner's game count is incremented, and the next game is automatically started if neither
player has won the set yet. If the set is already finished, further calls to this method have no effect. String
getScore() Returns the current game score as a string in the format "scoreA:scoreB", using the same display rules as
described earlier. The score clamping rule remains in effect.

String getSetScore() Returns the number of games won by each player as a string in the format "gameA:gameB".

char getSetWinner() Returns 'A' or 'B' if a player has already won 3 games in the set, or '#' if the set is not
finished.

Constraints:

All calls to pointTo will use valid player values ('A' or 'B').
A set consists of at most 5 games.
Each individual game is managed using the TennisGame interface and rules.
1 ≤ number of method calls ≤ 10⁴.
Example

Input:
["TennisSet", "pointTo", "pointTo", "pointTo", "pointTo", "getSetScore", "getScore", "pointTo", "pointTo", "pointTo",
"pointTo", "pointTo", "getSetScore", "pointTo", "pointTo", "pointTo", "pointTo", "getSetScore", "getSetWinner"]
[[], ['A'], ['A'], ['A'], ['A'], [], [], ['A'], ['A'], ['B'], ['A'], ['A'], [], ['A'], ['A'], ['A'], ['A'], [], []]

Output:
[null, null, null, null, null, "1:0", "0:0", null, null, null, null, null, "2:0", null, null, null, null, "3:0", "A"]

Explanation:

TennisSet set = new TennisSet();
set.pointTo('A');
set.pointTo('A');
set.pointTo('A');
set.pointTo('A'); // Player A wins the first game.
set.getSetScore(); // Return "1:0" after Player A wins the first game.
set.getScore(); // Return "0:0" because a new game has started.
set.pointTo('A');
set.pointTo('A');
set.pointTo('B');
set.pointTo('A');
set.pointTo('A'); // Player A wins the second game.
set.getSetScore(); // Return "2:0".
set.pointTo('A');
set.pointTo('A');
set.pointTo('A');
set.pointTo('A'); // Player A wins the third game and the set.
set.getSetScore(); // Return "3:0".
set.getSetWinner(); // Return 'A'.
*/
class TennisSet {
private:
    int point_a_;
    int point_b_;
    bool finished_;
    char winner_;
    int game_cnt_a_;
    int game_cnt_b_;
    char set_winner_;
    bool set_ended_;
public:
    TennisSet() {
        point_a_ = 0;
        point_b_ = 0;
        finished_ = false;
        winner_ = '#';
        game_cnt_a_ = 0;
        game_cnt_b_ = 0;
        set_winner_ = '#';
        set_ended_ = false;
    }

    void pointTo(char player) {
        if (set_ended_) {
            return;
        }


        if (player == 'A') {
            point_a_ += 1;
            if (point_a_ >= 4 && point_a_ - point_b_ >= 2) {
                point_a_ = 0;
                point_b_ = 0;
                game_cnt_a_ += 1;
                if (game_cnt_a_ >= 3) {
                    set_winner_ = player;
                    set_ended_ = true;
                }
            }
        } else {
            point_b_ += 1;
            if (point_b_ >= 4 && point_b_ - point_a_ >= 2) {
                point_a_ = 0;
                point_b_ = 0;
                game_cnt_b_ += 1;
                if (game_cnt_b_ >= 3) {
                    set_winner_ = player;
                    set_ended_ = true;
                }
            }
        }
    }

    string getScore() {
        if (point_a_ >= 3 && point_b_ >= 3 && point_a_ == point_b_) {
            return "3:3";
        }
        return to_string(point_a_) + ":" + to_string(point_b_);
    }

    string getSetScore() {
        return to_string(game_cnt_a_) + ":" + to_string(game_cnt_b_);
    }

    char getSetWinner() {
        return set_winner_;
    }

    bool isOver() {
        return set_ended_;
    }
};
