/*
292. Nim Game
You are playing the following Nim Game with your friend:
There is a heap of stones on the table,
each time one of you take turns to remove 1 to 3 stones.
The one who removes the last stone will be the winner.
You will take the first turn to remove the stones.

Both of you are very clever and have optimal strategies for the game.
Write a function to determine whether you can win the game given the number of stones in the heap.

Example:

Input: 4
Output: false
Explanation: If there are 4 stones in the heap, then you will never win the game;
             No matter 1, 2, or 3 stones you remove, the last stone will always be
             removed by your friend.
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
using namespace std;

/*
从4开始递推：5、6、7能分别拿掉1、2、3个石头，对方就拿到的是4，就输了，即5、6、7->true。
但是当n=8时，无论拿掉多少个石头，对方拿到的都是5/6/7个石头，对方就赢了，故8->false。
往后依此递推，9，10，11都可以给对方留下8个，对方就输了。
即对于每个n是false，n+1、n+2、n+3都是true，n+4都是false。递推关系满足n被4整除时返回false。
*/
class Solution {
public:
    bool canWinNim(int n) {
        return n % 4 != 0;
    }
};

class Solution1 {
    // tle
public:
    bool canWinNim(int n) {
        if (n <= 3) {
            return true;
        }
        bool take_one = true;
        bool take_two = true;
        bool take_three = true;
        bool result = false;
        for (int i = 4; i <= n; i++) {
            if (take_one and take_two and take_three) {
                result = false;
            } else {
                result = true;
            }
            take_three = take_two;
            take_two = take_one;
            take_one = result;
        }
        return result;
    }
};