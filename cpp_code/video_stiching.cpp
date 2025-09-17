/*
1024. Video Stitching
https://leetcode.com/problems/video-stitching/

You are given a series of video clips from a sporting event that lasted T seconds.
These video clips can be overlapping with each other and have varied lengths.

Each video clip clips[i] is an interval:
it starts at time clips[i][0] and ends at time clips[i][1].
We can cut these clips into segments freely:
for example, a clip [0, 7] can be cut into segments [0, 1] + [1, 3] + [3, 7].

Return the minimum number of clips needed
so that we can cut the clips into segments that cover the entire sporting event ([0, T]).
If the task is impossible, return -1.

Example 1:
Input: clips = [[0,2],[4,6],[8,10],[1,9],[1,5],[5,9]], T = 10
Output: 3
Explanation:
We take the clips [0,2], [8,10], [1,9]; a total of 3 clips.
Then, we can reconstruct the sporting event as follows:
We cut [1,9] into segments [1,2] + [2,8] + [8,9].
Now we have segments [0,2] + [2,8] + [8,10] which cover the sporting event [0, 10].

Example 2:
Input: clips = [[0,1],[1,2]], T = 5
Output: -1
Explanation:
We can't cover [0,5] with only [0,1] and [0,2].

Example 3:
Input: clips = [[0,1],[6,8],[0,2],[5,6],[0,4],[0,3],[6,7],[1,3],[4,7],[1,4],[2,5],[2,6],[3,4],[4,5],[5,7],[6,9]], T = 9
Output: 3
Explanation:
We can take clips [0,4], [4,7], and [6,9].

Example 4:
Input: clips = [[0,4],[2,8]], T = 5
Output: 2
Explanation:
Notice you can have extra video after the event ends.

Note:
1 <= clips.length <= 100
0 <= clips[i][0], clips[i][1] <= 100
0 <= T <= 100
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

class Solution { // dp
public:
    int videoStitching(vector<vector<int>>& clips, int T) {
        vector<int> dp(T + 1, T + 1);
        dp[0] = 0;
        for (int i = 1; i <= T; i++) {
            for (vector<int>& clip : clips) {
                if (clip[0] <= i and clip[1] >= i) {
                    dp[i] = min(dp[i], dp[clip[0]] + 1);
                }
            }
            if (dp[i] > T) {
                return -1;
            }
        }
        return dp[T];
    }
};

class Solution1 { // greedy
public:
    int videoStitching(vector<vector<int>>& clips, int T) {
        sort(clips.begin(), clips.end(), [](vector<int>& a, vector<int>& b) {
            return a[0] < b[0];
        });

        int result = 0;
        int end = 0;
        int cur = 0;
        while (cur < clips.size()) {
            if (clips[cur][0] > end) {
                return -1;
            }

            int maxEnd = end;
            while (cur < clips.size() and clips[cur][0] <= end) {
                maxEnd = max(maxEnd, clips[cur][1]);
                cur += 1;
            }

            result += 1;
            end = maxEnd;
            if (end >= T) {
                return result;
            }
        }
        return -1;
    }
};
