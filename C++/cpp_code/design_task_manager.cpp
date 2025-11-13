/*
https://leetcode.com/problems/design-task-manager/description/
3408. Design Task Manager

There is a task management system that allows users to manage their tasks, each associated with a priority. The system
should efficiently handle adding, modifying, executing, and removing tasks.

Implement the TaskManager class:

TaskManager(vector<vector<int>>& tasks) initializes the task manager with a list of user-task-priority triples. Each
element in the input list is of the form [userId, taskId, priority], which adds a task to the specified user with the
given priority.

void add(int userId, int taskId, int priority) adds a task with the specified taskId and priority to the user with
userId. It is guaranteed that taskId does not exist in the system.

void edit(int taskId, int newPriority) updates the priority of the existing taskId to newPriority. It is guaranteed that
taskId exists in the system.

void rmv(int taskId) removes the task identified by taskId from the system. It is guaranteed that taskId exists in the
system.

int execTop() executes the task with the highest priority across all users. If there are multiple tasks with the same
highest priority, execute the one with the highest taskId. After executing, the taskId is removed from the system.
Return the userId associated with the executed task. If no tasks are available, return -1.

Note that a user may be assigned multiple tasks.



Example 1:

Input:
["TaskManager", "add", "edit", "execTop", "rmv", "add", "execTop"]
[[[[1, 101, 10], [2, 102, 20], [3, 103, 15]]], [4, 104, 5], [102, 8], [], [101], [5, 105, 15], []]

Output:
[null, null, null, 3, null, null, 5]

Explanation

TaskManager taskManager = new TaskManager([[1, 101, 10], [2, 102, 20], [3, 103, 15]]); // Initializes with three tasks
for Users 1, 2, and 3. taskManager.add(4, 104, 5); // Adds task 104 with priority 5 for User 4. taskManager.edit(102,
8); // Updates priority of task 102 to 8. taskManager.execTop(); // return 3. Executes task 103 for User 3.
taskManager.rmv(101); // Removes task 101 from the system.
taskManager.add(5, 105, 15); // Adds task 105 with priority 15 for User 5.
taskManager.execTop(); // return 5. Executes task 105 for User 5.


Constraints:

1 <= tasks.length <= 105
0 <= userId <= 105
0 <= taskId <= 105
0 <= priority <= 109
0 <= newPriority <= 109
At most 2 * 105 calls will be made in total to add, edit, rmv, and execTop methods.
The input is generated such that taskId will be valid.
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

struct myComp {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
        return a.second < b.second || (a.second == b.second && a.first < b.first);
    }
};

class TaskManager {
public:
    TaskManager(vector<vector<int>>& tasks) {
        for (const vector<int>& task : tasks) {
            add(task[0], task[1], task[2]);
        }
    }

    void add(int userId, int taskId, int priority) {
        task_priority_[taskId] = priority;
        task_owner_[taskId] = userId;
        tasks_.push({taskId, priority});
    }

    void edit(int taskId, int newPriority) {
        task_priority_[taskId] = newPriority;
        tasks_.push({taskId, newPriority});
    }

    void rmv(int taskId) {
        task_priority_.erase(taskId);
        task_owner_.erase(taskId);
    }

    int execTop() {
        while (!tasks_.empty()) {
            int task_id = tasks_.top().first;
            int priority = tasks_.top().second;
            tasks_.pop();
            if (task_priority_.find(task_id) != task_priority_.end() && task_owner_.find(task_id) != task_owner_.end() && priority == task_priority_[task_id]) {
                int owner = task_owner_[task_id];
                rmv(task_id);
                return owner;
            }
        }
        return -1;
    }

private:
    unordered_map<int, int> task_priority_;
    unordered_map<int, int> task_owner_;
    priority_queue<pair<int, int>, vector<pair<int, int>>, myComp> tasks_;
};

/**
 * Your TaskManager object will be instantiated and called as such:
 * TaskManager* obj = new TaskManager(tasks);
 * obj->add(userId,taskId,priority);
 * obj->edit(taskId,newPriority);
 * obj->rmv(taskId);
 * int param_4 = obj->execTop();
 */