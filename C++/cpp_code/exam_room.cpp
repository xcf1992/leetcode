/*
855. Exam Room

In an exam room, there are N seats in a single row, numbered 0, 1, 2, ..., N-1.

When a student enters the room,
they must sit in the seat that maximizes the distance to the closest person.
If there are multiple such seats, they sit in the seat with the lowest number.
(Also, if no one is in the room, then the student sits at seat number 0.)

Return a class ExamRoom(int N) that exposes two functions:
ExamRoom.seat() returning an int representing what seat the student sat in,
and ExamRoom.leave(int p) representing that the student in seat number p now leaves the room.
It is guaranteed that any calls to ExamRoom.leave(p) have a student sitting in seat p.

Example 1:
Input: ["ExamRoom","seat","seat","seat","seat","leave","seat"], [[10],[],[],[],[],[4],[]]
Output: [null,0,9,4,2,null,5]
Explanation:
ExamRoom(10) -> null
seat() -> 0, no one is in the room, then the student sits at seat number 0.
seat() -> 9, the student sits at the last seat number 9.
seat() -> 4, the student sits at the last seat number 4.
seat() -> 2, the student sits at the last seat number 2.
leave(4) -> null
seat() -> 5, the student​​​​​​​ sits at the last seat number 5.
​​​​​​​
Note:
1 <= N <= 10^9
ExamRoom.seat() and ExamRoom.leave() will be called at most 10^4 times across all test cases.
Calls to ExamRoom.leave(p) are guaranteed to have a student currently sitting in seat number p.
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
#include <set>
using namespace std;

class ExamRoom {
private:
    int num;
    vector<int> seats;

public:
    ExamRoom(int N) {
        num = N;
    }

    int seat() {
        if (seats.size() == 0) {
            seats.push_back(0);
            return 0;
        }

        int pos = 0;
        int index = 0; // the index of seats where we will insert the new student
        int distance = seats[0];
        if (num - 1 - seats.back() > distance) {
            pos = num - 1;
            index = seats.size();
            distance = num - 1 - seats.back();
        }

        for (int i = 0; i < seats.size() - 1; i++) {
            if ((seats[i + 1] - seats[i]) / 2 > distance or(
                (seats[i + 1] - seats[i]) / 2 == distance and(seats[i + 1] + seats[i]) / 2 < pos)
            )
            {
                distance = (seats[i + 1] - seats[i]) / 2;
                pos = seats[i] + distance;
                index = i + 1;
            }
        }
        seats.insert(seats.begin() + index, pos);
        return pos;
    }

    void leave(int p) {
        for (auto it = seats.begin(); it != seats.end(); it++)
            if (*it == p) {
                seats.erase(it);
                return;
            }
    }
};

class ExamRoom1 {
private:
    int num;
    int taken;
    vector<int> seats;

public:
    ExamRoom1(int N) {
        num = N;
        taken = 0;
        seats.resize(num, 0);
    }

    int seat() {
        if (taken == 0) {
            seats[0] = 1;
            taken += 1;
            return 0;
        }

        int pre = -1;
        int next = -1;
        int pos = -1;
        int distance = -1;
        for (int i = 0; i < num; i++) {
            if (seats[i] == 1) {
                if (pre == -1) {
                    pre = i;
                } else if (next == -1) {
                    next = i;
                    int newSeat = pre + (next - pre) / 2;
                    if (pos == -1 or distance<min(newSeat - pre, next - newSeat)
                    )
                    {
                        pos = newSeat;
                        distance = min(newSeat - pre, next - newSeat);
                    }
                    pre = next;
                    next = -1;
                }
            }
        }

        if (next == -1) {
            if (pos == -1) {
                pos = 0;
                distance = pre;
            }
            if (distance < num - 1 - pre) {
                pos = num - 1;
            }
        }
        seats[pos] = 1;
        taken += 1;
        return pos;
    }

    void leave(int p) {
        taken -= 1;
        seats[p] = 0;
    }
};

/*
 * Your ExamRoom object will be instantiated and called as such:
 * ExamRoom obj = new ExamRoom(N);
 * int param_1 = obj.seat();
 * obj.leave(p);
*/