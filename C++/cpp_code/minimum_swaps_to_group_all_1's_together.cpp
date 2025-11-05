/*
1151. Minimum Swaps to Group All 1's Together
Given a binary array data,
return the minimum number of swaps required to group all 1’s present in the array together in any place in the array.

Example 1:

Input: [1,0,1,0,1]
Output: 1
Explanation:
There are 3 ways to group all 1's together:
[1,1,1,0,0] using 1 swap.
[0,1,1,1,0] using 2 swaps.
[0,0,1,1,1] using 1 swap.
The minimum is 1.
Example 2:

Input: [0,0,0,1,0]
Output: 0
Explanation:
Since there is only one 1 in the array, no swaps needed.
Example 3:

Input: [1,0,1,0,1,0,0,1,1,0,1]
Output: 3
Explanation:
One possible solution that uses 3 swaps is [0,0,0,0,0,1,1,1,1,1,1].


Note:

1 <= data.length <= 10^5
0 <= data[i] <= 1
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

class Solution {
public:
    int minSwaps(vector<int> &data) {
        int count = 0;
        for (int d: data) {
            count += d;
        }
        if (count <= 1) {
            return 0;
        }

        int cur = 0;
        for (int i = 0; i < count; ++i) {
            cur += data[i];
        }

        int result = count - cur;
        for (int i = count; i < data.size(); ++i) {
            cur -= data[i - count] == 1 ? 1 : 0;
            cur += data[i] == 1 ? 1 : 0;
            result = min(result, count - cur);
        }
        return result;
    }
};