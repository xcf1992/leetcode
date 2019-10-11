/*
341. Flatten Nested List Iterator
https://leetcode.com/problems/flatten-nested-list-iterator/

Given a nested list of integers, implement an iterator to flatten it.
Each element is either an integer, or a list -- whose elements may also be integers or other lists.

Example 1:
Input: [[1,1],2,[1,1]]
Output: [1,1,2,1,1]
Explanation: By calling next repeatedly until hasNext returns false,
             the order of elements returned by next should be: [1,1,2,1,1].

Example 2:
Input: [1,[4,[6]]]
Output: [1,4,6]
Explanation: By calling next repeatedly until hasNext returns false,
             the order of elements returned by next should be: [1,4,6].

*/
import java.util.Iterator;
import java.util.List;
import java.util.NoSuchElementException;
import java.util.Stack;

public class NestedIterator implements Iterator<Integer> {
    private Stack<NestedInteger> stk = new Stack<>();

    public NestedIterator(List<NestedInteger> nestedList) {
        for (int i = nestedList.size() - 1; i >= 0; --i) {
            stk.push(nestedList.get(i));
        }
    }

    @Override
    public Integer next() {
        if (!hasNext()) {
            throw new NoSuchElementException();
        }
        return stk.pop().getInteger();
    }

    @Override
    public boolean hasNext() {
        while (!stk.empty()) {
            NestedInteger cur = stk.peek();
            if (cur.isInteger()) {
                return true;
            }

            stk.pop();
            List<NestedInteger> curArr = cur.getList();
            for (int i = curArr.size() - 1; i >= 0; --i) {
                stk.push(curArr.get(i));
            }
        }
        return false;
    }
}
