/*
 825. Friends Of Appropriate Ages
 Some people will make friend requests. The list of their ages is given and ages[i] is the age of the ith person.

 Person A will NOT friend request person B (B != A) if any of the following conditions are true:

 age[B] <= 0.5 * age[A] + 7
 age[B] > age[A]
 age[B] > 100 && age[A] < 100
 Otherwise, A will friend request B.

 Note that if A requests B, B does not necessarily request A.  Also, people will not friend request themselves.

 How many total friend requests are made?

 Example 1:

 Input: [16,16]
 Output: 2
 Explanation: 2 people friend request each other.
 Example 2:

 Input: [16,17,18]
 Output: 2
 Explanation: Friend requests are made 17 -> 16, 18 -> 17.
 Example 3:

 Input: [20,30,100,110,120]
 Output:
 Explanation: Friend requests are made 110 -> 100, 120 -> 110, 120 -> 100.


 Notes:

 1 <= ages.length <= 20000.
 1 <= ages[i] <= 120.
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
using namespace std;

class Solution {
public:
    int numFriendRequests(vector<int>& ages) {
        vector<int> people(121, 0);
        for (int age : ages) {
            people[age] += 1;
        }

        int result = 0;
        for (int i = 0 ; i <= 120; i++) {
            for (int j = 1 + 7 + i / 2; j <= i; ++j) {
                result += people[j] * (people[i] - (i == j));
            }
        }
        return result;
    }
};
