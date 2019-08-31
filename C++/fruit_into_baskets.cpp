/*
904. Fruit Into Baskets
In a row of trees, the i-th tree produces fruit with type tree[i].

You start at any tree of your choice,
then repeatedly perform the following steps:

Add one piece of fruit from this tree to your baskets.
If you cannot, stop.
Move to the next tree to the right of the current tree.
If there is no tree to the right, stop.

Note that you do not have any choice after the initial choice of starting tree:
you must perform step 1, then step 2, then back to step 1, then step 2, and so on until you stop.

You have two baskets, and each basket can carry any quantity of fruit,
but you want each basket to only carry one type of fruit each.

What is the total amount of fruit you can collect with this procedure?

Example 1:

Input: [1,2,1]
Output: 3
Explanation: We can collect [1,2,1].
Example 2:

Input: [0,1,2,2]
Output: 3
Explanation: We can collect [1,2,2].
If we started at the first tree, we would only collect [0, 1].
Example 3:

Input: [1,2,3,2,2]
Output: 4
Explanation: We can collect [2,3,2,2].
If we started at the first tree, we would only collect [1, 2].
Example 4:

Input: [3,3,3,1,2,1,1,2,3,3,4]
Output: 5
Explanation: We can collect [1,2,1,1,2].
If we started at the first tree or the eighth tree, we would only collect 4 fruits.


Note:

1 <= tree.length <= 40000
0 <= tree[i] < tree.length
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

class Solution {
public:
    int totalFruit(vector<int>& tree) {
        int result = 0;
        int typ1 = -1;
        int typ2 = -1;
        int count = 0;
        int idx1 = -1;
        int idx2 = -1;
        for (int pos = 0; pos < tree.size(); pos++) {
            if (typ1 == -1 or typ1 == tree[pos]) {
                typ1 = tree[pos];
                count += 1;
                idx1 = pos;
            }
            else if (typ2 == -1 or typ2 == tree[pos]) {
                typ2 = tree[pos];
                count += 1;
                idx2 = pos;
            }
            else {
                result = max(result, count);
                if (idx2 < idx1) {
                    swap(idx1, idx2);
                    swap(typ1, typ2);
                }
                count = pos - idx1;
                typ1 = tree[pos];
                idx1 = pos;
            }
        }
        return max(count, result);
    }
};
