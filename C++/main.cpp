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
#include "design_excel_sum_formula.cpp"
using namespace std;

int main() {
    Excel exc(3, 'C');
    exc.set(1, 'A', 2);
    exc.sum(3, 'C', {"A1", "A1:B2"});
    exc.set(2, 'B', 2);
    exc.get(3, 'C');
    return 0;
}
