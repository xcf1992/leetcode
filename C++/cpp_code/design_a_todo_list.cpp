/*
https://leetcode.com/problems/design-a-todo-list/description/
2590. Design a Todo List

Design a Todo List Where users can add tasks, mark them as complete, or get a list of pending tasks. Users can also add
tags to tasks and can filter the tasks by certain tags.

Implement the TodoList class:

TodoList() Initializes the object.
int addTask(int userId, String taskDescription, int dueDate, List<String> tags) Adds a task for the user with the ID
userId with a due date equal to dueDate and a list of tags attached to the task. The return value is the ID of the task.
This ID starts at 1 and is sequentially increasing. That is, the first task's id should be 1, the second task's id
should be 2, and so on. List<String> getAllTasks(int userId) Returns a list of all the tasks not marked as complete for
the user with ID userId, ordered by the due date. You should return an empty list if the user has no uncompleted tasks.
List<String> getTasksForTag(int userId, String tag) Returns a list of all the tasks that are not marked as complete for
the user with the ID userId and have tag as one of their tags, ordered by their due date. Return an empty list if no
such task exists. void completeTask(int userId, int taskId) Marks the task with the ID taskId as completed only if the
task exists and the user with the ID userId has this task, and it is uncompleted.


Example 1:

Input
["TodoList", "addTask", "addTask", "getAllTasks", "getAllTasks", "addTask", "getTasksForTag", "completeTask",
"completeTask", "getTasksForTag", "getAllTasks"]
[[], [1, "Task1", 50, []], [1, "Task2", 100, ["P1"]], [1], [5], [1, "Task3", 30, ["P1"]], [1, "P1"], [5, 1], [1, 2], [1,
"P1"], [1]] Output [null, 1, 2, ["Task1", "Task2"], [], 3, ["Task3", "Task2"], null, null, ["Task3"], ["Task3",
"Task1"]]

Explanation
TodoList todoList = new TodoList();
todoList.addTask(1, "Task1", 50, []); // return 1. This adds a new task for the user with id 1.
todoList.addTask(1, "Task2", 100, ["P1"]); // return 2. This adds another task for the user with id 1.
todoList.getAllTasks(1); // return ["Task1", "Task2"]. User 1 has two uncompleted tasks so far.
todoList.getAllTasks(5); // return []. User 5 does not have any tasks so far.
todoList.addTask(1, "Task3", 30, ["P1"]); // return 3. This adds another task for the user with id 1.
todoList.getTasksForTag(1, "P1"); // return ["Task3", "Task2"]. This returns the uncompleted tasks that have the tag
"P1" for the user with id 1. todoList.completeTask(5, 1); // This does nothing, since task 1 does not belong to user 5.
todoList.completeTask(1, 2); // This marks task 2 as completed.
todoList.getTasksForTag(1, "P1"); // return ["Task3"]. This returns the uncompleted tasks that have the tag "P1" for the
user with id 1.
                                  // Notice that we did not include "Task2" because it is completed now.
todoList.getAllTasks(1); // return ["Task3", "Task1"]. User 1 now has 2 uncompleted tasks.



Constraints:

1 <= userId, taskId, dueDate <= 100
0 <= tags.length <= 100
1 <= taskDescription.length <= 50
1 <= tags[i].length, tag.length <= 20
All dueDate values are unique.
All the strings consist of lowercase and uppercase English letters and digits.
At most 100 calls will be made for each method.
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

class Task {
public:
    int id_;
    int user_id_;
    string description_;
    int due_date_;
    bool done_;
    unordered_set<string> tags_;
};

struct myComp {
    bool operator()(pair<int, string>& a, pair<int, string>& b) {
        return a.first > b.first;
    }
};

class TodoList {
public:
    TodoList() {
        global_id_ = 0;
    }

    int addTask(int userId, string taskDescription, int dueDate, vector<string> tags) {
        global_id_ += 1;

        shared_ptr<Task> task = make_shared<Task>();
        task->id_ = global_id_;
        task->user_id_ = userId;
        task->description_ = taskDescription;
        task->due_date_ = dueDate;
        task->done_ = false;
        task->tags_.clear();
        task->tags_.insert(tags.begin(), tags.end());

        if (user_tasks_.find(userId) == user_tasks_.end()) {
            user_tasks_[userId] = unordered_map<int, shared_ptr<Task>>();
        }
        user_tasks_[userId][task->id_] = task;
        return task->id_;
    }

    vector<string> getAllTasks(int userId) {
        if (user_tasks_.find(userId) == user_tasks_.end()) {
            return vector<string>();
        }

        priority_queue<pair<int, string>, vector<pair<int, string>>, myComp> pq;
        for (auto it = user_tasks_[userId].begin(); it != user_tasks_[userId].end(); ++it) {
            pq.push({it->second->due_date_, it->second->description_});
        }

        vector<string> result;
        result.reserve(user_tasks_[userId].size());
        while (!pq.empty()) {
            result.push_back(pq.top().second);
            pq.pop();
        }
        return result;
    }

    vector<string> getTasksForTag(int userId, string tag) {
        if (user_tasks_.find(userId) == user_tasks_.end()) {
            return vector<string>();
        }

        priority_queue<pair<int, string>, vector<pair<int, string>>, myComp> pq;
        for (auto it = user_tasks_[userId].begin(); it != user_tasks_[userId].end(); ++it) {
            if (it->second->tags_.find(tag) == it->second->tags_.end()) {
                continue;
            }
            pq.push({it->second->due_date_, it->second->description_});
        }

        vector<string> result;
        result.reserve(user_tasks_[userId].size());
        while (!pq.empty()) {
            result.push_back(pq.top().second);
            pq.pop();
        }
        return result;
    }

    void completeTask(int userId, int taskId) {
        if (user_tasks_.find(userId) == user_tasks_.end()) {
            return;
        }

        if (user_tasks_[userId].find(taskId) == user_tasks_[userId].end()) {
            return;
        }

        user_tasks_[userId].erase(taskId);
    }
private:
    int global_id_;
    unordered_map<int, unordered_map<int, shared_ptr<Task>>> user_tasks_;
};

/**
 * Your TodoList object will be instantiated and called as such:
 * TodoList* obj = new TodoList();
 * int param_1 = obj->addTask(userId,taskDescription,dueDate,tags);
 * vector<string> param_2 = obj->getAllTasks(userId);
 * vector<string> param_3 = obj->getTasksForTag(userId,tag);
 * obj->completeTask(userId,taskId);
 */