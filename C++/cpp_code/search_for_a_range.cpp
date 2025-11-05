#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

vector<int> findTarget(int left, int right, int A[], int target) {
    vector<int> range;
    range.clear();

    if (left == right) {
        if (A[left] == target) {
            range.push_back(left);
            range.push_back(right);
            return range;
        } else {
            range.push_back(-1);
            range.push_back(-1);
            return range;
        }
    }


    if (left > right) {
        range.push_back(-1);
        range.push_back(-1);
        return range;
    }

    int middle = (left + right) / 2;
    if (A[middle] < target) {
        return findTarget(middle + 1, right, A, target);
    } else if (A[middle] > target) {
        return findTarget(left, middle - 1, A, target);
    }

    vector<int> l(findTarget(left, middle - 1, A, target));
    vector<int> r(findTarget(middle + 1, right, A, target));
    range.push_back(l.at(0));
    range.push_back(r.at(1));

    return range;
}

vector<int> searchRange(int A[], int n, int target) {
    vector<int> range;
    range.clear();
    if (n == 0) {
        range.push_back(-1);
        range.push_back(-1);
        return range;
    }

    if (n == 1) {
        if (A[0] == target) {
            range.push_back(0);
            range.push_back(0);
            return range;
        } else {
            range.push_back(-1);
            range.push_back(-1);
            return range;
        }
    }

    int middle = n / 2;
    if (A[middle] > target) {
        return findTarget(0, middle - 1, A, target);
    } else if (A[middle] < target) {
        return findTarget(middle + 1, n, A, target);
    }

    vector<int> left(findTarget(0, middle - 1, A, target));
    vector<int> right(findTarget(middle + 1, n, A, target));
    range.push_back(left.at(0));
    range.push_back(right.at(1));

    return range;
}


int main() {
    int A[2] = {2, 2};
    vector<int> result = searchRange(A, 2, 2);
    cout << 1 / 2 << endl;
    return 0;
}