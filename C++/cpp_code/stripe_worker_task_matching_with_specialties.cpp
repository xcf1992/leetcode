/*
https://www.hack2hire.com/companies/stripe/coding-questions/697a5a4e2ae9e181e44b7b95/practice?questionId=697a5a552ae9e181e44b7b96
Worker-Task Matching with Specialties

You are designing a system to distribute a sequence of tasks among several workers, aiming to minimize the workload
difference between them. The input consists of a list of worker names and a list of tasks, where each task is defined by
a unique integer id and a positive integer duration.

Tasks are to be assigned sequentially, one at a time, in the given order. For each task, assign it to the worker whose
current total workload (the sum of durations for all previously assigned tasks) is the lowest among all workers. If more
than one worker has the minimum workload, choose the worker with the lexicographically smallest name.

Return a list of assignment strings in the format "<task_id>:<worker_name>". The order of the returned list can be
arbitrary.

Constraints:

1 ≤ workers.length ≤ 1000
1 ≤ tasks.length ≤ 1000
1 ≤ duration ≤ 1000
All worker names are unique, non-empty strings containing only lowercase English letters.
Example:

Input:
workers = ["alice", "bob", "carol"],
tasks =
[
  { "id": 1, "duration": 4 },
  { "id": 2, "duration": 2 },
  { "id": 3, "duration": 7 },
  { "id": 4, "duration": 1 }
]
Output: ["1:alice", "2:bob", "3:carol", "4:bob"]
Explanation:

Task 1 is assigned to "alice" because all workers start with workload 0, and "alice" is lexicographically smallest.
Task 2 is assigned to "bob" because "bob" and "carol" both have workload 0, and "bob" is lexicographically smaller.
Task 3 is assigned to "carol" because she has the minimum workload 0.
Task 4 is assigned to "bob" because after previous assignments, "bob" has the lowest workload among all workers.
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
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <any>
#include <set>

using namespace std;

class Task {
public:
    int id;
    int duration;
    Task(int id, int duration) : id(id), duration(duration) {
    }
};

class Worker {
public:
    int currentWorkload;
    string workerName;
    Worker(int currentWorkload, string workerName) : currentWorkload(currentWorkload), workerName(workerName) {
    }
};

struct WorkerComparator {
    bool operator()(const Worker& a, const Worker& b) {
        if (a.currentWorkload != b.currentWorkload)
            return a.currentWorkload > b.currentWorkload;
        return a.workerName > b.workerName;
    }
};

class Solution {
public:
    vector<string> assignTasks(vector<string> workers, vector<Task> tasks) {
        priority_queue<Worker, vector<Worker>, WorkerComparator> heap;

        for (const string& worker : workers) {
            heap.push(Worker(0, worker));
        }

        vector<string> result;
        for (const Task& task : tasks) {
            Worker cur = heap.top();
            heap.pop();

            result.push_back(to_string(task.id) + ":" + cur.workerName);
            heap.push(Worker(cur.currentWorkload + task.duration, cur.workerName));
        }
        return result;
    }
};

void printVector(const vector<string>& vec) {
    cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        cout << vec[i];
        if (i < vec.size() - 1)
            cout << ", ";
    }
    cout << "]" << endl;
}

void test1() {
    cout << "===== Test 1 =====" << endl;
    Solution solution;
    vector<string> workers = {"alice", "bob", "carol"};
    vector<Task> tasks = {Task(1, 4), Task(2, 2), Task(3, 7), Task(4, 1)};
    vector<string> res = solution.assignTasks(workers, tasks);
    printVector(res);  // Expected: [1:alice, 2:bob, 3:carol, 4:bob]
}

void test2() {
    cout << "===== Test 2 =====" << endl;
    Solution solution;
    vector<string> workers = {"alice", "bob"};
    vector<Task> tasks = {Task(1, 1), Task(2, 1), Task(3, 1)};
    vector<string> res = solution.assignTasks(workers, tasks);
    printVector(res);  // Expected: [1:alice, 2:bob, 3:alice]
}

void test3() {
    cout << "===== Test 3 =====" << endl;
    Solution solution;
    vector<string> workers = {"alice", "bob", "carol", "dave", "eve"};
    vector<Task> tasks = {Task(1, 10), Task(2, 5), Task(3, 3), Task(4, 8),
                          Task(5, 2),  Task(6, 7), Task(7, 1), Task(8, 4)};
    vector<string> res = solution.assignTasks(workers, tasks);
    printVector(res);  // Expected: [1:alice, 2:bob, 3:carol, 4:dave, 5:eve, 6:eve, 7:carol, 8:carol]
}

void test4() {
    cout << "===== Test 4 =====" << endl;
    Solution solution;
    vector<string> workers = {"alice"};
    vector<Task> tasks = {Task(1, 5), Task(2, 3), Task(3, 2)};
    vector<string> res = solution.assignTasks(workers, tasks);
    printVector(res);  // Expected: [1:alice, 2:alice, 3:alice]
}

void test5() {
    cout << "===== Test 5 =====" << endl;
    Solution solution;
    vector<string> workers = {"zebra", "alice", "bob"};
    vector<Task> tasks = {Task(1, 5), Task(2, 5), Task(3, 5)};
    vector<string> res = solution.assignTasks(workers, tasks);
    printVector(res);  // Expected: [1:alice, 2:bob, 3:zebra]
}

int main() {
    test1();
    test2();
    test3();
    test4();
    test5();
    return 0;
}

/*
Follow-up 1:
In this variation, each worker has one or more specialties, and every task specifies a single requiredSpecialty.

A task can be assigned only to a worker who possesses the required specialty. If no eligible worker is available for a
task, skip that task and do not include it in the output.

From the pool of qualified workers, assign the task to the worker with the lowest current total workload. If there is a
tie, select the worker whose name comes first lexicographically.

Return a list of task assignment strings in the format "<task_id>:<worker_name>", including only the tasks that were
successfully assigned. You may return the result in any order.

Constraints

0 ≤ worker.specialties.length ≤ 100
Example:

Input:
workers =
[
  { "name": "alice", "specialties": ["frontend", "backend"] },
  { "name": "bob", "specialties": ["backend"] },
  { "name": "carol", "specialties": ["frontend"] }
],
tasks =
[
  { "id": 1, "duration": 2, "requiredSpecialty": "frontend" },
  { "id": 2, "duration": 4, "requiredSpecialty": "backend" },
  { "id": 3, "duration": 1, "requiredSpecialty": "database" }
]

Output:
["1:alice", "2:bob"]

Explanation:

Task 1 requires "frontend". Eligible workers are "alice" and "carol", both with workload 0, so "alice" is chosen
(lexicographically smallest). Task 2 requires "backend". Eligible workers are "alice" (workload 2) and "bob" (workload
0), so "bob" is chosen. Task 3 requires "database", but no worker has this specialty.
 */
class Solution {
public:
    std::vector<std::string> assignTasks(std::vector<Worker>& workers, std::vector<Task>& tasks) {
        unordered_map<string, vector<string>> worker_to_specialties;
        unordered_map<string, set<pair<int, string>>> speciality_to_worker_load;
        for (Worker& w : workers) {
            worker_to_specialties[w.name] = w.specialties;
            for (string& skill : w.specialties) {
                if (speciality_to_worker_load.find(skill) == speciality_to_worker_load.end()) {
                    speciality_to_worker_load[skill] = set<pair<int, string>>();
                }
                speciality_to_worker_load[skill].insert(pair<int, string>(0, w.name));
            }
        }

        vector<std::string> result;
        for (Task& t : tasks) {
            string required = t.requiredSpecialty;
            if (speciality_to_worker_load.find(required) == speciality_to_worker_load.end()) {
                continue;
            }

            int cur_workload = speciality_to_worker_load[required].begin()->first;
            string worker_name = speciality_to_worker_load[required].begin()->second;
            int new_workload = cur_workload + t.duration;
            for (string& skill : worker_to_specialties[worker_name]) {
                speciality_to_worker_load[skill].erase({cur_workload, worker_name});
                speciality_to_worker_load[skill].insert(pair<int, string>(new_workload, worker_name));
            }
            result.push_back(std::to_string(t.id) + ":" + worker_name);
        }
        return result;
    }

    static void test1() {
        std::cout << "===== Test 1 =====" << std::endl;
        Solution solution;
        std::vector<Worker> workers;
        workers.push_back(Worker("alice", {"frontend", "backend"}));
        workers.push_back(Worker("bob", {"backend"}));
        workers.push_back(Worker("carol", {"frontend"}));

        std::vector<Task> tasks;
        tasks.push_back(Task(1, 2, "frontend"));
        tasks.push_back(Task(2, 4, "backend"));
        tasks.push_back(Task(3, 1, "database"));

        std::vector<std::string> res = solution.assignTasks(workers, tasks);
        std::cout << "[";
        for (size_t i = 0; i < res.size(); ++i) {
            std::cout << res[i];
            if (i < res.size() - 1)
                std::cout << ", ";
        }
        std::cout << "]" << std::endl;  // Expected: [1:alice, 2:bob]
    }

    static void test2() {
        std::cout << "===== Test 2 =====" << std::endl;
        Solution solution;
        std::vector<Worker> workers;
        workers.push_back(Worker("alice", {"backend"}));
        workers.push_back(Worker("bob", {"backend"}));
        workers.push_back(Worker("carol", {"backend"}));

        std::vector<Task> tasks;
        tasks.push_back(Task(1, 5, "backend"));
        tasks.push_back(Task(2, 5, "backend"));
        tasks.push_back(Task(3, 5, "backend"));
        tasks.push_back(Task(4, 1, "backend"));

        std::vector<std::string> res = solution.assignTasks(workers, tasks);
        std::cout << "[";
        for (size_t i = 0; i < res.size(); ++i) {
            std::cout << res[i];
            if (i < res.size() - 1)
                std::cout << ", ";
        }
        std::cout << "]" << std::endl;  // Expected: [1:alice, 2:bob, 3:carol, 4:alice]
    }

    static void test3() {
        std::cout << "===== Test 3 =====" << std::endl;
        Solution solution;
        std::vector<Worker> workers;
        workers.push_back(Worker("alice", {"frontend", "backend", "devops"}));
        workers.push_back(Worker("bob", {"backend", "database"}));
        workers.push_back(Worker("carol", {"frontend"}));
        workers.push_back(Worker("dave", {"devops", "database"}));

        std::vector<Task> tasks;
        tasks.push_back(Task(1, 10, "frontend"));
        tasks.push_back(Task(2, 5, "backend"));
        tasks.push_back(Task(3, 3, "database"));
        tasks.push_back(Task(4, 8, "devops"));
        tasks.push_back(Task(5, 2, "frontend"));
        tasks.push_back(Task(6, 7, "backend"));
        tasks.push_back(Task(7, 1, "database"));
        tasks.push_back(Task(8, 4, "devops"));

        std::vector<std::string> res = solution.assignTasks(workers, tasks);
        std::cout << "[";
        for (size_t i = 0; i < res.size(); ++i) {
            std::cout << res[i];
            if (i < res.size() - 1)
                std::cout << ", ";
        }
        std::cout << "]" << std::endl;  // Expected: [1:alice, 2:bob, 3:dave, 4:dave, 5:carol, 6:bob, 7:dave, 8:alice]
    }

    static void test4() {
        std::cout << "===== Test 4 =====" << std::endl;
        Solution solution;
        std::vector<Worker> workers;
        workers.push_back(Worker("alice", {"frontend"}));
        workers.push_back(Worker("bob", {"backend"}));
        workers.push_back(Worker("carol", {"frontend", "backend"}));

        std::vector<Task> tasks;
        tasks.push_back(Task(1, 5, "frontend"));
        tasks.push_back(Task(2, 10, "backend"));
        tasks.push_back(Task(3, 3, "frontend"));
        tasks.push_back(Task(4, 2, "backend"));
        tasks.push_back(Task(5, 1, "frontend"));
        tasks.push_back(Task(6, 8, "backend"));

        std::vector<std::string> res = solution.assignTasks(workers, tasks);
        std::cout << "[";
        for (size_t i = 0; i < res.size(); ++i) {
            std::cout << res[i];
            if (i < res.size() - 1)
                std::cout << ", ";
        }
        std::cout << "]" << std::endl;  // Expected: [1:alice, 2:bob, 3:carol, 4:carol, 5:alice, 6:carol]
    }

    static void test5() {
        std::cout << "===== Test 5 =====" << std::endl;
        Solution solution;
        std::vector<Worker> workers;
        workers.push_back(Worker("alice", {"frontend"}));
        workers.push_back(Worker("bob", {"backend"}));
        workers.push_back(Worker("carol", {}));

        std::vector<Task> tasks;
        tasks.push_back(Task(1, 5, "database"));
        tasks.push_back(Task(2, 3, "devops"));
        tasks.push_back(Task(3, 2, "ml"));

        std::vector<std::string> res = solution.assignTasks(workers, tasks);
        std::cout << "[";
        for (size_t i = 0; i < res.size(); ++i) {
            std::cout << res[i];
            if (i < res.size() - 1)
                std::cout << ", ";
        }
        std::cout << "]" << std::endl;  // Expected: []
    }
};

int main() {
    Solution::test1();
    Solution::test2();
    Solution::test3();
    Solution::test4();
    Solution::test5();
    return 0;
}

/*
Follow-up 2:
Each task now has an account field, indicating the internal account required to complete the work. To reduce operational
overhead and maintain security, it is important to minimize unnecessary transfers of account ownership between workers.
Since switching accounts often can lead to extra administrative steps and potential risk.

Assignments should follow these updated rules:

If a worker has previously been assigned any task with a particular account and has the required specialty for the
current task, all future tasks for that account must be assigned to this worker (regardless of current workload). If the
previous handler of the account does not have the required specialty, or if no worker has handled the account yet,
assign the task to an eligible worker with the lowest total workload. If there is a tie, pick the worker whose name
comes first lexicographically. If no worker is eligible for a given task, skip it and exclude it from the output. Return
a list of task assignment strings in the format "<task_id>:<worker_name>", including only the tasks that were
successfully assigned. You may return the result in any order.

Example:

Input:
workers =
[
  { "name": "alice", "specialties": ["frontend", "backend"] },
  { "name": "bob", "specialties": ["backend"] },
  { "name": "carol", "specialties": ["frontend"] }
],
tasks =
[
  { "id": 1, "duration": 2, "requiredSpecialty": "frontend", "account": "acct1" },
  { "id": 2, "duration": 4, "requiredSpecialty": "backend", "account": "acct2" },
  { "id": 3, "duration": 3, "requiredSpecialty": "frontend", "account": "acct1" }
]

Output:
["1:alice", "2:bob", "3:alice"]

Explanation:

Task 1 is assigned to "alice". Account mapping becomes: "acct1 -> alice".
Task 2 requires "backend" and is assigned to "bob"). Account mapping becomes: "acct2 -> bob".
Task 3 has account "acct1". The previous handler is "alice", and she has all the required specialty, task 3 must be
assigned to "alice" regardless of workload.
 */
struct Task {
    int id;
    int duration;
    std::string requiredSpecialty;
    std::string account;

    Task(int id, int duration, std::string requiredSpecialty, std::string account)
            : id(id), duration(duration), requiredSpecialty(requiredSpecialty), account(account) {
    }
};

struct Worker {
    std::string name;
    std::vector<std::string> specialties;

    Worker(std::string name, std::vector<std::string> specialties) : name(name), specialties(specialties) {
    }
};

struct Entry {
    int currentWorkload;
    std::string workerName;

    Entry(int currentWorkload, std::string workerName) : currentWorkload(currentWorkload), workerName(workerName) {
    }
};

struct EntryComparator {
    bool operator()(const Entry& a, const Entry& b) const {
        if (a.currentWorkload != b.currentWorkload) {
            return a.currentWorkload > b.currentWorkload;
        }
        return a.workerName > b.workerName;
    }
};

class Solution {
public:
    std::vector<std::string> assignTasks(std::vector<Worker>& workers, std::vector<Task>& tasks) {
        std::unordered_map<std::string, int> worker_to_load;
        std::unordered_map<std::string, std::unordered_set<std::string>> worker_to_spec;
        std::unordered_map<std::string, std::priority_queue<Entry, std::vector<Entry>, EntryComparator>> spec_heap;
        std::unordered_map<std::string, std::string> acc_to_worker;

        // Initialize all mappings
        for (const Worker& worker : workers) {
            worker_to_load[worker.name] = 0;
            worker_to_spec[worker.name] =
                    std::unordered_set<std::string>(worker.specialties.begin(), worker.specialties.end());
            for (const std::string& spec : worker.specialties) {
                if (spec_heap.find(spec) == spec_heap.end()) {
                    spec_heap[spec] = std::priority_queue<Entry, std::vector<Entry>, EntryComparator>();
                }
                spec_heap[spec].push(Entry(0, worker.name));
            }
        }

        std::vector<std::string> result;
        for (const Task& task : tasks) {
            std::string chosen = "";

            if (acc_to_worker.find(task.account) != acc_to_worker.end()) {
                std::string mappedWorker = acc_to_worker[task.account];
                if (worker_to_spec.find(mappedWorker) != worker_to_spec.end() &&
                    worker_to_spec[mappedWorker].find(task.requiredSpecialty) != worker_to_spec[mappedWorker].end()) {
                    chosen = mappedWorker;
                }
            }

            // Fallback to heap selection
            if (chosen.empty()) {
                if (spec_heap.find(task.requiredSpecialty) == spec_heap.end()) {
                    continue;
                }

                std::priority_queue<Entry, std::vector<Entry>, EntryComparator>& heap =
                        spec_heap[task.requiredSpecialty];
                // Remove stale entries
                while (!heap.empty() && heap.top().currentWorkload != worker_to_load[heap.top().workerName]) {
                    heap.pop();
                }

                if (heap.empty()) {
                    continue;
                }

                chosen = heap.top().workerName;
                heap.pop();
            }

            result.push_back(std::to_string(task.id) + ":" + chosen);
            worker_to_load[chosen] = worker_to_load[chosen] + task.duration;
            acc_to_worker[task.account] = chosen;

            // Push updated workload to all relevant specialty heaps
            for (const std::string& spec : worker_to_spec[chosen]) {
                spec_heap[spec].push(Entry(worker_to_load[chosen], chosen));
            }
        }
        return result;
    }

    static void test1() {
        std::cout << "===== Test 1 =====" << std::endl;
        Solution solution;
        std::vector<Worker> workers;
        workers.push_back(Worker("alice", {"frontend", "backend"}));
        workers.push_back(Worker("bob", {"backend"}));
        workers.push_back(Worker("carol", {"frontend"}));
        std::vector<Task> tasks;
        tasks.push_back(Task(1, 2, "frontend", "acct1"));
        tasks.push_back(Task(2, 4, "backend", "acct2"));
        tasks.push_back(Task(3, 3, "frontend", "acct1"));
        std::vector<std::string> res = solution.assignTasks(workers, tasks);
        for (const std::string& s : res) {
            std::cout << s << " ";
        }
        std::cout << std::endl;  // Expected: [1:alice, 2:bob, 3:alice]
    }

    static void test2() {
        std::cout << "===== Test 2 =====" << std::endl;
        Solution solution;
        std::vector<Worker> workers;
        workers.push_back(Worker("alice", {"backend"}));
        workers.push_back(Worker("bob", {"backend"}));
        workers.push_back(Worker("carol", {"backend"}));
        std::vector<Task> tasks;
        tasks.push_back(Task(1, 10, "backend", "acct1"));
        tasks.push_back(Task(2, 5, "backend", "acct2"));
        tasks.push_back(Task(3, 1, "backend", "acct1"));
        tasks.push_back(Task(4, 8, "backend", "acct2"));
        std::vector<std::string> res = solution.assignTasks(workers, tasks);
        for (const std::string& s : res) {
            std::cout << s << " ";
        }
        std::cout << std::endl;  // Expected: [1:alice, 2:bob, 3:alice, 4:bob]
    }

    static void test3() {
        std::cout << "===== Test 3 =====" << std::endl;
        Solution solution;
        std::vector<Worker> workers;
        workers.push_back(Worker("alice", {"frontend", "backend"}));
        workers.push_back(Worker("bob", {"backend", "database"}));
        workers.push_back(Worker("carol", {"frontend", "database"}));
        workers.push_back(Worker("dave", {"devops"}));
        std::vector<Task> tasks;
        tasks.push_back(Task(1, 5, "frontend", "acct1"));
        tasks.push_back(Task(2, 3, "backend", "acct2"));
        tasks.push_back(Task(3, 2, "database", "acct3"));
        tasks.push_back(Task(4, 4, "frontend", "acct1"));
        tasks.push_back(Task(5, 1, "backend", "acct2"));
        tasks.push_back(Task(6, 6, "database", "acct3"));
        tasks.push_back(Task(7, 2, "devops", "acct4"));
        std::vector<std::string> res = solution.assignTasks(workers, tasks);
        for (const std::string& s : res) {
            std::cout << s << " ";
        }
        std::cout << std::endl;  // Expected: [1:alice, 2:bob, 3:carol, 4:alice, 5:bob, 6:carol, 7:dave]
    }

    static void test4() {
        std::cout << "===== Test 4 =====" << std::endl;
        Solution solution;
        std::vector<Worker> workers;
        workers.push_back(Worker("alice", {"frontend"}));
        workers.push_back(Worker("bob", {"backend"}));
        workers.push_back(Worker("carol", {"frontend", "backend"}));
        std::vector<Task> tasks;
        tasks.push_back(Task(1, 5, "frontend", "acct1"));
        tasks.push_back(Task(2, 3, "backend", "acct1"));
        tasks.push_back(Task(3, 2, "frontend", "acct1"));
        std::vector<std::string> res = solution.assignTasks(workers, tasks);
        for (const std::string& s : res) {
            std::cout << s << " ";
        }
        std::cout << std::endl;  // Expected: [1:alice, 2:bob, 3:carol]
    }

    static void test5() {
        std::cout << "===== Test 5 =====" << std::endl;
        Solution solution;
        std::vector<Worker> workers;
        workers.push_back(Worker("alice", {"frontend"}));
        workers.push_back(Worker("bob", {"backend"}));
        workers.push_back(Worker("carol", {}));
        std::vector<Task> tasks;
        tasks.push_back(Task(1, 5, "database", "acct1"));
        tasks.push_back(Task(2, 3, "devops", "acct2"));
        tasks.push_back(Task(3, 2, "ml", "acct3"));
        std::vector<std::string> res = solution.assignTasks(workers, tasks);
        for (const std::string& s : res) {
            std::cout << s << " ";
        }
        std::cout << std::endl;  // Expected: []
    }

    static void test6() {
        std::cout << "===== Test 6 =====" << std::endl;
        Solution solution;
        std::vector<Worker> workers;
        workers.push_back(Worker("alice", {"frontend", "backend"}));
        workers.push_back(Worker("bob", {"backend", "database"}));
        workers.push_back(Worker("carol", {"frontend"}));
        workers.push_back(Worker("dave", {"database", "devops"}));
        workers.push_back(Worker("erin", {"devops", "frontend"}));
        std::vector<Task> tasks;
        tasks.push_back(Task(1, 3, "frontend", "acct1"));
        tasks.push_back(Task(2, 4, "backend", "acct2"));
        tasks.push_back(Task(3, 2, "frontend", "acct1"));
        tasks.push_back(Task(4, 5, "database", "acct3"));
        tasks.push_back(Task(5, 1, "backend", "acct1"));
        tasks.push_back(Task(6, 2, "devops", "acct2"));
        tasks.push_back(Task(7, 3, "devops", "acct2"));
        tasks.push_back(Task(8, 1, "devops", "acct5"));
        tasks.push_back(Task(9, 1, "database", "acct2"));
        tasks.push_back(Task(10, 2, "database", "acct2"));
        tasks.push_back(Task(11, 4, "frontend", "acct2"));
        tasks.push_back(Task(12, 1, "backend", "acct2"));
        tasks.push_back(Task(13, 2, "ml", "acct4"));
        tasks.push_back(Task(14, 1, "database", "acct3"));
        tasks.push_back(Task(15, 3, "frontend", "acct3"));
        tasks.push_back(Task(16, 2, "frontend", "acct3"));
        std::vector<std::string> res = solution.assignTasks(workers, tasks);
        for (const std::string& s : res) {
            std::cout << s << " ";
        }
        std::cout << std::endl;
        // Expected: [1:alice, 2:bob, 3:alice, 4:dave, 5:alice, 6:erin, 7:erin,
        // 8:dave, 9:bob, 10:bob, 11:carol, 12:alice, 14:dave, 15:carol, 16:carol]
    }
};

int main() {
    Solution::test1();
    Solution::test2();
    Solution::test3();
    Solution::test4();
    Solution::test5();
    Solution::test6();
    return 0;
}