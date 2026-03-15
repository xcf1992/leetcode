/*
https://www.hack2hire.com/companies/openai/coding-questions/6916140a3f8671d8f7a56641/practice?questionId=691614103f8671d8f7a56642
Design Cluster Message Aggregation

You are implementing a message-based protocol for a distributed system organized as a rooted n-ary tree. Each node in
this system represents a machine, identified by a unique string ID from 0 to n - 1. Each node also stores its parent's
ID (-1 for the root) and a list of its children's IDs.

Nodes communicate only with their immediate parent and children using a provided messaging API. Communication is
bi-directional. You need to support the following two operations, both triggered by an external client sending a message
to the root node:

Counting all nodes in the cluster: Triggered by sending a "count" message to the root node.
Reconstructing the cluster's topology as a string: Triggered by sending a "topology" message to the root node.
The node structure is defined as follows:

class Node {
    String nodeId;
    String parentId;
    List<String> children; // List of child node IDs

    **
     * This method is automatically invoked when a message is received by this node.
     * You need to implement this method.
     *
void receiveMessage(String fromId, String message);
}
You are also provided with the following asynchronous messaging API :

        class Cluster {
    **
     * Sends a message asynchronously to the target node.
     * This API is already implemented for you.
     *
    void sendAsyncMessage(String targetId, String message, String fromId);
}
You need to extend the Node class as necessary and implement the receiveMessage method:

void receiveMessage(int fromId, String message)

Invoked automatically when a message arrives at this node from the node specified by fromId.

If the message is initiated by an external client (the initial command to the root), fromId will be -1.

This method must handle two types of operations, both initiated at the root:

"count" operation
When the root receives the message "count", it should initiate a distributed counting process. When the process
finishes, only the root node should print the final total node count.

"topology" operation
When the root receives the message "topology", it should initiate a process to reconstruct the tree's topology as a
string. When the process finishes, only the root node should print the final reconstructed string. The required string
format is:

For a leaf node: its own ID (e.g., "4").
For an internal node: "ID(<child1_topology>,<child2_topology>,...)".
Children must be listed in the order provided in the children list.
Note: All inter-node communication must be done via sendAsyncMessage and receiveMessage. Your solution should ensure
that message passing, aggregation, and coordination are correctly managed for both operations.

Constraints:

1 ≤ n ≤
10
4
10
4

Each nodeId is a unique string.
The initial "count" or "topology" message is only sent to the root and has fromId as -1.
Example:

Input:

["sendAsyncMessage", "sendAsyncMessage"]
[[1, "count", -1], [1, "topology", -1]]

Output:
[null, null]

Explanation:

sendAsyncMessage(1, "count", -1); // This action is expected to cause the root node (1) to print the total number of
nodes: "7". sendAsyncMessage( 1, "topology", -1);  // This action is expected to cause the root node (1) to print the
cluster topology: "1(2(4),3(5,6(7)))".
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <set>

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <stdexcept>
#include <sstream>
using namespace std;

class Cluster;  // Forward declaration

class Node {
private:
    const int id;
    const int parentId;
    const std::vector<int> childIds;
    Cluster* const cluster;

    // state for count
    int cnt_initiator = -1;
    int subtree_cnt;
    int child_cnt_received;

    // state for topology
    int topo_initiator = -1;
    unordered_map<int, string> child_topo;
    int child_topo_received;
public:
    Node(int id, int parentId, const std::vector<int>& childIds, Cluster* cluster)
            : id(id), parentId(parentId), childIds(childIds), cluster(cluster) {
    }

    // This method is automatically invoked when a message arrives.
    void receiveMessage(int fromId, const std::string& message) {
        if (message == "count") {
            // Handle "count" request from cluster
            handleCountRequest(fromId);
        } else if (message == "topology") {
            // Handle "topology" request from cluster
            handleTopologyRequest(fromId);
        } else {
            // Handle message from other nodes
            if (message.substr(0, 6) == "COUNT:") {
                int count = std::stoi(message.substr(6));
                handleCountResponse(count);
            } else if (message.substr(0, 9) == "TOPOLOGY:") {
                std::string topology = message.substr(9);
                handleTopologyResponse(fromId, topology);
            } else {
                throw std::invalid_argument("Unknown message format: " + message);
            }
        }
    }

private:
    void handleCountRequest(int fromId) {
        cnt_initiator = fromId;
        subtree_cnt = 0;
        child_cnt_received = 0;
        if (childIds.empty()) {
            if (parentId == -1) {
                std::cout << "Total nodes: 1" << std::endl;
            } else {
                sendAsyncMessage(parentId, "COUNT:1", id);
            }
        } else {
            for (int child : childIds) {
                sendAsyncMessage(child, "count", id);
            }
        }
    }

    void handleTopologyRequest(int fromId) {
        topo_initiator = fromId;
        child_topo_received = 0;
        child_topo.clear();

        if (childIds.empty()) {
            if (parentId == -1) {
                std::cout << "Cluster topology: " << id << std::endl;
            } else {
                sendAsyncMessage(parentId, "TOPOLOGY:" + std::to_string(id), id);
            }
        } else {
            for (int child : childIds) {
                sendAsyncMessage(child, "topology", id);
            }
        }
    }

    void handleCountResponse(int count) {
        subtree_cnt += count;
        child_cnt_received += 1;
        if (child_cnt_received == childIds.size()) {
            subtree_cnt += 1;
            if (cnt_initiator == -1) {
                std::cout << "Total nodes: " << subtree_cnt << std::endl;
            } else {
                sendAsyncMessage(cnt_initiator, "COUNT:" + std::to_string(subtree_cnt), id);
            }

            cnt_initiator = -1; // reset
        }
    }

    void handleTopologyResponse(int fromId, const std::string& topology) {
        child_topo[fromId] = topology;
        child_topo_received++;

        if (child_topo_received == childIds.size()) {
            std::string cur_topo = buildTopologyString();
            if (topo_initiator == -1) { // This is the root
                std::cout << "Cluster topology: " << cur_topo << std::endl;
            } else {
                sendAsyncMessage(topo_initiator, "TOPOLOGY:" + cur_topo, id);
            }
            // Reset state
            topo_initiator = -1;
        }
    }

    std::string buildTopologyString() {
        if (childIds.empty()) {
            return to_string(id);
        }

        std::ostringstream sb;
        for (int i = 0; i < childIds.size(); i++) {
            if (i > 0) {
                sb << ",";
            }
            sb << child_topo[childIds[i]];
        }
        return std::to_string(id) + "(" + sb.str() + ")";
    }
protected:
    void sendAsyncMessage(int targetId, const std::string& message, int fromId);
};

class Cluster {
private:
    std::unordered_map<int, Node*> nodes;
    const int rootId;

public:
    Cluster(int rootId) : rootId(rootId) {
    }

    void addNode(int id, int parentId, const std::vector<int>& childIds) {
        nodes[id] = new Node(id, parentId, childIds, this);
    }

    /**
     * Provided API to simulate the process of sending a message to a target node
     * asynchronously.
     */
    void sendAsyncMessage(int targetId, const std::string& message, int fromId) {
        auto it = nodes.find(targetId);
        if (it != nodes.end()) {
            it->second->receiveMessage(fromId, message);
        }
    }

    static void main() {
        test1();
        test2();
        test3();
        test4();
    }

private:
    static void test1() {
        std::cout << "================= Test 1 ===================" << std::endl;
        // Cluster topology:
        //
        //        1
        //      /   \
        //     2     3
        //    /     / \
        //   4     5   6
        //               \
        //                7
        Cluster cluster(1);
        cluster.addNode(1, -1, {2, 3});
        cluster.addNode(2, 1, {4});
        cluster.addNode(3, 1, {5, 6});
        cluster.addNode(4, 2, {});
        cluster.addNode(5, 3, {});
        cluster.addNode(6, 3, {7});
        cluster.addNode(7, 6, {});

        std::cout << "--- Triggering Node Count ---" << std::endl;
        cluster.sendAsyncMessage(cluster.rootId, "count", -1);
        // Expected: 8

        std::cout << "\n--- Triggering Topology Reconstruction ---" << std::endl;
        cluster.sendAsyncMessage(cluster.rootId, "topology", -1);
        // Expected: "1(2(4),3(5,6(7)))"
    }

    static void test2() {
        std::cout << "\n================= Test 2 ===================" << std::endl;
        // Cluster topology:
        //               1
        //          /    |    \
        //        2      3      4
        //      /  \     |   /  |  \
        //     5    6    7  8   9  10
        //    /          |      |
        //   11          12     13
        //                     /  \
        //                   14    15
        Cluster cluster(1);
        cluster.addNode(1, -1, {2, 3, 4});
        cluster.addNode(2, 1, {5, 6});
        cluster.addNode(3, 1, {7});
        cluster.addNode(4, 1, {8, 9, 10});
        cluster.addNode(5, 2, {11});
        cluster.addNode(6, 2, {});
        cluster.addNode(7, 3, {12});
        cluster.addNode(8, 4, {});
        cluster.addNode(9, 4, {13});
        cluster.addNode(10, 4, {});
        cluster.addNode(11, 5, {});
        cluster.addNode(12, 7, {});
        cluster.addNode(13, 9, {14, 15});
        cluster.addNode(14, 13, {});
        cluster.addNode(15, 13, {});

        std::cout << "--- Triggering Node Count ---" << std::endl;
        cluster.sendAsyncMessage(cluster.rootId, "count", -1);
        // Expected: 15

        std::cout << "\n--- Triggering Topology Reconstruction ---" << std::endl;
        cluster.sendAsyncMessage(cluster.rootId, "topology", -1);
        // Expected: "1(2(5(11),6),3(7(12)),4(8,9(13(14,15)),10))"
    }

    static void test3() {
        std::cout << "\n================= Test 3 ===================" << std::endl;
        // Cluster topology: Single node (100)
        Cluster cluster(100);
        cluster.addNode(100, -1, {});

        std::cout << "--- Triggering Node Count ---" << std::endl;
        cluster.sendAsyncMessage(cluster.rootId, "count", -1);
        // Expected: 1

        std::cout << "\n--- Triggering Topology Reconstruction ---" << std::endl;
        cluster.sendAsyncMessage(cluster.rootId, "topology", -1);
        // Expected: "100"
    }

    static void test4() {
        std::cout << "\n================= Test 4 ===================" << std::endl;
        // Cluster topology:
        // 10 -> 20 -> 30 -> 40 -> 50
        Cluster cluster(10);
        cluster.addNode(10, -1, {20});
        cluster.addNode(20, 10, {30});
        cluster.addNode(30, 20, {40});
        cluster.addNode(40, 30, {50});
        cluster.addNode(50, 40, {});

        std::cout << "--- Triggering Node Count ---" << std::endl;
        cluster.sendAsyncMessage(cluster.rootId, "count", -1);
        // Expected: 5

        std::cout << "\n--- Triggering Topology Reconstruction ---" << std::endl;
        cluster.sendAsyncMessage(cluster.rootId, "topology", -1);
        // Expected: "10(20(30(40(50))))"
    }
};

void Node::sendAsyncMessage(int targetId, const std::string& message, int fromId) {
    cluster->sendAsyncMessage(targetId, message, fromId);
}

int main() {
    Cluster::main();
    return 0;
}