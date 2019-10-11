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
import java.util.*;

class Vector2D {
    private Iterator<List<Integer>> listIterator;
    private Iterator<Integer> subIterator;

    private void advanceListIterator() {
        while (listIterator.hasNext()) {
            subIterator = listIterator.next().iterator();
            if (subIterator.hasNext()) {
                break;
            }
        }
    }

    public Vector2D(List<List<Integer>> vec2d) {
        this.listIterator = vec2d.iterator();
        advanceListIterator();
    }

    public int next() {
        if (!hasNext()) {
            throw new NoSuchElementException();
        }

        int result = subIterator.next();
        if (!subIterator.hasNext()) {
            advanceListIterator();
        }
        return result;
    }

    public boolean hasNext() {
        return subIterator != null && subIterator.hasNext();
    }
}
