/*
https://www.hack2hire.com/companies/stripe/coding-questions/697c2d689731315964cfb047/practice?questionId=697c2d6c9731315964cfb048
Applicant Coding Skills Matching
In the modern recruitment process, Applicant Tracking Systems (ATS) automatically filter candidates based on their
listed skills. An applicant provides a list of their technical skills in a comma-separated string, ordered by their
proficiency and preference. The job description lists the required skills for the position.

Given an applicant's skill string, such as:

Applicant-Skills: "Java-8, Python-3, Go-Lang"
The applicant is stating their skills in order of strength:

Java (version 8) - strongest skill
Python (version 3)
Go (Lang) - weakest skill
The recruitment system has a specific list of skills required for a job. When evaluating a candidate, the system must
identify which of the applicant's skills are actually relevant to the job requirements, preserving the order of the
applicant's strength/preference.

You are tasked to implement a function that, given a string applicantSkills (the applicant's list) and a list of strings
requiredSkills (the job's requirements), returns a list of relevant skills found in the applicant's list, in order of
their appearance.

The returned list should include each matching skill at most once, according to its first occurrence in the applicant's
list. Matching must be exact (case-sensitive, no normalization or variant matching). Whitespace surrounding each skill
in the string should be ignored. If no required skills appear in the applicant's list, return an empty list.
Constraints:

1 ≤ requiredSkills.length ≤ 1000
0 ≤ applicantSkills.length ≤ 104
Each skill consists of alphanumeric characters and hyphens, e.g., "Java-8", "C++-17", "AWS".
All elements in requiredSkills are unique.
You may assume the inputs are well-formed as described.
Example 1:

Input: applicantSkills = "Java-8, Python-3, Go-Lang", requiredSkills = ["Go-Lang", "Java-8"]
Output: ["Java-8", "Go-Lang"]
Explanation: Only "Java-8" and "Go-Lang" are required. They are returned in the order they appear in the applicant's
list.

Example 2:

Input: applicantSkills = "Python-3, Go-Lang", requiredSkills = ["Java-8", "Go-Lang"]
Output: ["Go-Lang"]

Example 3:

Input: applicantSkills = "Java-8", requiredSkills = ["Java-8", "Python-3"]
Output: ["Java-8"]
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
private:
    void parse_skills(string& applicantSkills, vector<string>& rst) {
        int pos = applicantSkills.find(',');
        while (pos != string::npos) {
            rst.push_back(applicantSkills.substr(0, pos));
            applicantSkills = applicantSkills.substr(pos + 1);
            pos = applicantSkills.find(',');
        }
        rst.push_back(applicantSkills);
    }

    void trim(string& str) {
        int start = str.find_first_not_of(" \t");
        int end = str.find_last_not_of(" \t");
        str = str.substr(start, end - start + 1);
    }

public:
    vector<string> matchSkills(string applicantSkills, vector<string> requiredSkills) {
        if (applicantSkills == "") {
            return {};
        }
        unordered_set<string> required(requiredSkills.begin(), requiredSkills.end());
        vector<string> app_skills;
        parse_skills(applicantSkills, app_skills);
        vector<string> result;
        for (string& skill : app_skills) {
            trim(skill);
            if (required.count(skill)) {
                result.push_back(skill);
            }
        }
        return result;
    }
};
/*
Follow-up 1:
In this follow-up, the Applicant-Skills list may contain generic skill categories that are not version-specific. For
example, a skill listed simply as "Java" refers to any version of Java, such as "Java-8" or "Java-11".

Extend your function so that when the applicant lists a generic skill (with no version/hyphen), it matches all required
skills that begin with that prefix and have a hyphen, in addition to still matching any exact skills.

The returned list should still:

Contain only required skills.
Reflect the applicant's order of preference as expressed in their list.
Include each required skill at most once, based on its first appearance in the applicant's list.
Example 1:

Input: applicantSkills = "Java", requiredSkills = ["Java-8", "Python-3", "Python-2"]
Output: ["Java-8"]
Explanation: The applicant lists "Java", which is a generic category. The only required skill matching this prefix is
"Java-8".

Example 2:

Input: applicantSkills = "Python", requiredSkills = ["Java-8", "Python-3", "Python-2"]
Output: ["Python-3", "Python-2"]

Example 3:

Input: applicantSkills = "Python-3, Python", requiredSkills = ["Java-8", "Python-3", "Python-2"]
Output: ["Python-3", "Python-2"]
Explanation: "Python-3" is matched exactly first. Then "Python" matches the remaining "Python-2".
 */
class Solution {
private:
    void parse_skills(string& applicantSkills, vector<string>& rst) {
        int pos = applicantSkills.find(',');
        while (pos != string::npos) {
            rst.push_back(applicantSkills.substr(0, pos));
            applicantSkills = applicantSkills.substr(pos + 1);
            pos = applicantSkills.find(',');
        }
        rst.push_back(applicantSkills);
    }

    void trim(string& str) {
        int start = str.find_first_not_of(" \t");
        int end = str.find_last_not_of(" \t");
        str = str.substr(start, end - start + 1);
    }

public:
    vector<string> matchSkills(string applicantSkills, vector<string> requiredSkills) {
        if (applicantSkills == "") {
            return {};
        }

        unordered_set<string> required(requiredSkills.begin(), requiredSkills.end());

        vector<string> app_skills;
        parse_skills(applicantSkills, app_skills);

        vector<string> result;
        unordered_set<string> added;
        for (string& skill : app_skills) {
            trim(skill);
            if (required.count(skill)) {  // exact match
                result.push_back(skill);
                added.insert(skill);
            } else if (string::npos == skill.find('-')) {  // prefix match
                string prefix = skill + "-";
                for (string& req : requiredSkills) {
                    if (added.count(req)) {
                        continue;
                    }

                    if (req.substr(0, prefix.length()) == prefix) {
                        result.push_back(req);
                        added.insert(req);
                    }
                }
            }
        }
        return result;
    }
};

/*
Follow-up 2:
In this follow-up, the Applicant-Skills list may include a wildcard entry, represented by an asterisk "*". The wildcard
indicates that the applicant possesses (or is willing to work with) all other required skills that haven't been
explicitly listed or matched yet.

When processing the list, if a wildcard "*" is encountered, add every remaining required skill (those not already
selected) to the result. The relative order for these skills should follow their order in the requiredSkills list.

Example 1:

Input: applicantSkills = "Java-8, *", requiredSkills = ["Java-8", "Python-3", "Go-Lang"]
Output: ["Java-8", "Python-3", "Go-Lang"]
Explanation: "Java-8" is matched first. The wildcard "*" then adds "Python-3" and "Go-Lang", which are the remaining
required skills.

Example 2:

Input: applicantSkills = "Python-3, Python, *", requiredSkills = ["Java-8", "Python-3", "Python-2"]
Output: ["Python-3", "Python-2", "Java-8"]

Example 3:

Input: applicantSkills = "*", requiredSkills = ["Java-8", "Python-3", "C++-17"]
Output: ["Java-8", "Python-3", "C++-17"]
 */

class Solution {
private:
    void parse_skills(string& applicantSkills, vector<string>& rst) {
        int pos = applicantSkills.find(',');
        while (pos != string::npos) {
            rst.push_back(applicantSkills.substr(0, pos));
            applicantSkills = applicantSkills.substr(pos + 1);
            pos = applicantSkills.find(',');
        }
        rst.push_back(applicantSkills);
    }

    void trim(string& str) {
        int start = str.find_first_not_of(" \t");
        int end = str.find_last_not_of(" \t");
        str = str.substr(start, end - start + 1);
    }

public:
    vector<string> matchSkills(string applicantSkills, vector<string> requiredSkills) {
        if (applicantSkills == "") {
            return {};
        }

        unordered_set<string> required(requiredSkills.begin(), requiredSkills.end());

        vector<string> app_skills;
        parse_skills(applicantSkills, app_skills);

        vector<string> result;
        unordered_set<string> added;
        for (string& skill : app_skills) {
            trim(skill);

            if (skill == "*") {
                for (string& req : requiredSkills) {
                    if (added.count(req)) {
                        continue;
                    }
                    result.push_back(req);
                    added.insert(req);
                }
                continue;
            }

            if (required.count(skill) && !added.count(skill)) {  // exact match
                result.push_back(skill);
                added.insert(skill);
            } else if (string::npos == skill.find('-')) {  // prefix match
                string prefix = skill + "-";
                for (string& req : requiredSkills) {
                    if (added.count(req)) {
                        continue;
                    }

                    if (req.substr(0, prefix.length()) == prefix) {
                        result.push_back(req);
                        added.insert(req);
                    }
                }
            }
        }
        return result;
    }
};

/*
Follow-up 3:
Now, in this follow-up, the Applicant-Skills list may include numeric weights, indicated by p= (preference/proficiency),
for each entry. These weights indicate the relative strength or preference for each skill, and they are in the range [0,
1].

A higher weight means a higher preference. If a skill has a weight of 0, it is considered least preferred but should
still be included in the result if it is required.

Extend your function to parse and respect these weights. After processing all entries, return all matched required
skills, sorted in descending order of weight. For skills with the same weight, preserve their left-to-right order of
first appearance in the list.

Example 1:

Input: applicantSkills = "Java-8;p=1, Python-3;p=0, Python;p=0.5", requiredSkills = ["Java-8", "Python-3", "Python-2"]
Output: ["Java-8", "Python-2", "Python-3"]
Explanation: "Java-8" has the highest weight (1.0). "Python" matches "Python-2" with p=0.5. "Python-3" has p=0, so it is
placed last.

Example 2:

Input: applicantSkills = "Java-8;p=1, Python-3;p=0, *;p=0.5", requiredSkills = ["Java-8", "Python-3", "Python-2",
"Go-Lang"] Output: ["Java-8", "Python-2", "Go-Lang", "Python-3"]

Example 3:

Input: applicantSkills = "Java-8;p=1, Python-3;p=0.8, *;p=0.5", requiredSkills = ["Java-8", "Python-3", "Python-2",
"Go-Lang"]
 */

class Solution {
private:
    void parse_skills(string& applicantSkills, vector<string>& rst) {
        int pos = applicantSkills.find(',');
        while (pos != string::npos) {
            rst.push_back(applicantSkills.substr(0, pos));
            applicantSkills = applicantSkills.substr(pos + 1);
            pos = applicantSkills.find(',');
        }
        rst.push_back(applicantSkills);
    }

    void trim(string& str) {
        int start = str.find_first_not_of(" \t");
        int end = str.find_last_not_of(" \t");
        str = str.substr(start, end - start + 1);
    }

public:
    vector<string> matchSkills(string applicantSkills, vector<string> requiredSkills) {
        if (applicantSkills == "") {
            return {};
        }

        unordered_set<string> required(requiredSkills.begin(), requiredSkills.end());

        vector<string> app_skills;
        parse_skills(applicantSkills, app_skills);

        vector<string> result;
        unordered_set<string> added;

        unordered_map<string, double> skill_to_weight;
        unordered_map<string, int> skill_to_order;
        int cur_order = 0;
        for (string& skill : app_skills) {
            trim(skill);

            double weight = 1.0;
            if (skill.find(';') != string::npos) {
                size_t pos = skill.find(';');
                string weight_str = skill.substr(pos + 1);
                trim(weight_str);
                if (weight_str.size() > 2 && weight_str.substr(0, 2) == "p=") {
                    weight = stod(weight_str.substr(2));
                }

                skill = skill.substr(0, pos);
                trim(skill);
            }

            if (skill == "*") {
                for (string& req : requiredSkills) {
                    if (added.count(req)) {
                        continue;
                    }
                    result.push_back(req);
                    added.insert(req);

                    skill_to_weight[req] = weight;
                    skill_to_order[req] = cur_order;
                    cur_order++;
                }
                continue;
            }

            if (required.count(skill) && !added.count(skill)) {  // exact match
                result.push_back(skill);
                added.insert(skill);

                skill_to_weight[skill] = weight;
                skill_to_order[skill] = cur_order;
                cur_order++;
            } else if (string::npos == skill.find('-')) {  // prefix match
                string prefix = skill + "-";
                for (string& req : requiredSkills) {
                    if (added.count(req)) {
                        continue;
                    }

                    if (req.substr(0, prefix.length()) == prefix) {
                        result.push_back(req);
                        added.insert(req);

                        skill_to_weight[req] = weight;
                        skill_to_order[req] = cur_order;
                        cur_order++;
                    }
                }
            }
        }

        sort(result.begin(), result.end(), [&](string& a, string& b) {
            return skill_to_weight[a] > skill_to_weight[b] ||
                   (skill_to_weight[a] == skill_to_weight[b] && skill_to_order[a] < skill_to_order[b]);
        });
        return result;
    }
};
