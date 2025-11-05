/*
1386. Cinema Seat Allocation
https://leetcode.com/problems/cinema-seat-allocation/

A cinema has n rows of seats,
numbered from 1 to n and there are ten seats in each row,
labelled from 1 to 10 as shown in the figure above.

Given the array reservedSeats containing the numbers of seats already reserved,
for example, reservedSeats[i]=[3,8]
means the seat located in row 3 and labelled with 8 is already reserved.

Return the maximum number of four-person families you can allocate on the cinema seats.
A four-person family occupies fours seats in one row, that are next to each other.
Seats across an aisle (such as [3,3] and [3,4]) are not considered to be next to each other,
however, It is permissible for the four-person family to be separated by an aisle,
but in that case, exactly two people have to sit on each side of the aisle.

Example 1:
Input: n = 3, reservedSeats = [[1,2],[1,3],[1,8],[2,6],[3,1],[3,10]]
Output: 4
Explanation: The figure above shows the optimal allocation for four families, where seats mark with blue are already reserved and contiguous seats mark with orange are for one family.

Example 2:
Input: n = 2, reservedSeats = [[2,1],[1,8],[2,6]]
Output: 2

Example 3:
Input: n = 4, reservedSeats = [[4,3],[1,4],[4,6],[1,7]]
Output: 4

Constraints:
1 <= n <= 10^9
1 <= reservedSeats.length <= min(10*n, 10^4)
reservedSeats[i].length == 2
1 <= reservedSeats[i][0] <= n
1 <= reservedSeats[i][1] <= 10
All reservedSeats[i] are distinct.
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
#include "extra_data_types.hpp"
using namespace std;

class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int> > &reservedSeats) {
        int ans = n * 2;

        unordered_map<int, char> m;

        for (auto r: reservedSeats)
            if (r[1] > 1 && r[1] < 10)
                m[r[0]] |= 1 << (r[1] - 2);

        for (auto seats: m) {
            bool p1 = !(seats.second & 0b11110000);
            bool p2 = !(seats.second & 0b00111100);
            bool p3 = !(seats.second & 0b00001111);

            if (p1 && p3)
                continue;
            else if (p1 || p2 || p3)
                ans -= 1;
            else
                ans -= 2;
        }

        return ans;
    }
};