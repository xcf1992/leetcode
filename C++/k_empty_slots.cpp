/*
683. K Empty Slots
You have N bulbs in a row numbered from 1 to N.
Initially, all the bulbs are turned off.
We turn on exactly one bulb everyday until all bulbs are on after N days.

You are given an array bulbs of length N where bulbs[i] = x
means that on the (i+1)th day, we will turn on the bulb at position x
where i is 0-indexed and x is 1-indexed.

Given an integer K,
find out the minimum day number such that there exists two turned on bulbs
that have exactly K bulbs between them that are all turned off.

If there isn't such day, return -1.

Example 1:

Input:
bulbs: [1,3,2]
K: 1
Output: 2
Explanation:
On the first day: bulbs[0] = 1, first bulb is turned on: [1,0,0]
On the second day: bulbs[1] = 3, third bulb is turned on: [1,0,1]
On the third day: bulbs[2] = 2, second bulb is turned on: [1,1,1]
We return 2 because on the second day, there were two on bulbs with one off bulb between them.
Example 2:

Input:
bulbs: [1,2,3]
K: 1
Output: -1


Note:

1 <= N <= 20000
1 <= bulbs[i] <= N
bulbs is a permutation of numbers from 1 to N.
0 <= K <= 20000
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
#include <set>
using namespace std;

/*
We wanted to find candidate intervals [left, right] where days[left],
days[right] are the two smallest values in [days[left], days[left+1], ..., days[right]],
and right - left = k + 1.

Notice that these candidate intervals cannot intersect:
for example, if the candidate intervals are [left1, right1] and [left2, right2] with
left1 < left2 < right1 < right2, then for the first interval to be a candidate, days[left2] > days[right1];
and for the second interval to be a candidate, days[right1] > days[left2], a contradiction.

That means whenever whether some interval can be a candidate and it fails first at i,
indices j < i can't be the start of a candidate interval. This motivates a sliding window approach.
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
The idea is to use an array days[] to record each position's flower's blooming day.
That means days[i] is the blooming day of the flower in position i+1.

We just need to find a subarray days[left, left+1,..., left+k-1, right]
which satisfies: for any i = left+1,..., left+k-1,
we can have days[left] < days[i] && days[right] < days[i].
Then, the result is max(days[left], days[right]).
-=-=-=-=-=-
It took me a while to figure out why we need to update left to i instead of (left+1),
when we find the current window is invalid, and I want to share the idea:

if days[i] < days[left]/days[right],
since we already know days[left]/days[right] < days[k] for k = left+1, ... i-1,
then days[i] < days[k] for k=left+1,...,i-1.
So any window starting from left+1~i-1 will not be valid because of the existence of days[i],
so we have to set left to i, to make the window potentially valid.
This make all the information from already scanned positions useful.
*/
class Solution { // O(N)
public:
    int kEmptySlots(vector<int>& bulbs, int K) {
        int n = bulbs.size();
        vector<int> days(n, 0); // days[i] means bulbs i + 1 was turned on at days[i]
        for (int i = 0; i < n; i++) {
            days[bulbs[i] - 1] = i + 1;
        }

        int left = 0;
        int right = K + 1;
        int res = INT_MAX;
        for (int i = 1; right < n; i++) {
            // current days[i] is valid, continue scanning
            if (days[i] > days[left] and days[i] > days[right]) {
                continue;
            }
            // reach boundary of sliding window, since previous number are all valid, record result
            if (i == right) {
                res = min(res, max(days[left], days[right]));
            }
            // not valid, move the sliding window
            left = i;
            right = left + K + 1;
        }
        return res == INT_MAX ? -1 : res;
    }
};

class Solution { // O(nlogn)
public:
    int kEmptySlots(vector<int>& bulbs, int K) {
        set<int> lighted;
        int day = 1;
        for (int bulb : bulbs) {
            auto it = lighted.upper_bound(bulb);
            if (it != lighted.end() and *it - bulb == K + 1) {
                return day;
            }
            it = lighted.insert(bulb).first;
            if (it != lighted.begin() and bulb - *prev(it) == K + 1) {
                return day;
            }
            day += 1;
        }
        return -1;
    }
};
