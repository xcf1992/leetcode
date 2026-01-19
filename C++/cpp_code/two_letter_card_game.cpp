/*
https://leetcode.com/problems/two-letter-card-game/description/
3664. Two-Letter Card Game

You are given a deck of cards represented by a string array cards, and each card displays two lowercase letters.

You are also given a letter x. You play a game with the following rules:

Start with 0 points.
On each turn, you must find two compatible cards from the deck that both contain the letter x in any position.
Remove the pair of cards and earn 1 point.
The game ends when you can no longer find a pair of compatible cards.
Return the maximum number of points you can gain with optimal play.

Two cards are compatible if the strings differ in exactly 1 position.



Example 1:

Input: cards = ["aa","ab","ba","ac"], x = "a"

Output: 2

Explanation:

On the first turn, select and remove cards "ab" and "ac", which are compatible because they differ at only index 1.
On the second turn, select and remove cards "aa" and "ba", which are compatible because they differ at only index 0.
Because there are no more compatible pairs, the total score is 2.

Example 2:

Input: cards = ["aa","ab","ba"], x = "a"

Output: 1

Explanation:

On the first turn, select and remove cards "aa" and "ba".
Because there are no more compatible pairs, the total score is 1.

Example 3:

Input: cards = ["aa","ab","ba","ac"], x = "b"

Output: 0

Explanation:

The only cards that contain the character 'b' are "ab" and "ba". However, they differ in both indices, so they are not
compatible. Thus, the output is 0.



Constraints:

2 <= cards.length <= 105
cards[i].length == 2
Each cards[i] is composed of only lowercase English letters between 'a' and 'j'.
x is a lowercase English letter between 'a' and 'j'.
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
#include <climits>
#include <map>
#include <set>
#include <numeric>
using namespace std;

/*
We essentially have 3 sets:-

1- 1st Character is the x (SET 1)
2- 2nd Character is the x (SET 2)
3- Both Characters are x. (SET 3)

We only need to keep track of total strings in each set and the max frequency of a string of the first 2 sets.

f = max frequency of string in set 1.
tf = total count of strings in set 1.
s = max frequency of string in set 2.
ts = total count of stirngs in set 2.
xx = total count of strings in set 3.

To keep the counts in set is easy beacuse for Set 1, we know that the first character is equal to 'x', so using the
second character as key is sufficient to keep count of strings.

Similarly for Set 2 we know that second character is equal to 'x, so we use the first character as key to keep count of
strings.

In the following I will be using Set 1 as example and what we do with Set 1 will be mirrored for Set 2 as well.

Now, Let's take example in Set 1 there are 10 strings and max frequency of a string in set is 5. Let max string = "ab"
where 'x' is 'a'.

So, if we wanted to make pairs using pigeon hole:-

Max pairs possible would be 5, so let's take 5 columns each column representing a pair. Since we can't use "ab" with
itself we will have to put each "ab" in a seprate column.

ab | ab | ab | ab | ab |
   |    |    |    |    |
We can fill the remaining strings in the empty spaces in the columns and thus we will have 5 pairs(max possible pairs
when count is 10).

Suppose, count of 'ab' is more than 5, well in that case an 'ab' will overlap, so when they overlap they wouldn't form a
pair.

Example

ab | ab | ab | ab | ab |
ab | ab |    |    |    |
In this case only the (empty spaces) = (total count) - (max frequency string in set) would make pairs, thus 3 pairs.

What about when the max frequency of string in set is less than half? Well in that case there is no overlap possible
hence all strings can be part of a pair.

So, using pigeon hole, 2 case are there
1- When (max frequency of a string in set is) > (total count of strings in set) / 2.
2- When frequency of max frequency of a string in set is <= (total count of strings in set) / 2

In the first case, (tf - f) is the pairs possible, add that to 'ans' . We will store the count of strings not able to
form a pair in 'tf' .

In second case we add the max possible pairs from 'tf' in ans and remaining pairs will be tf % 2.

We do the same for Set 2 as well.
So, now we have the remainders for both set in 'tf' and 'ts' respectively, now we will try forming pairs with the
strings in Set 3 that is where 1st and 2nd character are equal to x.(xx stores count of strings in Set 3)

We add that to variable 'used', and decrease 'xx' with respect to how many pairs formed using the remaining strings in
set 1 and set 2. Why we added the pairs in this case to another variable 'used' will be explained below.

Now, Finally if there are any strings left in 'xx', we can now use the pairs in ans currently to use them.
So, in 'ans' we have pairs like ("ab", "ac"), ("da, "ea") where 'x' is character 'a'.

Now, if we think about it, we can split a pair and use the strings to pair with strings left in 'xx'.

Example :-
Pair = ("ab", "ac")
xx represents count of "aa". Let's say count is 2, so basically in Set 3 we have ("aa", "aa")

If we break the pair, we will have
("ab", )
("ac", )

We can now pair each of them with an "aa" pair.

So finally we have
("ab", "aa")
("ac", "aa)

This helps us increase the count of pairs by 1 using 2 "aa".

If there was only a single "aa", the count of pairs wouldn't increase by splitting, since one of the split strings
wouldn't be able to form a pair.

So, for every 2 counts of xx used , we can increase our pair count by 1. How many pairs count can we increase at max if
we had infinite count of 'xx'. In that case the limiting factor would be how many pairs that we stored in 'ans' we could
break. So, breaking all pairs in ans and using each string then to pair with "aa" so, max pairs = (ans * 2).

So our ans should be the minium of (max possible pairs that can be formed if we were to break all pairs currently in
'ans' , or break as mainy pairs in 'ans' until the count of 'xx' becomes less than 2 and thus can no longer be
consumed).

We then add the count of pairs stored in 'used' to ans and return it.

The reason we break the pairs in 'ans' and not try to use the strings in Set 1 and Set 2 to pair with count of 'xx' to
begin with, is due to remainder possiblity.

There can be remainders if the max frequency strings in each set is too large (> ttotal count of strings in set / 2).

Now, how do we decide which strings should the count in 'xx' pair with the strings in set 1 first or set 2 first? And
even if somehow we choose a set say Set 1, which strings should we form a pair with? The max frequency of string in Set
1? or the remaining elements?

If we were to choose the max frequcency, it could be that the second max frequency of string in Set 1 wouldn't be able
to completely pair as it is also too large. I we were to choose the remaining elemnts it could be that the max frequency
string isn't able to form all pairs it possibly could.

Taking Example to Demonstrate the above:-

Let's take 1 Set for simplicity, Set 1, 'x' = 'a', Count of strings in 'xx' = 8

So Set 1 contains :

ab (Count 8)
ac (Count 5)
ad (Count 1)

Total Count is 14.

So, if we were to choose the max frequency string "ab" and pair it with strings in 'xx'. We will have 8 pairs. The
remaining ac and ad can only pair with each other and thus only 1 pair is possible. So, total pairs is 9.

If we were to follow my method, we would first pair "ab" , "ac" and "ad". This results in 6 Pairs, and 2 counts of "ab"
as remainder, which we can pair with 'xx'. Thus 2 pairs will be stored in 'used', and new count of 'xx' is 6. We can now
split the 3 of the 6 pairs originally made and pair each of the strings from the resulting split with strings in count
of 'xx'. This will result in the 3 pairs and 'xx' = 6 tranforming into 6 pairs and 'xx' = 0. So, we have the pairs in
'used' = 2, the 3 original pairs not split, and the newly formed 6 pairs resulting in total of 11 pairs.

This is because 'xx' can always pair up later if there are any leftover counts of 'xx' since we have already created the
max possible pair for each string frequency. Thus, we first pair up the elements in each set and then try to use as much
'xx' count as possible.
 */
class Solution {
public:
    int score(vector<string>& cards, char x) {
        int first_max_freq = 0;
        int first_cnt = 0;
        int second_max_freq = 0;
        int second_cnt = 0;
        int same_card_cnt = 0;
        vector<int> dict1(26, 0);
        vector<int> dict2(26, 0);

        for (int i = 0; i < cards.size(); ++i) {
            char c1 = cards[i][0];
            char c2 = cards[i][1];
            if (c1 == x && c2 == x) {
                same_card_cnt += 1;
            }
            else if (c1 == x) {
                dict1[c2 - 'a'] += 1;
                first_max_freq = max(dict1[c2 - 'a'], first_max_freq);
                first_cnt += 1;
            } else if (c2 == x) {
                dict2[c1 - 'a']++;
                second_max_freq = max(dict2[c1 - 'a'], second_max_freq);
                second_cnt += 1;
            }
        }

        int rst = 0;
        if (first_max_freq > first_cnt - first_max_freq) {
            rst += first_cnt - first_max_freq;
            first_cnt = first_max_freq - (first_cnt - first_max_freq);
        } else {
            rst += first_cnt / 2;
            first_cnt = first_cnt % 2;
        }

        if (second_max_freq > second_cnt - second_max_freq) {
            rst += second_cnt - second_max_freq;
            second_cnt = second_max_freq - (second_cnt - second_max_freq);
        } else {
            rst += second_cnt / 2;
            second_cnt = second_cnt % 2;
        }

        int used = min(first_cnt + second_cnt, same_card_cnt);
        same_card_cnt -= used;
        rst = min(rst * 2, rst + same_card_cnt / 2);
        rst += used;
        return rst;
    }
};