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
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <regex>
using namespace std;

/*
Follow-up:
You are working with the same Node and Function type system described previously, which includes primitive types,
generics, and arbitrarily nested tuple types.

Your task is to implement a type inference utility:

Node inferReturnType(Function function, List<Node> params)
Given a function definition function and a list of concrete argument types params, this helper must:

Validate whether params align with the function's parameter types, allowing generics in the function signature to be
mapped to concrete types. If the match is successful, determine and return the concrete return type by substituting
generics in the return type according to these mappings. If there is any type mismatch, return null. A valid match
requires:

The number of arguments and parameters to be identical.
Generics in the function definition can appear in parameters or the return type, either directly or nested inside
tuples. Primitive type mismatches (such as "int" versus "char") are considered failures. Each generic name must be
consistently bound to a single concrete type throughout the entire matching process. Any scenario where the same generic
would need to represent conflicting types (for example, both "int" and "char", or tuples with different structures)
should result in a mismatch. Tuple types are matched recursively: the tuple's structure, arity (the number of elements),
and the types of each nested element (including deeply nested tuples) must all align exactly. Your solution should infer
and return the concrete return type for the given invocation if possible, or null if the arguments do not satisfy the
rules above.

Constraints:

Both the function parameter list and the input params may contain arbitrarily nested tuples, but params are always
concrete. Each tuple contains at most 100 elements. Primitive types are limited to "int", "char", "float". All other
non-tuple type names must be valid generics of the form "T" followed by a digit. Generics may be reused multiple times
anywhere in the function definition, including nested tuples and the return type. Example 1:

Input: Function: ["T1", "T2", "int", "T1"] -> ["T1", "T2"], params = ["int", "char", "int", "int"]
Output: A node stringified as "[int,char]"
Explanation: "T1" is bound to "int" (positions 1 and 4), "T2" is bound to "char". Substituting these bindings into the
return type ["T1", "T2"] yields ["int", "char"].

Example 2:

Input: Function: ["int", "T1", ["T2", "int"]] -> "T1", params = ["int", ["int", "str"], ["float", "int"]]
Output: A node stringified as "[int,str]"

Example 3:

Input: Function: ["T1", "T2", "int", "T1"] -> ["T1", "T2"], params = ["int", "int", "int", "char"]
Output: null
 */
class Node {
private:
    string value;        // for primitive or generic types
    vector<Node> tuple;  // for tuple types
    bool is_tuple_;

public:
    // Default constructor needed for std::map<std::string, Node>
    Node() : value(""), is_tuple_(false) {}

    Node(string value) {
        this->value = value;
        this->is_tuple_ = false;
    }

    Node(vector<Node> tuple) {
        this->tuple = tuple;
        this->is_tuple_ = true;
    }

    bool isTuple() const {
        return is_tuple_;
    }

    std::string getValue() const {
        return value;
    }

    std::vector<Node> getTuple() const {
        return tuple;
    }

    string toString() {
        if (!is_tuple_) {
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

    std::vector<Node> getParams() {
        return params;
    }

    Node getReturnType() {
        return returnType;
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

class Solution1 {
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

class Solution {
private:
        static bool isGeneric(std::string value) {
        std::regex pattern("T\\d+");
        return std::regex_match(value, pattern);
    }

    static bool typesEqual(Node a, Node b) {
        if (a.isTuple() && b.isTuple()) {
            std::vector<Node> aTuple = a.getTuple();
            std::vector<Node> bTuple = b.getTuple();
            if (aTuple.size() != bTuple.size()) {
                return false;
            }
            for (int i = 0; i < (int)aTuple.size(); i++) {
                if (!typesEqual(aTuple[i], bTuple[i])) {
                    return false;
                }
            }
            return true;
        } else if (!a.isTuple() && !b.isTuple()) {
            return a.getValue() == b.getValue();
        } else {
            return false;
        }
    }

    // Unify expected type (may contain generics) with actual type (concrete)
    // Returns true if successful, false if there is a mismatch
    static bool unify(Node expected, Node actual, std::map<std::string, Node>& bindings) {
        if (expected.isTuple()) {
            // Expected is a tuple, actual must also be a tuple with same arity
            if (!actual.isTuple()) {
                return false;
            }

            std::vector<Node> expectedTuple = expected.getTuple();
            std::vector<Node> actualTuple = actual.getTuple();
            if (expectedTuple.size() != actualTuple.size()) {
                return false;
            }

            // Recursively unify each element
            for (int i = 0; i < (int)expectedTuple.size(); i++) {
                if (!unify(expectedTuple[i], actualTuple[i], bindings)) {
                    return false;
                }
            }

            return true;
        } else if (isGeneric(expected.getValue())) {
            // Expected is a generic type variable
            std::string genericName = expected.getValue();
            if (bindings.find(genericName) != bindings.end()) {
                // Generic already bound, check consistency
                Node existingBinding = bindings[genericName];
                if (!typesEqual(existingBinding, actual)) {
                    return false;
                }
            } else {
                // Bind the generic to the actual type reference
                bindings[genericName] = actual;
            }
            return true;
        } else {
            // Expected is a concrete primitive type
            if (actual.isTuple()) {
                return false;
            }
            if (expected.getValue() != actual.getValue()) {
                return false;
            }
            return true;
        }
    }

    // Substitute generics in a type with their bound values
    static Node* substitute(Node type, std::map<std::string, Node>& bindings) {
        if (type.isTuple()) {
            // Substitute in each element of the tuple
            std::vector<Node> substitutedTuple;
            for (Node child : type.getTuple()) {
                Node* substituted = substitute(child, bindings);
                if (substituted == nullptr) {
                    return nullptr;
                }
                substitutedTuple.push_back(*substituted);
                delete substituted;
            }
            return new Node(substitutedTuple);
        } else if (isGeneric(type.getValue())) {
            // Replace generic with its binding
            std::string genericName = type.getValue();
            if (bindings.find(genericName) == bindings.end()) {
                return nullptr;
            }
            return new Node(bindings[genericName]);
        } else {
            // Concrete type, return as is
            return new Node(type.getValue());
        }
    }

public:
    static Node* inferReturnType(Function function, std::vector<Node> params) {
        std::vector<Node> expectedParams = function.getParams();

        // Check arity
        if (expectedParams.size() != params.size()) {
            return nullptr;
        }

        // Build bindings map by unifying each parameter
        std::map<std::string, Node> bindings;
        for (int i = 0; i < (int)expectedParams.size(); i++) {
            if (!unify(expectedParams[i], params[i], bindings)) {
                return nullptr;
            }
        }

        // Substitute generics in return type with their bindings
        return substitute(function.getReturnType(), bindings);
    }

public:
    static void test1() {
        std::cout << "===== Test 1 =====" << std::endl;
        // Function: [T1, T2, int, T1] -> [T1, T2].
        // Params: [int, char, int, int]
        Function func({Node("T1"), Node("T2"), Node("int"), Node("T1")},
                Node({Node("T1"), Node("T2")}));
        std::vector<Node> params = {Node("int"), Node("char"), Node("int"), Node("int")};
        Node* result = inferReturnType(func, params);
        if (result != nullptr) {
            std::cout << result->toString() << std::endl; // Expected: "[int,char]"
            delete result;
        } else {
            std::cout << "null" << std::endl;
        }
    }

    static void test2() {
        std::cout << "\n===== Test 2 =====" << std::endl;
        // Function: [int, T1, [T2, int]] -> T1.
        // Params: [int, [int, char], [float, int]]
        Function func({Node("int"), Node("T1"),
                Node({Node("T2"), Node("int")})}, Node("T1"));
        std::vector<Node> params = {Node("int"), Node({Node("int"), Node("char")}),
                Node({Node("float"), Node("int")})};

        Node* result = inferReturnType(func, params);
        if (result != nullptr) {
            std::cout << result->toString() << std::endl; // Expected: "[int,char]"
            delete result;
        } else {
            std::cout << "null" << std::endl;
        }
    }

    static void test3() {
        std::cout << "\n===== Test 3 =====" << std::endl;
        // Function: [T1, T2, int, T1] -> [T1, T2].
        // Params: [int, int, int, char]
        Function func({Node("T1"), Node("T2"), Node("int"), Node("T1")},
                Node({Node("T1"), Node("T2")}));
        std::vector<Node> params = {Node("int"), Node("int"), Node("int"), Node("char")};
        Node* result = inferReturnType(func, params);
        if (result != nullptr) {
            std::cout << result->toString() << std::endl;
            delete result;
        } else {
            std::cout << "null" << std::endl; // Expected: null
        }
    }

    static void test4() {
        std::cout << "\n===== Test 4 =====" << std::endl;
        // Function: [[T1, T2], [T2, T3], T3] -> [T1, [T2, T3]].
        // Params: [[int, char], [char, [float, int]], [float, int]]
        Function func(
                {Node({Node("T1"), Node("T2")}),
                        Node({Node("T2"), Node("T3")}), Node("T3")},
                Node({Node("T1"), Node({Node("T2"), Node("T3")})}));

        std::vector<Node> params = {Node({Node("int"), Node("char")}),
                Node({Node("char"), Node({Node("float"), Node("int")})}),
                Node({Node("float"), Node("int")})};

        Node* result = inferReturnType(func, params);
        if (result != nullptr) {
            std::cout << result->toString() << std::endl; // Expected: "[int,[char,[float,int]]]"
            delete result;
        } else {
            std::cout << "null" << std::endl;
        }
    }

    static void test5() {
        std::cout << "\n===== Test 5 =====" << std::endl;
        // Function: [int, float] -> char.
        // Params: [int, char]
        Function func1({Node("int"), Node("float")}, Node("char"));
        std::vector<Node> params1 = {Node("int"), Node("char")};
        Node* result1 = inferReturnType(func1, params1);
        if (result1 != nullptr) {
            std::cout << result1->toString() << std::endl;
            delete result1;
        } else {
            std::cout << "null" << std::endl; // Expected: null
        }
    }

    static void test6() {
        std::cout << "\n===== Test 6 =====" << std::endl;
        // Function: [int] -> int.
        // Params: []
        Function func2({Node("int")}, Node("int"));
        std::vector<Node> params2;
        Node* result2 = inferReturnType(func2, params2);
        if (result2 != nullptr) {
            std::cout << result2->toString() << std::endl;
            delete result2;
        } else {
            std::cout << "null" << std::endl; // Expected: null
        }
        std::cout << std::endl;
    }
};

int main() {
    Solution::test1();
    Solution::test2();
    Solution::test3();
    Solution::test4();
    Solution::test5();
    Solution::test6();
    return 0;
}
