/*
251. Flatten 2D Vector
https://leetcode.com/problems/flatten-2d-vector/

Design and implement an iterator to flatten a 2d vector.
It should support the following operations: next and hasNext.

Example:
Vector2D iterator = new Vector2D([[1,2],[3],[4]]);
iterator.next(); // return 1
iterator.next(); // return 2
iterator.next(); // return 3
iterator.hasNext(); // return true
iterator.hasNext(); // return true
iterator.next(); // return 4
iterator.hasNext(); // return false

Notes:
Please remember to RESET your class variables declared in Vector2D,
as static/class variables are persisted across multiple test cases.
Please see here for more details.
You may assume that next() call will always be valid,
that is, there will be at least a next element in the 2d vector when next() is called.

Follow up:
As an added challenge, try to code it using only iterators in C++ or iterators in Java.
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

class Vector2D {
private:
    vector<vector<int> >::iterator rowIt;
    vector<vector<int> >::iterator rowEnd;
    vector<int>::iterator colIt;

public:
    Vector2D(vector<vector<int> > &vec2d) {
        rowIt = vec2d.begin();
        rowEnd = vec2d.end();
        if (rowIt != rowEnd) {
            colIt = rowIt->begin();
        }
    }

    int next() {
        hasNext(); // check before get the value
        int i = *colIt;
        colIt += 1;
        return i;
    }

    bool hasNext() {
        while (rowIt != rowEnd and colIt
        ==
        rowIt->end()
        )
        {
            rowIt += 1;
            if (rowIt != rowEnd) {
                colIt = rowIt->begin();
            }
        }
        return rowIt != rowEnd;
    }
};

/*
* Your Vector2D object will be instantiated and called as such:
* Vector2D i(vec2d);
* while (i.hasNext()) cout << i.next();
*/