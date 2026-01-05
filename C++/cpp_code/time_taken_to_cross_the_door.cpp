/*
https://leetcode.com/problems/time-taken-to-cross-the-door/description/
2534. Time Taken to Cross the Door

There are n persons numbered from 0 to n - 1 and a door. Each person can enter or exit through the door once, taking one
second.

You are given a non-decreasing integer array arrival of size n, where arrival[i] is the arrival time of the ith person
at the door. You are also given an array state of size n, where state[i] is 0 if person i wants to enter through the
door or 1 if they want to exit through the door.

If two or more persons want to use the door at the same time, they follow the following rules:

If the door was not used in the previous second, then the person who wants to exit goes first.
If the door was used in the previous second for entering, the person who wants to enter goes first.
If the door was used in the previous second for exiting, the person who wants to exit goes first.
If multiple persons want to go in the same direction, the person with the smallest index goes first.
Return an array answer of size n where answer[i] is the second at which the ith person crosses the door.

Note that:

Only one person can cross the door at each second.
A person may arrive at the door and wait without entering or exiting to follow the mentioned rules.


Example 1:

Input: arrival = [0,1,1,2,4], state = [0,1,0,0,1]
Output: [0,3,1,2,4]
Explanation: At each second we have the following:
- At t = 0: Person 0 is the only one who wants to enter, so they just enter through the door.
- At t = 1: Person 1 wants to exit, and person 2 wants to enter. Since the door was used the previous second for
entering, person 2 enters.
- At t = 2: Person 1 still wants to exit, and person 3 wants to enter. Since the door was used the previous second for
entering, person 3 enters.
- At t = 3: Person 1 is the only one who wants to exit, so they just exit through the door.
- At t = 4: Person 4 is the only one who wants to exit, so they just exit through the door.
Example 2:

Input: arrival = [0,0,0], state = [1,0,1]
Output: [0,2,1]
Explanation: At each second we have the following:
- At t = 0: Person 1 wants to enter while persons 0 and 2 want to exit. Since the door was not used in the previous
second, the persons who want to exit get to go first. Since person 0 has a smaller index, they exit first.
- At t = 1: Person 1 wants to enter, and person 2 wants to exit. Since the door was used in the previous second for
exiting, person 2 exits.
- At t = 2: Person 1 is the only one who wants to enter, so they just enter through the door.


Constraints:

n == arrival.length == state.length
1 <= n <= 105
0 <= arrival[i] <= n
arrival is sorted in non-decreasing order.
state[i] is either 0 or 1.
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <set>
using namespace std;
/*
Intuition
There can be 4 states at any time:
1) No one is at the door
2) Some people are exiting but no one is entering
3) Some people are entering but no one is exiting
4) There are people at both sides of the door

People at both sides will line up (i.e. form queues) when they arrive at the door. So, it feels natural to have two
queues represeting the lines at each side.

Once these are established the solution starts to take form.

The arrival array is already sorted. We just have to split it into two queues. We can assign arrival index as the id
number for that person. We also have to keep arrival times in queues

Then, for each point in time we are going to check if there is anyone waiting to go through the door by looking at the
queues. Since we kept arrival times in queues, we can compare the time to the arrival time of the front of each queue.
If it is earlier than the time of queue front, that means that person hasn't arrived yet.

The first three states are not complicated. For the last state, in order to decide who goes first we need a variable
keeping the previous state of the door.

We simply simulate each second while at least one queue is not empty. Each time someone goes through the door (states 2,
3 and 4) time is added to the results array.

Approach
create two queues with pair elements: one for entry one for exit.
pairs keep arrival time and id num
create a vector for result
t = 0 for time, door = 0 for door state enumaration: (0=unused, 1=entered, 2=exited)

iterate arrival: push {time, id} pairs to their respective que

loop while at least one que is not empty:

    if time is earlier than the front of either queue:
        no one has arrived at the door -> set door state to "not used"

    else if time is equal to or later than exit queue front, but earlier than enter queue front:
        no one is entering, people are waiting to exit ->
        person in front of the exit que exits, write time to result
        pop exit que, set door state to "exit"

    else if time is equal to or later than enter queue front, but earlier than exit queue front::
        no one is exiting, people are waiting to enter ->
        person in front of the enter que enters, write time to result
        pop enter que, set door state to "enter"

    else:
        people are waiting at both sides ->
        if door state is "exit" or "not used":
            person in front of the exit que exits, write time to result
            pop exit que, set door state to "exit"
        else:
            person in front of the enter que enters, write time to
            pop enter que, set door state to "enter"

    increment time
end while loop

return result
*/
class Solution {
public:
    vector<int> timeTaken(vector<int>& arrival, vector<int>& state) {
        int n = arrival.size();
        queue<pair<int, int>> enter_q, exit_q;
        for (int i = 0; i < n; i++) {
            if (state[i]) {
                exit_q.push({arrival[i], i});
            } else {
                enter_q.push({arrival[i], i});
            }
        }

        int cur_time = 0;
        int door = 0;
        vector<int> rst(n, 0);
        while (!exit_q.empty() || !enter_q.empty()) {
            if ((exit_q.empty() || exit_q.front().first > cur_time) &&
                (enter_q.empty() || enter_q.front().first > cur_time)) {
                door = 0;  // door not used
                cur_time += 1;
                continue;
            }

            if (!exit_q.empty() && exit_q.front().first <= cur_time &&
                (enter_q.empty() || enter_q.front().first > cur_time)) {
                rst[exit_q.front().second] = cur_time;
                door = 2;  // door used to exit
                exit_q.pop();
                cur_time += 1;
                continue;
            }

            if ((exit_q.empty() || exit_q.front().first > cur_time) && !enter_q.empty() &&
                enter_q.front().first <= cur_time) {
                rst[enter_q.front().second] = cur_time;
                door = 1;  // door used to enter
                enter_q.pop();
                cur_time += 1;
                continue;
            }

            if (door == 0 || door == 2) {
                rst[exit_q.front().second] = cur_time;
                door = 2;
                exit_q.pop();
            } else {
                rst[enter_q.front().second] = cur_time;
                door = 1;
                enter_q.pop();
            }
            cur_time += 1;
        }
        return rst;
    }
};
