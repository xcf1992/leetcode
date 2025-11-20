/*
https://leetcode.com/problems/print-zero-even-odd/description/
1116. Print Zero Even Odd

You have a function printNumber that can be called with an integer parameter and prints it to the console.

For example, calling printNumber(7) prints 7 to the console.
You are given an instance of the class ZeroEvenOdd that has three functions: zero, even, and odd. The same instance of
ZeroEvenOdd will be passed to three different threads:

Thread A: calls zero() that should only output 0's.
Thread B: calls even() that should only output even numbers.
Thread C: calls odd() that should only output odd numbers.
Modify the given class to output the series "010203040506..." where the length of the series must be 2n.

Implement the ZeroEvenOdd class:

ZeroEvenOdd(int n) Initializes the object with the number n that represents the numbers that should be printed.
void zero(printNumber) Calls printNumber to output one zero.
void even(printNumber) Calls printNumber to output one even number.
void odd(printNumber) Calls printNumber to output one odd number.


Example 1:

Input: n = 2
Output: "0102"
Explanation: There are three threads being fired asynchronously.
One of them calls zero(), the other calls even(), and the last one calls odd().
"0102" is the correct output.
Example 2:

Input: n = 5
Output: "0102030405"


Constraints:

1 <= n <= 1000
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
#include <numeric>
using namespace std;

class ZeroEvenOdd {
private:
    int n;
    sem_t sem_z, sem_o, sem_e;
public:
    ZeroEvenOdd(int n) : n(n) {
        sem_init(&sem_z, 0, 1);
        sem_init(&sem_o, 0, 0);
        sem_init(&sem_e, 0, 0);
    }
    void zero(function<void(int)> printNumber) {
        for (int i = 1; i <= n; ++i) {
            sem_wait(&sem_z);
            printNumber(0);
            if (i & 1) sem_post(&sem_o);
            else sem_post(&sem_e);
        }
    }
    void even(function<void(int)> printNumber) {
        for (int i = 2; i <= n; i += 2) {
            sem_wait(&sem_e);
            printNumber(i);
            sem_post(&sem_z);
        }
    }
    void odd(function<void(int)> printNumber) {
        for (int i = 1; i <= n; i += 2) {
            sem_wait(&sem_o);
            printNumber(i);
            sem_post(&sem_z);
        }
    }
    ~ZeroEvenOdd() {
        sem_destroy(&sem_z);
        sem_destroy(&sem_o);
        sem_destroy(&sem_e);
    }
};

class ZeroEvenOdd {
private:
    int n;
    std::condition_variable cv;
    std::mutex mtx;
    int nextState; // next state: 0 - zero, 1 - odd, 2 - even

public:
    ZeroEvenOdd(int n) {
        this->n = n;
        nextState = 0;
    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber) {
        for (int i = 0; i < n; i++) {
            std::unique_lock lk(mtx);
            cv.wait(lk, [&] { return nextState == 0; });
            printNumber(0);
            nextState = ((i % 2 == 0) ? 1 : 2); // calculate next state
            cv.notify_all();
        }
    }

    void even(function<void(int)> printNumber) {
        for (int i = 0; i < n / 2; i++) {
            std::unique_lock lk(mtx);
            cv.wait(lk, [&] { return nextState == 2; });
            printNumber(2 + i * 2);
            nextState = 0; // next state is print 0
            cv.notify_all();
        }
    }

    void odd(function<void(int)> printNumber) {
        for (int i = 0; i < n / 2 + (n % 2); i++) {
            std::unique_lock lk(mtx);
            cv.wait(lk, [&] { return nextState == 1; });
            printNumber(1 + i * 2);
            nextState = 0; // next state is print 0
            cv.notify_all();
        }
    }
};
