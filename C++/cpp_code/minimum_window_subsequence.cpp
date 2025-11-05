/*
727. Minimum Window Subsequence

Given strings S and T, find the minimum (contiguous) substring W of S,
so that T is a subsequence of W.

If there is no such window in S that covers all characters in T,
return the empty string "".
If there are multiple such minimum-length windows,
return the one with the left-most starting index.

Example 1:
Input:
S = "abcdebdde", T = "bde"
Output: "bcde"
Explanation:
"bcde" is the answer because it occurs before "bdde" which has the same length.
"deb" is not a smaller window because the elements of T in the window must occur in order.

Note:
All the strings in the input will only contain lowercase letters.
The length of S will be in the range [1, 20000].
The length of T will be in the range [1, 100].
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
using namespace std;
/* DP
这道题给了我们两个字符串S和T，让我们找出S的一个长度最短子串W，使得T是W的子序列，如果长度相同，取起始位置靠前的。清楚子串和子序列的区别，
那么题意就不难理解，题目中给的例子也很好的解释了题意。我们经过研究可以发现，返回的子串的起始字母和T的起始字母一定相同，这样才能保证最短。
那么你肯定会想先试试暴力搜索吧，以S中每个T的起始字母为起点，均开始搜索字符串T，然后维护一个子串长度的最小值。如果是这种思路，那么还是趁早打消念头吧
，博主已经替你试过了，OJ不依。原因也不难想，假如S中有大量的连续b，并且如果T也很长的话，这种算法实在是不高效啊。根据博主多年经验，
这种玩字符串且还是Hard的题，十有八九都是要用动态规划Dynamic Programming来做的，那么就直接往DP上去想吧。DP的第一步就是设计dp数组，像这种两个字符串的题，
一般都是一个二维数组，想想该怎么定义。确定一个子串的两个关键要素是起始位置和长度，那么我们的dp值到底应该是定起始位置还是长度呢？
That is a question! 仔细想一想，其实起始位置是长度的基础，因为我们一旦知道了起始位置，那么当前位置减去起始位置，
就是长度了，所以我们dp值定为起始位置。

那么 dp[i][j] 表示范围S中前i个字符包含范围T中前j个字符的子串的起始位置，注意这里的包含是子序列包含关系。

然后就是确定长度了，有时候会使用字符串的原长度，有时候会多加1，看个人习惯吧，
这里博主长度多加了个1。OK，下面就是重中之重啦，求递推式。一般来说，dp[i][j]的值是依赖于之前已经求出的dp值的，
在递归形式的解法中，dp数组也可以看作是记忆数组，从而省去了大量的重复计算，这也是dp解法凌驾于暴力搜索之上的主要原因。
牛B的方法总是最难想出来的，dp的递推式就是其中之一。在脑子一片浆糊的情况下，
博主的建议是从最简单的例子开始分析，比如 S = "b", T = "b", 那么我们就有 dp[1][1] = 0，
因为S中的起始位置为0，长度为1的子串可以包含T。如果当 S = "d", T = "b"，
那么我们有 dp[1][1] = -1，因为我们的dp数组初始化均为-1，表示未匹配或者无法匹配。
下面来看一个稍稍复杂些的例子，S = "dbd", T = "bd"，我们的dp数组是：
   ∅  b  d
∅  ?  ?  ?
d  ? -1 -1
b  ?  1 -1
d  ?  1  1
这里的问号是边界，我们还不知道如何初给边界赋值，我们看到，为-1的地方是对应的字母不相等的地方。
我们首先要明确的是dp[i][j]中的j不能大于i，因为T的长度不能大于S的长度，
所以j大于i的dp[i][j]一定都是-1的。再来看为1的几个位置，首先是 dp[2][1] = 1，
这里表示db包含b的子串起始位置为1，make sense！然后是 dp[3][1] = 1，这里表示dbd包含b的子串起始位置为1，
没错！然后是 dp[3][2] = 1，这里表示dbd包含bd的起始位置为1，all right! 那么我们可以观察出，当 S[i] == T[j] 的时候，
实际上起始位置和 dp[i - 1][j - 1] 是一样的，比如dbd包含bd的起始位置和db包含b的起始位置一样，所以可以继承过来。
那么当 S[i] != T[j] 的时候，怎么搞？其实是和 dp[i - 1][j] 是一样的，比如dbd包含b的起始位置和db包含b的起始位置是一样的。

嗯，这就是递推式的核心了，下面再来看边界怎么赋值，由于j比如小于等于i，所以第一行的第二个位置往后一定都是-1，我们只需要给第一列赋值即可。通过前面的分析，我们知道了当 S[i] == T[j] 时，我们取的是左上角的dp值，表示当前字母在S中的位置，由于我们dp数组提前加过1，所以第一列的数只要赋值为当前行数即可。最终的dp数组如下：

   ∅  b  d
∅  0 -1 -1
d  1 -1 -1
b  2  1 -1
d  3  1  1
为了使代码更加简洁，我们在遍历完每一行，检测如果 dp[i][n] 不为-1，说明T已经被完全包含了，
且当前的位置跟起始位置都知道了，我们计算出长度来更新一个全局最小值minLen，
同时更新最小值对应的起始位置start，最后取出这个全局最短子串，如果没有找到返回空串即可，
参见代码如下：
*/
class Solution {
public:
    string minWindow(string S, string T) {
        int m = S.size();
        int n = T.size();
        if (m < n) {
            return "";
        }

        int start = -1;
        int minLen = S.size();
        vector<vector<int> > dp(m + 1, vector<int>(n + 1, -1));
        for (int i = 0; i <= m; ++i) {
            dp[i][0] = i;
        }
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= min(i, n); ++j) {
                if (S[i - 1] == T[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = dp[i - 1][j];
                }
            }
            if (dp[i][n] != -1) {
                int len = i - dp[i][n];
                if (minLen > len) {
                    minLen = len;
                    start = dp[i][n];
                }
            }
        }
        return start != -1 ? S.substr(start, minLen) : "";
    }
};

/* two pointers
优化过的暴力搜索的方法，而且居然beat了100%，给跪了好嘛？！而且这双指针的跳跃方式犹如舞蹈般美妙绝伦，比那粗鄙的暴力搜索双指针不知道高到哪里去了？！
举个栗子来说吧，比如当 S = "bbbbdde", T = "bde"时，我们知道暴力搜索的双指针在S和T的第一个b匹配上之后，就开始检测S之后的字符能否包含T之后的所有字符，
当匹配结束后，S的指针就会跳到第二个b开始匹配，由于有大量的重复b出现，所以每一个b都要遍历一遍，会达到平方级的复杂度，
会被OJ无情拒绝。而下面这种修改后的算法会跳过所有重复的b，使得效率大大提升，具体是这么做的，当第一次匹配成功后，
我们的双指针往前走，找到那个刚好包含T中字符的位置，比如开始指针 i = 0 时，指向S中的第一个b，
指针 j = 0 时指向T中的第一个b，然后开始匹配T，当 i = 6， j = 2 时，此时完全包含了T。
暴力搜索解法中此时i会回到1继续找，而这里，我们通过向前再次匹配T，会在 i = 3，j = 0处停下，
然后继续向后找，这样S中重复的b就会被跳过，从而达到线性的复杂度
*/
class Solution1 {
public:
    string minWindow(string S, string T) {
        int m = S.size();
        int n = T.size();
        int start = -1;
        int minLen = S.size();
        int i = 0;
        int j = 0;
        while (i < m) {
            if (S[i] == T[j]) {
                if (j == n - 1) {
                    int end = i;
                    i -= 1;
                    j -= 1;
                    for (; j >= 0; --j) {
                        while (S[i] != T[j]) {
                            i -= 1;
                        }
                    }
                    j = 0;

                    if (end - i + 1 < minLen) {
                        minLen = end - i + 1;
                        start = i;
                    }
                } else {
                    j += 1;
                }
            }
            i += 1;
        }
        return start == -1 ? "" : S.substr(start, minLen);
    }
};