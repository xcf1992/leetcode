/*
Load Balancer for Notebook Platform
Problem Description
You are implementing a load balancer for a notebook platform that runs multiple Jupyter servers. The goal is to decide
which server (called a "target") should handle each incoming WebSocket connection request, balancing load and applying
various constraints. Function Signature route_requests(numTargets, maxConnectionsPerTarget, requests) -> list of strings
Parameters

numTargets (integer): The number of servers (targets), indexed 1 to numTargets.
maxConnectionsPerTarget (integer): The maximum number of active connections allowed per target at any time.
requests (list of strings): A series of requests, each in one of the following formats:

CONNECT,connectionId,userId,objectId — Open a new WebSocket connection.
DISCONNECT,connectionId,userId,objectId — Close a previously established connection.
SHUTDOWN,targetIndex — Temporarily shut down a server, evict all its connections, and reroute them.



Output
Return a list of strings, each representing a successful CONNECT in the format:
connectionId,userId,targetIndex
where targetIndex is 1-based. Rejected connections (due to capacity) do not appear in the output.

Rules (Applied Incrementally)
Part 1: Basic Load Balancing
Assign each new connection to the target with the fewest active connections. If there is a tie, choose the smaller
index. Example: With 2 targets and two CONNECT requests, conn1 goes to target 1, conn2 goes to target 2. Part 2:
Disconnections When a DISCONNECT request is received, remove that connection from its target, freeing the slot. Future
connections will see the updated counts. Example: Connect conn1 to target 1, disconnect it, then connect conn2 — both
are logged on target 1. Part 3: Object Pinning If an objectId already has an active connection on a target, all future
connections for that same objectId must go to the same target. Once the last connection for that object is disconnected,
the pin is removed. Example: Two connects with the same objectId both go to the same target regardless of load. Part 4:
Capacity Limits Each target cannot exceed maxConnectionsPerTarget active connections. If all eligible targets
(considering object pinning) are full, the connection is rejected and not logged. Example: With maxConnectionsPerTarget
= 1, conn1 and conn2 connect to different servers, but conn3 is rejected. Part 5: Target Shutdown A SHUTDOWN,targetIndex
request:

Evicts all active connections on that target.
Reroutes them in ascending connectionId order, following the same rules (least connections, tie-break by smaller index,
object pinning, capacity limits). During rerouting, the shutdown target is not considered as a destination. After
rerouting completes, the target is immediately available again for future requests.

Example: Shutting down target 1 causes its connections to be rerouted to target 2, then new requests can again be
assigned to target 1.

Constraints

Connection IDs are unique strings.
All request formats are well-formed.
The system processes requests sequentially in the order given.
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
#include <map>
using namespace std;

vector<string> route_requests(int numTargets, int maxConnectionsPerTarget, vector<string>& requests) {
    vector<string> output;

    // Active connections per target (1-indexed, so size numTargets+1)
    vector<int> activeCount(numTargets + 1, 0);

    // Connection info: connectionId -> {userId, objectId, targetIndex}
    struct ConnInfo {
        string userId;
        string objectId;
        int targetIndex;
    };
    map<string, ConnInfo> connections;  // connectionId -> ConnInfo

    // Object pinning: objectId -> targetIndex (only while object has active connections)
    map<string, int> objectPin;
    // Count of active connections per objectId
    map<string, int> objectConnCount;

    // Track which connections are on each target (for shutdown)
    vector<set<string>> targetConnections(numTargets + 1);

    // Whether a target is shut down (temporarily, during rerouting)
    vector<bool> isShutdown(numTargets + 1, false);

    auto findBestTarget = [&](const string& objectId) -> int {
        // If object is pinned, must use that target (if it's not shut down and has capacity)
        if (objectPin.count(objectId)) {
            int pinned = objectPin[objectId];
            if (!isShutdown[pinned] && activeCount[pinned] < maxConnectionsPerTarget) {
                return pinned;
            }
            // If pinned target is shut down or full, we need to find a new target
            // But during shutdown rerouting, the pinned target IS the shutdown one
            // so we pick a new one. If full, reject.
            if (isShutdown[pinned]) {
                // Pick new target ignoring the shutdown one, but still apply least-connections
                int best = -1;
                for (int t = 1; t <= numTargets; t++) {
                    if (isShutdown[t])
                        continue;
                    if (activeCount[t] >= maxConnectionsPerTarget)
                        continue;
                    if (best == -1 || activeCount[t] < activeCount[best]) {
                        best = t;
                    }
                }
                return best;  // -1 if all full
            }
            // Pinned but full -> reject
            if (activeCount[pinned] >= maxConnectionsPerTarget) {
                return -1;
            }
            return pinned;
        }

        // No pin: find target with fewest active connections, tie-break by smaller index
        int best = -1;
        for (int t = 1; t <= numTargets; t++) {
            if (isShutdown[t])
                continue;
            if (activeCount[t] >= maxConnectionsPerTarget)
                continue;
            if (best == -1 || activeCount[t] < activeCount[best]) {
                best = t;
            }
        }
        return best;  // -1 if all full
    };

    auto doConnect = [&](const string& connectionId, const string& userId, const string& objectId) -> int {
        int target = findBestTarget(objectId);
        if (target == -1)
            return -1;  // rejected

        connections[connectionId] = {userId, objectId, target};
        activeCount[target]++;
        targetConnections[target].insert(connectionId);

        // Update object pin
        objectPin[objectId] = target;
        objectConnCount[objectId]++;

        return target;
    };

    auto doDisconnect = [&](const string& connectionId) {
        if (connections.find(connectionId) == connections.end())
            return;
        auto& info = connections[connectionId];
        int target = info.targetIndex;
        string objectId = info.objectId;

        activeCount[target]--;
        targetConnections[target].erase(connectionId);

        objectConnCount[objectId]--;
        if (objectConnCount[objectId] == 0) {
            objectPin.erase(objectId);
            objectConnCount.erase(objectId);
        }

        connections.erase(connectionId);
    };

    for (auto& req : requests) {
        // Parse request
        stringstream ss(req);
        string action;
        getline(ss, action, ',');

        if (action == "CONNECT") {
            string connectionId, userId, objectId;
            getline(ss, connectionId, ',');
            getline(ss, userId, ',');
            getline(ss, objectId, ',');

            int target = doConnect(connectionId, userId, objectId);
            if (target != -1) {
                output.push_back(connectionId + "," + userId + "," + to_string(target));
            }
        } else if (action == "DISCONNECT") {
            string connectionId, userId, objectId;
            getline(ss, connectionId, ',');
            getline(ss, userId, ',');
            getline(ss, objectId, ',');

            doDisconnect(connectionId);
        } else if (action == "SHUTDOWN") {
            string targetStr;
            getline(ss, targetStr, ',');
            int targetIdx = stoi(targetStr);

            // Collect all connections on this target, sorted by connectionId ascending
            vector<string> evicted(targetConnections[targetIdx].begin(), targetConnections[targetIdx].end());
            sort(evicted.begin(), evicted.end());

            // Save their info before evicting
            vector<ConnInfo> evictedInfo;
            for (auto& cid : evicted) {
                evictedInfo.push_back(connections[cid]);
            }

            // Evict all connections (this also removes object pins if needed)
            for (auto& cid : evicted) {
                doDisconnect(cid);
            }

            // Mark target as shut down during rerouting
            isShutdown[targetIdx] = true;

            // Reroute in ascending connectionId order
            for (int i = 0; i < (int)evicted.size(); i++) {
                string& cid = evicted[i];
                string& userId = evictedInfo[i].userId;
                string& objectId = evictedInfo[i].objectId;

                int target = doConnect(cid, userId, objectId);
                if (target != -1) {
                    output.push_back(cid + "," + userId + "," + to_string(target));
                }
            }

            // Target is back online
            isShutdown[targetIdx] = false;
        }
    }

    return output;
}

int main() {
    // Test Part 1: Basic load balancing
    {
        cout << "=== Test 1: Basic Load Balancing ===" << endl;
        vector<string> requests = {"CONNECT,conn1,userA,obj1", "CONNECT,conn2,userB,obj2"};
        auto result = route_requests(2, 10, requests);
        for (auto& s : result)
            cout << s << endl;
        // Expected: conn1,userA,1  conn2,userB,2
    }

    // Test Part 2: Disconnections
    {
        cout << "\n=== Test 2: Disconnections ===" << endl;
        vector<string> requests = {"CONNECT,conn1,userA,obj1", "DISCONNECT,conn1,userA,obj1",
                                   "CONNECT,conn2,userB,obj2"};
        auto result = route_requests(2, 10, requests);
        for (auto& s : result)
            cout << s << endl;
        // Expected: conn1,userA,1  conn2,userB,1
    }

    // Test Part 3: Object pinning
    {
        cout << "\n=== Test 3: Object Pinning ===" << endl;
        vector<string> requests = {
                "CONNECT,conn1,userA,obj1",
                "CONNECT,conn2,userB,obj1"  // same objectId -> pinned to target 1
        };
        auto result = route_requests(2, 10, requests);
        for (auto& s : result)
            cout << s << endl;
        // Expected: conn1,userA,1  conn2,userB,1
    }

    // Test Part 4: Capacity limits
    {
        cout << "\n=== Test 4: Capacity Limits ===" << endl;
        vector<string> requests = {
                "CONNECT,conn1,userA,obj1", "CONNECT,conn2,userB,obj2",
                "CONNECT,conn3,userC,obj3"  // should be rejected
        };
        auto result = route_requests(2, 1, requests);
        for (auto& s : result)
            cout << s << endl;
        // Expected: conn1,userA,1  conn2,userB,2  (conn3 rejected)
    }

    // Test Part 5: Shutdown
    {
        cout << "\n=== Test 5: Shutdown ===" << endl;
        vector<string> requests = {
                "CONNECT,conn1,userA,obj1", "CONNECT,conn2,userB,obj2",
                "SHUTDOWN,1",               // evict conn1 from target 1, reroute to target 2
                "CONNECT,conn3,userC,obj3"  // target 1 now available again
        };
        auto result = route_requests(2, 10, requests);
        for (auto& s : result)
            cout << s << endl;
        // Expected: conn1,userA,1  conn2,userB,2  conn1,userA,2  conn3,userC,1
    }

    return 0;
}