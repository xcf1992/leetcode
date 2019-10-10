/*
1166. Design File System
https://leetcode.com/problems/design-file-system/

You are asked to design a file system which provides two functions:
create(path, value):
Creates a new path and associates a value to it if possible and returns True.
Returns False if the path already exists or its parent path doesn't exist.

get(path):
Returns the value associated with a path or returns -1 if the path doesn't exist.

The format of a path is one or more concatenated strings of the form:
/ followed by one or more lowercase English letters.

For example, /leetcode and /leetcode/problems are valid paths while an empty string and / are not.
Implement the two functions.
Please refer to the examples for clarifications.

Example 1:

Input:
["FileSystem","create","get"]
[[],["/a",1],["/a"]]
Output:
[null,true,1]
Explanation:
FileSystem fileSystem = new FileSystem();

fileSystem.create("/a", 1); // return true
fileSystem.get("/a"); // return 1
Example 2:

Input:
["FileSystem","create","create","get","create","get"]
[[],["/leet",1],["/leet/code",2],["/leet/code"],["/c/d",1],["/c"]]
Output:
[null,true,true,2,false,-1]
Explanation:
FileSystem fileSystem = new FileSystem();

fileSystem.create("/leet", 1); // return true
fileSystem.create("/leet/code", 2); // return true
fileSystem.get("/leet/code"); // return 2
fileSystem.create("/c/d", 1); // return false because the parent path "/c" doesn't exist.
fileSystem.get("/c"); // return -1 because this path doesn't exist.

Constraints:
The number of calls to the two functions is less than or equal to 10^4 in total.
2 <= path.length <= 100
1 <= value <= 10^9
*/
import java.util.HashMap;
import java.util.Map;

class FileSystem {
    private TrieNode root;

    public FileSystem() {
        this.root = new TrieNode(-1);
    }

    public boolean createPath(String path, int value) {
        String[] nodes = path.split("/");
        TrieNode cur = root;
        int len = nodes.length;
        for (int i = 1; i < len; ++i) {
            if (!cur.child.containsKey(nodes[i])) {
                if (i != len - 1) {
                    return false;
                }
                cur.child.put(nodes[i], new TrieNode(-1));
            }
            else {
                if (i == len - 1) {
                    return false;
                }
            }
            cur = cur.child.get(nodes[i]);
        }
        cur.isFile = true;
        cur.value = value;
        return true;
    }

    public int get(String path) {
        String[] nodes = path.split("/");
        TrieNode cur = root;
        int len = nodes.length;
        for (int i = 1; i < len; ++i) {
            if (!cur.child.containsKey(nodes[i])) {
                return -1;
            }
            cur = cur.child.get(nodes[i]);
        }

        if (!cur.isFile) {
            return -1;
        }
        return cur.value;
    }

    public class TrieNode {
        Map<String, TrieNode> child;
        boolean isFile;
        int value;

        TrieNode(int val) {
            this.child = new HashMap<>();
            this.isFile = false;
            this.value = val;
        }
    }
}
