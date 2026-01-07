/*
https://leetcode.com/problems/reward-top-k-students/description/
2512. Reward Top K Students

You are given two string arrays positive_feedback and negative_feedback, containing the words denoting positive and
negative feedback, respectively. Note that no word is both positive and negative.

Initially every student has 0 points. Each positive word in a feedback report increases the points of a student by 3,
whereas each negative word decreases the points by 1.

You are given n feedback reports, represented by a 0-indexed string array report and a 0-indexed integer array
student_id, where student_id[i] represents the ID of the student who has received the feedback report report[i]. The ID
of each student is unique.

Given an integer k, return the top k students after ranking them in non-increasing order by their points. In case more
than one student has the same points, the one with the lower ID ranks higher.



Example 1:

Input: positive_feedback = ["smart","brilliant","studious"], negative_feedback = ["not"], report = ["this student is
studious","the student is smart"], student_id = [1,2], k = 2 Output: [1,2] Explanation: Both the students have 1
positive feedback and 3 points but since student 1 has a lower ID he ranks higher. Example 2:

Input: positive_feedback = ["smart","brilliant","studious"], negative_feedback = ["not"], report = ["this student is not
studious","the student is smart"], student_id = [1,2], k = 2 Output: [2,1] Explanation:
- The student with ID 1 has 1 positive feedback and 1 negative feedback, so he has 3-1=2 points.
- The student with ID 2 has 1 positive feedback, so he has 3 points.
Since student 2 has more points, [2,1] is returned.


Constraints:

1 <= positive_feedback.length, negative_feedback.length <= 104
1 <= positive_feedback[i].length, negative_feedback[j].length <= 100
Both positive_feedback[i] and negative_feedback[j] consists of lowercase English letters.
No word is present in both positive_feedback and negative_feedback.
n == report.length == student_id.length
1 <= n <= 104
report[i] consists of lowercase English letters and spaces ' '.
There is a single space between consecutive words of report[i].
1 <= report[i].length <= 100
1 <= student_id[i] <= 109
All the values of student_id[i] are unique.
1 <= k <= n
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
using namespace std;

class Solution {
private:
    int calc_feedback_points(unordered_set<string>& positive, unordered_set<string>& negative, string& feedback) {
        int rst = 0;
        int pos = feedback.find(" ");
        while (pos != string::npos) {
            string word = feedback.substr(0, pos);
            if (positive.find(word) != positive.end()) {
                rst += 3;
            }
            if (negative.find(word) != negative.end()) {
                rst -= 1;
            }
            feedback = feedback.substr(pos + 1);
            pos = feedback.find(" ");
        }

        if (positive.find(feedback) != positive.end()) {
            rst += 3;
        }
        if (negative.find(feedback) != negative.end()) {
            rst -= 1;
        }
        return rst;
    }

public:
    vector<int> topStudents(vector<string>& positive_feedback, vector<string>& negative_feedback,
                            vector<string>& report, vector<int>& student_id, int k) {
        unordered_set<string> positive(positive_feedback.begin(), positive_feedback.end());
        unordered_set<string> negative(negative_feedback.begin(), negative_feedback.end());

        int n = report.size();
        vector<pair<int, int>> student_points(n);
        for (int i = 0; i < n; i++) {
            int point = calc_feedback_points(positive, negative, report[i]);
            student_points[i] = make_pair(point, student_id[i]);
        }

        sort(student_points.begin(), student_points.end(), [](pair<int, int>& a, pair<int, int>& b) {
            return a.first > b.first || (a.first == b.first && a.second < b.second);
        });

        vector<int> rst;
        int cnt = min(n, k);
        for (int i = 0; i < cnt; i++) {
            rst.push_back(student_points[i].second);
        }
        return rst;
    }
};
