/*
781. Rabbits in Forest

In a forest, each rabbit has some color.
Some subset of rabbits (possibly all of them) tell you how many other rabbits have the same color as them.
Those answers are placed in an array.

Return the minimum number of rabbits that could be in the forest.

Examples:
Input: answers = [1, 1, 2]
Output: 5
Explanation:
The two rabbits that answered "1" could both be the same color, say red.
The rabbit than answered "2" can't be red or the answers would be inconsistent.
Say the rabbit that answered "2" was blue.
Then there should be 2 other blue rabbits in the forest that didn't answer into the array.
The smallest possible number of rabbits in the forest is therefore 5: 3 that answered plus 2 that didn't.

Input: answers = [10, 10, 10]
Output: 11

Input: answers = []
Output: 0
Note:

answers will have length at most 1000.
Each answers[i] will be an integer in the range [0, 999].
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
using namespace std;
/*
Each rabbit that says a different number must be a different color,
and a rabbit only tells us information about rabbits of its color.
We can count the number of rabbits of each color separately.

Now, say 13 rabbits answer 5. What does this imply?
Say one of the rabbits is red. We could have 5 other red rabbits in this group answering 5,
but not more. So, say another rabbit in this group is a different color (blue).
We could have 5 other blue rabbits in this group answering 5, but not more.
Finally, another rabbit must be a different color (green), and there are 5 other green rabbits (in the forest).

Notice there must be a minimum of 18 rabbits saying 5 (answering or in the forest),
since there must be at least 3 unique colors among rabbits that answered or would have answered 5,
so it didn't matter that we chose the rabbits to be grouped by color or not when answering.
*/
class Solution {
public:
    int numRabbits(vector<int>& answers) {
        if (answers.empty()) {
            return 0;
        }

        unordered_map<double, double> counts;
        for (int ans : answers) {
            counts[ans + 1] += 1;
        }

        int result = 0;
        for (pair<double, double> count : counts) {
            result += ceil(count.second / count.first) * count.first;
        }
        return result;
    }
};