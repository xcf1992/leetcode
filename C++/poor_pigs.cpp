/*
 458. Poor Pigs
 There are 1000 buckets, one and only one of them contains poison,
 the rest are filled with water. They all look the same. If a pig drinks that poison it will die within 15 minutes.
 What is the minimum amount of pigs you need to figure out which bucket contains the poison within one hour.

 Answer this question, and write an algorithm for the follow-up general case.

 Follow-up:

 If there are n buckets and a pig drinking poison will die within m minutes,
 how many pigs (x) you need to figure out the "poison" bucket within p minutes? There is exact one bucket with poison.
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

/*
 Suppose there are 10 buckest, 10 minutes to test and the pig dies after 3 minutes.
 then we can test at most 3 rounds. For each bucket, a big can drink it during round 1 or round 2 or round 3 or not drink at all ( 4 possibilities ).
 Convert each bucket to a number of base 4.

 0 - 00
 1 - 01
 2 - 02
 3 - 03
 4 - 10
 5 - 11
 6 - 12
 7 - 13
 8 - 20
 9 - 21
 10 - 22

 We need at most 2 digits to represent 10 buckets with base 4. Each digit represents a pig.
 The number indicates at which round should the pig drink water in this bucket.

 Take bucket 6 as an example, 12 means, pig 1 should drink water in bucket 6 during round 1,
 pig 2 should drink water in bucket 6 during round 2.
 if pig 1 dies in round 1 and pig 2 dies in round 2, then bucket 6 is poisonous.

 Similarly, for bucket 8, pig 1 should drink its water during round 2 and pig 2 don't need to drink water in this bucket.
 If pig 1 dies in round 2 and pig 2 is not dead then bucket 8 is poisonous.

 The problem is converted to how many digits are required to represent a number.
 */
class Solution {
public:
    int poorPigs(int buckets, int minutesToDie, int minutesToTest) {
        int test = minutesToTest / minutesToDie + 1;
        int pigs = 0;
        while (pow(test, pigs) < buckets) {
            pigs += 1;
        }
        return pigs;
    }
};
