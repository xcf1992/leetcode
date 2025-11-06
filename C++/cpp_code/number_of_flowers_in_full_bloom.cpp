/*
2251. Number of Flowers in Full Bloom
You are given a 0-indexed 2D integer array flowers, where flowers[i] = [starti, endi] means the ith flower will be in
full bloom from starti to endi (inclusive). You are also given a 0-indexed integer array people of size n, where
people[i] is the time that the ith person will arrive to see the flowers.

Return an integer array answer of size n, where answer[i] is the number of flowers that are in full bloom when the ith
person arrives.

Example 1:


Input: flowers = [[1,6],[3,7],[9,12],[4,13]], people = [2,3,7,11]
Output: [1,2,2,2]
Explanation: The figure above shows the times when the flowers are in full bloom and when the people arrive.
For each person, we return the number of flowers in full bloom during their arrival.
Example 2:


Input: flowers = [[1,10],[3,3]], people = [3,3,2]
Output: [2,2,1]
Explanation: The figure above shows the times when the flowers are in full bloom and when the people arrive.
For each person, we return the number of flowers in full bloom during their arrival.


Constraints:

1 <= flowers.length <= 5 * 104
flowers[i].length == 2
1 <= starti <= endi <= 109
1 <= people.length <= 5 * 104
1 <= people[i] <= 109
*/

#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
#include <map>
#include <set>
#include <numeric>
#include "../extra_data_types.hpp"
using namespace std;

/*
 Collect start bloom time point array, then sort it.
 Collect end bloom time point array, then sort it.

 For each time point t in persons:

 Binary search the upper bound of t in start, then we find the started flowers.
 Binary search the lower bound of t in end, then we find the started flowers.
 Blooming flowers = started flowers - ended flowers
 */
class Solution {
public:
    vector<int> fullBloomFlowers(vector<vector<int>>& flowers, vector<int>& people) {
        size_t num_of_flowers = flowers.size();
        vector<int> flower_start(num_of_flowers, 0);
        vector<int> flower_end(num_of_flowers, 0);
        for (size_t i = 0; i < num_of_flowers; i++) {
            flower_start[i] = flowers[i][0];
            flower_end[i] = flowers[i][1];
        }
        sort(flower_start.begin(), flower_start.end());
        sort(flower_end.begin(), flower_end.end());

        vector<int> result(people.size(), 0);
        for (size_t i = 0; i < people.size(); i++) {
            int start_cnt = upper_bound(flower_start.begin(), flower_start.end(), people[i]) - flower_start.begin();
            int end_cnt = lower_bound(flower_end.begin(), flower_end.end(), people[i]) - flower_end.begin();
            result[i] = start_cnt - end_cnt;
        }
        return result;
    }
};