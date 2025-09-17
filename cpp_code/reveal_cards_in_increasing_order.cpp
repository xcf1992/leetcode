/*
950. Reveal Cards In Increasing Order
https://leetcode.com/problems/reveal-cards-in-increasing-order/

In a deck of cards, every card has a unique integer.
You can order the deck in any order you want.

Initially, all the cards start face down (unrevealed) in one deck.

Now, you do the following steps repeatedly, until all cards are revealed:

Take the top card of the deck, reveal it, and take it out of the deck.
If there are still cards in the deck, put the next top card of the deck at the bottom of the deck.
If there are still unrevealed cards, go back to step 1.
Otherwise, stop.
Return an ordering of the deck that would reveal the cards in increasing order.

The first entry in the answer is considered to be the top of the deck.

Example 1:

Input: [17,13,11,2,3,5,7]
Output: [2,13,3,11,5,17,7]
Explanation:
We get the deck in the order [17,13,11,2,3,5,7] (this order doesn't matter), and reorder it.
After reordering, the deck starts as [2,13,3,11,5,17,7], where 2 is the top of the deck.
We reveal 2, and move 13 to the bottom.  The deck is now [3,11,5,17,7,13].
We reveal 3, and move 11 to the bottom.  The deck is now [5,17,7,13,11].
We reveal 5, and move 17 to the bottom.  The deck is now [7,13,11,17].
We reveal 7, and move 13 to the bottom.  The deck is now [11,17,13].
We reveal 11, and move 17 to the bottom.  The deck is now [13,17].
We reveal 13, and move 17 to the bottom.  The deck is now [17].
We reveal 17.
Since all the cards revealed are in increasing order, the answer is correct.


Note:

1 <= A.length <= 1000
1 <= A[i] <= 10^6
A[i] != A[j] for all i != j
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
/*
一开始对原始的deck进行排序，以例题为例子，deck=[17,13,11,2,3,5,7],deck.sort之后为deck=[2, 3, 5, 7, 11, 13, 17]，
然后我们开始进行逆向操作还原。每一次操作的规律也比较简单，在数据排序完毕的情况下，
我们首先将最后一位数字移回原数组的第一位，然后在第一位数字的前面加入剩下的数里面最大的数，
具体的还是举例子说明方便些：deck=[2, 3, 5, 7, 11, 13, 17]
1、17 移到第一位，然后在17前面插入13，此时数组为【13，17】
2、17 移到第一位，然后在17前面插入11，此时数组为【11，17，13】
3、13 移到第一位，然后在13前面插入7，此时数组为【7，13，11，17】
4、17 移到第一位，然后在17前面插入13，此时数组为【5，17，7，13，11】
5、11 移到第一位，然后在11前面插入3，此时数组为【3，11，5，17，7，13】
6、13 移到第一位，然后在13前面插入2，此时数组为【2，13，3，11，5，17，7】
最终得到正确答案【2，13，3，11，5，17，7】
*/
class Solution {
public:
    vector<int> deckRevealedIncreasing(vector<int>& deck) {
        sort(deck.begin(), deck.end());
        deque<int> result;
        result.push_front(deck.back());
        for (int i = deck.size() - 2; i >= 0; i--) {
            result.push_front(result.back());
            result.pop_back();
            result.push_front(deck[i]);
        }
        return vector<int>(result.begin(), result.end());
    }
};

class Solution1 {
private:
    vector<int> orderDeck(vector<int>& deck, int start, int n) {
        int curSize = n - start;
        vector<int> result(curSize, 0);
        if (curSize == 2) {
            return {deck[start], deck[start + 1]};
        }
        if (curSize == 1) {
            return {deck[start]};
        }

        int pos = 0;
        int i = 0;
        while (pos < result.size()) {
            result[pos] = deck[start + i];
            pos += 2;
            i += 1;
        }

        vector<int> halfDeck = orderDeck(deck, start + i, n);
        pos = 1;
        if (curSize % 2 != 0) {
            /*
             if number of cards is odd:
             1 - a - 2 - b - 3 - c - 4
             then after we pick 4, a will be moved to the bottom
             so we need to do an extra operation here
             put a as the biggest card of the left half cards
             then we will pick from order b c a
             which should be the order we generated
            */
            result[pos] = halfDeck.back();
            pos += 2;
        }
        i = 0;
        while (pos < result.size()) {
            result[pos] = halfDeck[i++];
            pos += 2;
        }
        return result;
    }
public:
    vector<int> deckRevealedIncreasing(vector<int>& deck) {
        int n = deck.size();
        sort(deck.begin(), deck.end());
        return orderDeck(deck, 0, n);
    }
};
