/*
https://leetcode.com/problems/print-foobar-alternately/description/
1115. Print FooBar Alternately

Suppose you are given the following code:

class FooBar {
  public void foo() {
    for (int i = 0; i < n; i++) {
      print("foo");
    }
  }

  public void bar() {
    for (int i = 0; i < n; i++) {
      print("bar");
    }
  }
}
The same instance of FooBar will be passed to two different threads:

thread A will call foo(), while
thread B will call bar().
Modify the given program to output "foobar" n times.



Example 1:

Input: n = 1
Output: "foobar"
Explanation: There are two threads being fired asynchronously. One of them calls foo(), while the other calls bar().
"foobar" is being output 1 time.
Example 2:

Input: n = 2
Output: "foobarfoobar"
Explanation: "foobar" is being output 2 times.


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
#include <climits>
#include <condition_variable>
#include <mutex>
using namespace std;

class FooBar {
private:
    int n_;
    mutex mtx_;
    condition_variable cv_;
    int cur_;

public:
    FooBar(int n) {
        this->n_ = n;
        this->cur_ = 0;
    }

    void foo(function<void()> printFoo) {
        for (int i = 0; i < n_; i++) {
            unique_lock<mutex> lk(mtx_);
            cv_.wait(lk, [&] { return cur_ % 2 == 0; });

            // printFoo() outputs "foo". Do not change or remove this line.
            printFoo();

            cur_ = cur_ + 1;
            lk.unlock();
            cv_.notify_all();
        }
    }

    void bar(function<void()> printBar) {
        for (int i = 0; i < n_; i++) {
            unique_lock<mutex> lk(mtx_);
            cv_.wait(lk, [&] { return cur_ % 2 == 1; });

            // printBar() outputs "bar". Do not change or remove this line.
            printBar();

            cur_ = cur_ + 1;
            lk.unlock();
            cv_.notify_all();
        }
    }
};
