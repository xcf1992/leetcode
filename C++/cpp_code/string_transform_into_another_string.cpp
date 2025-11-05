/*
1153. String Transforms Into Another String

Given two strings str1 and str2 of the same length,
determine whether you can transform str1 into str2 by doing zero or more conversions.

In one conversion you can convert all occurrences of one character in str1 to any other lowercase English character.
Return true if and only if you can transform str1 into str2.

Example 1:
Input: str1 = "aabcc", str2 = "ccdee"
Output: true
Explanation: Convert 'c' to 'e' then 'b' to 'd' then 'a' to 'c'. Note that the order of conversions matter.

Example 2:
Input: str1 = "leetcode", str2 = "codeleet"
Output: false
Explanation: There is no way to transform str1 to str2.

Note:
1 <= str1.length == str2.length <= 10^4
Both str1 and str2 contain only lowercase English letters.
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
/*
It's easier to think about when str1 cannot be transformed, namely:

    If two equal str1 characters are forced to transform to different str2 characters.
    If any characters need to be 'swapped' (say, 'a' to 'b' and 'b' to a'),
    but there is no third character available as a temporary placeholder.

The first condition is straight-forward to check.
For the second condition, it is only required that str2 uses fewer than 26 unique characters.

We don't need to check str1 for the second condition,
because even if it does use 26 unique characters,
we can use the first conversion to pool two characters into one,
freeing up a character to use as a placeholder.
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
Explanation
Scan s1 and s2 at the same time,
record the transform mapping into a map/array.
The same char should transform to the same char.
Otherwise we can directly return false.

To realise the transformation:

transformation of link link ,like a -> b -> c:
we do the transformation from end to begin, that is b->c then a->b

transformation of cycle, like a -> b -> c -> a:
in this case we need a tmp
c->tmp, b->c a->b and tmp->a
Same as the process of swap two variable.

In both case, there should at least one character that is unused,
to use it as the tmp for transformation.
So we need to return if the size of set of unused characters < 26.

Complexity
Time O(N) for scanning input
Space O(26) to record the mapping
running time can be improved if count available character during the scan.
*/
class Solution {
public:
    bool canConvert(string str1, string str2) {
        if (str1 == str2) {
            return true;
        }

        unordered_map<char, char> transform;
        for (int i = 0; i < str1.size(); ++i) {
            if (transform.find(str1[i]) != transform.end() and transform[str1[i]]
            !=
            str2[i]
            )
            {
                return false;
            }
            transform[str1[i]] = str2[i];
        }
        /*
        * consider the case from abcd -> bcda
        * we can transform each letter from back
        * so str1 will become acda, without any problem
        * but when it comes to transform a -> b, we have letter a both front and back
        * so it would require we transform a -> x(some other letter not used yet)
        * and then transform x -> b
        */
        return unordered_set(str2.begin(), str2.end()).size() < 26;
    }
};