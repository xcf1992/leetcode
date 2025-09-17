/*
1744. Can You Eat Your Favorite Candy on Your Favorite Day?
https://leetcode.com/problems/can-you-eat-your-favorite-candy-on-your-favorite-day/

You are given a (0-indexed) array of positive integers candiesCount
where candiesCount[i] represents the number of candies of the ith type you have.
You are also given a 2D array queries where queries[i] = [favoriteTypei, favoriteDayi, dailyCapi].

You play a game with the following rules:
You start eating candies on day 0.
You cannot eat any candy of type i unless you have eaten all candies of type i - 1.
You must eat at least one candy per day until you have eaten all the candies.

Construct a boolean array answer such that answer.length == queries.length
and answer[i] is true
if you can eat a candy of type favoriteTypei on day favoriteDayi
without eating more than dailyCapi candies on any day,
and false otherwise. Note that you can eat different types of candy on the same day,
provided that you follow rule 2.

Return the constructed array answer.

Example 1:
Input: candiesCount = [7,4,5,3,8], queries = [[0,2,2],[4,2,4],[2,13,1000000000]]
Output: [true,false,true]
Explanation:
1- If you eat 2 candies (type 0) on day 0 and 2 candies (type 0) on day 1, you will eat a candy of type 0 on day 2.
2- You can eat at most 4 candies each day.
   If you eat 4 candies every day, you will eat 4 candies (type 0) on day 0 and 4 candies (type 0 and type 1) on day 1.
   On day 2, you can only eat 4 candies (type 1 and type 2), so you cannot eat a candy of type 4 on day 2.
3- If you eat 1 candy each day, you will eat a candy of type 2 on day 13.
Example 2:
Input: candiesCount = [5,2,6,4,1], queries = [[3,1,2],[4,10,3],[3,10,100],[4,100,30],[1,3,1]]
Output: [false,true,true,false,false]

Constraints:
1 <= candiesCount.length <= 105
1 <= candiesCount[i] <= 105
1 <= queries.length <= 105
queries[i].length == 3
0 <= favoriteTypei < candiesCount.length
0 <= favoriteDayi <= 109
1 <= dailyCapi <= 109
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
#include <stdio.h>
#include <set>
#include <numeric>
#include <bitset>
using namespace std;
/*
We have given count of all candies of a particular type,
Now as I have to eat all the candies of type < i before eating candy of type i, so we can have a prefix sum array for candies count
(int array elements can overflow)

As for each query, we have

type
day
capacity
Now,
max and min day required to eat are
maxDay = prefix[type+1]-1;
minDay = prefix[type]/capacity;

If, day lies between max and min day then query is true
else false
*/
class Solution {
public:
    vector<bool> canEat(vector<int>& candies, vector<vector<int>>& queries) {
        int n = candies.size();
        vector<long long> prefix(n + 1, 0);
        for (int i = 1; i < n + 1; ++i) {
            prefix[i] = prefix[i - 1] + candies[i - 1];
        }

        vector<bool> ans;
        for (auto &query : queries) {
            long long type = query[0], day = query[1], capacity = query[2];
            long long maxDay = prefix[type + 1] - 1;
            long long minDay = prefix[type] / capacity;

            if (day <= maxDay && day >= minDay)
                ans.push_back(true);
            else
                ans.push_back(false);
        }
        return ans;
    }
};