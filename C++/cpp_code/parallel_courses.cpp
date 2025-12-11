/*
https://leetcode.com/problems/parallel-courses/description/
1136. Parallel Courses

You are given an integer n, which indicates that there are n courses labeled from 1 to n. You are also given an array
relations where relations[i] = [prevCoursei, nextCoursei], representing a prerequisite relationship between course
prevCoursei and course nextCoursei: course prevCoursei has to be taken before course nextCoursei.

In one semester, you can take any number of courses as long as you have taken all the prerequisites in the previous
semester for the courses you are taking.

Return the minimum number of semesters needed to take all courses. If there is no way to take all the courses, return
-1.



Example 1:


Input: n = 3, relations = [[1,3],[2,3]]
Output: 2
Explanation: The figure above represents the given graph.
In the first semester, you can take courses 1 and 2.
In the second semester, you can take course 3.
Example 2:


Input: n = 3, relations = [[1,2],[2,3],[3,1]]
Output: -1
Explanation: No course can be studied because they are prerequisites of each other.


Constraints:

1 <= n <= 5000
1 <= relations.length <= 5000
relations[i].length == 2
1 <= prevCoursei, nextCoursei <= n
prevCoursei != nextCoursei
All the pairs [prevCoursei, nextCoursei] are unique.
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
using namespace std;

class Solution {
    // bfs 72.3%
public:
    int minimumSemesters(int n, vector<vector<int>>& relations) {
        vector<int> pre_cnt(n, 0);
        vector<unordered_set<int>> next_courses(n);
        for (vector<int>& relation : relations) {
            int pre = relation[0] - 1;
            int after = relation[1] - 1;
            pre_cnt[after] += 1;
            next_courses[pre].insert(after);
        }

        queue<int> bfs;
        int left_cnt = n;
        for (int i = 0; i < n; ++i) {
            if (pre_cnt[i] == 0) {
                bfs.push(i);
                left_cnt -= 1;
            }
        }

        if (bfs.empty()) {
            return -1;
        }

        int rst = 0;
        while (!bfs.empty()) {
            rst += 1;
            int cur_size = bfs.size();
            for (int i = 0; i < cur_size; ++i) {
                int cur = bfs.front();
                bfs.pop();

                for (int nxt : next_courses[cur]) {
                    pre_cnt[nxt] -= 1;
                    if (pre_cnt[nxt] == 0) {
                        bfs.push(nxt);
                        left_cnt -= 1;
                    }
                }
            }
        }
        return left_cnt == 0 ? rst : -1;
    }
};

class Solution1 {
    // 36.6%
public:
    int minimumSemesters(int N, vector<vector<int>>& relations) {
        vector<int> preCount(N, 0);
        vector<unordered_set<int>> learnAfter(N);
        for (vector<int>& relation : relations) {
            preCount[relation[1] - 1] += 1;
            learnAfter[relation[0] - 1].insert(relation[1] - 1);
        }

        int courseLeft = N;
        int result = 0;
        while (courseLeft > 0) {
            result += 1;
            vector<int> complelted;
            for (int i = 0; i < N; ++i)
                if (preCount[i] == 0) {
                    complelted.push_back(i);
                    preCount[i] = -1;
                    courseLeft -= 1;
                }

            if (complelted.empty()) {
                break;
            }

            for (int c : complelted) {
                for (int nxt : learnAfter[c]) {
                    preCount[nxt] -= 1;
                }
            }
        }
        return courseLeft == 0 ? result : -1;
    }
};