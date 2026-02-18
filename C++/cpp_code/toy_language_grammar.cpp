/*
https://www.hack2hire.com/companies/openai/coding-questions/69166e4e10632c00111ca0ea/practice?questionId=69166e5710632c00111ca0eb
Toy Language Grammar

You are working with a toy language grammar that supports three kinds of types: primitives, generics, and tuples. This
system is used for defining function types, including parameter and return types.

Primitive types: "int", "char", "float"
Generic types: Strings following the pattern "T" plus a digit, such as "T1", "T2". A generic can stand for any type,
including a tuple. Tuple types: Represented as a list of types, for example ["int", "T1", "char"]. Tuples may be nested,
such as ["int", "char", ["int", "T1"]]. A Node represents either a primitive, a generic, or a tuple.

A Function is described by its parameter list, params, and its return type, returnType. Both parameters and return type
are represented as Node objects.

Your task is to implement the string representation of these types, following the exact format below:

Node.toString() returns a string for the type:

For a primitive or generic, return its value directly, such as "int" or "T2".
For a tuple, return its children in square brackets, separated by commas, such as "[int,T1,char]". There should be no
extra spaces between each child. Nested tuples must be handled recursively. Function.toString() returns the function
type as "[<param1>,<param2>,...] -> <returnType>", where parameters and return type are rendered using Node.toString().

Constraints:

All type names are valid.
The params list and tuple children may be empty.
Nesting is allowed to any depth within tuples.
Example 1:

Input: Node representing primitive type "int".
Output: "int"

Example 2:

Input: Node representing tuple ["int", "T1", "char"].
Output: "[int,T1,char]"

Example 3:

Input: Function with params ["int", "T1", ["int", "T2"]] and return type "T1"
Output: "[int,T1,[int,T2]] -> T1"


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
using namespace std;

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Node {
private:
    string value;        // for primitive or generic types
    vector<Node> tuple;  // for tuple types
    bool isTuple;

public:
    Node(string value) {
        this->value = value;
        this->isTuple = false;
    }

    Node(vector<Node> tuple) {
        this->tuple = tuple;
        this->isTuple = true;
    }

    string toString() {
        if (!isTuple) {
            return value;
        }

        string rst = "[";
        int cnt = tuple.size();
        for (int i = 0; i < cnt; i++) {
            rst += tuple[i].toString();
            if (i < cnt - 1) {
                rst += ",";
            }
        }
        rst += "]";
        return rst;
    }
};

class Function {
private:
    vector<Node> params;
    Node returnType;

public:
    Function(vector<Node> params, Node returnType) : params(params), returnType(returnType) {
    }

    string toString() {
        string rst = "[";
        int p_cnt = params.size();
        for (int i = 0; i < p_cnt; i++) {
            rst += params[i].toString();
            if (i < p_cnt - 1) {
                rst += ",";
            }
        }
        rst += "] -> " + returnType.toString();
        return rst;
    }
};

class Solution {
public:
    static void main() {
        nodeTest();
        functionTest();
    }

private:
    static void nodeTest() {
        cout << "===== Node Test =====" << endl;

        Node node1 = Node("int");
        cout << node1.toString() << endl;  // Expected: "int"

        Node node2 = Node("char");
        cout << node2.toString() << endl;  // Expected: "char"

        Node node3 = Node("float");
        cout << node3.toString() << endl;  // Expected: "float"

        Node node4 = Node("T1");
        cout << node4.toString() << endl;  // Expected: "T1"

        Node node7 = Node({Node("int"), Node("T1"), Node("char")});
        cout << node7.toString() << endl;  // Expected: "[int,T1,char]"

        Node node8 = Node({Node("float"), Node("T3")});
        cout << node8.toString() << endl;  // Expected: "[float,T3]"

        Node node9 = Node({Node("int"), Node("char"), Node({Node("int"), Node("T1")})});
        cout << node9.toString() << endl;  // Expected: "[int,char,[int,T1]]"

        Node node10 = Node({Node("int"), Node({Node("char"), Node({Node("float"), Node("T1")})})});
        cout << node10.toString() << endl;  // Expected: "[int,[char,[float,T1]]]"

        Node node11 = Node(
                {Node({Node("int"), Node("char")}), Node({Node("T1"), Node("T2")}), Node({Node("float"), Node("T3")})});
        cout << node11.toString() << endl;  // Expected: "[[int,char],[T1,T2],[float,T3]]"

        Node node12 = Node(vector<Node>{Node("int")});
        cout << node12.toString() << endl;  // Expected: "[int]"

        Node node13 = Node(vector<Node>());
        cout << node13.toString() << endl;  // Expected: "[]"

        Node node14 = Node(vector<Node>{Node(vector<Node>{Node("int")})});
        cout << node14.toString() << endl;  // Expected: "[[int]]"
    }

    static void functionTest() {
        cout << "\n===== Function Test =====" << endl;

        Function func1 = Function({Node("int"), Node("T1"), Node({Node("int"), Node("T2")})}, Node("T1"));
        cout << func1.toString() << endl;  // Expected: "[int,T1,[int,T2]] -> T1"

        Function func2 = Function({Node("char"), Node("float")}, Node("int"));
        cout << func2.toString() << endl;  // Expected: "[char,float] -> int"

        Function func3 = Function(
                {Node({Node("int"), Node("char")}), Node("T1"), Node({Node("float"), Node({Node("T2"), Node("T3")})})},
                Node({Node("int"), Node("T1")}));
        cout << func3.toString() << endl;  // Expected: "[[int,char],T1,[float,[T2,T3]]] -> [int,T1]"

        Function func4 = Function({Node("int")}, Node("char"));
        cout << func4.toString() << endl;  // Expected: "[int] -> char"

        Function func5 = Function(vector<Node>(), Node("int"));
        cout << func5.toString() << endl;  // Expected: "[] -> int"

        Function func6 = Function({Node("int"), Node(vector<Node>())}, Node("T1"));
        cout << func6.toString() << endl;  // Expected: "[int,[]] -> T1"

        Function func7 = Function({Node("int")}, Node(vector<Node>()));
        cout << func7.toString() << endl;  // Expected: "[int] -> []"
    }
};
