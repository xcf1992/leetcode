/*
You are given a list of services and their dependencies.
Input:
service_list: A list of strings in the format
service_name=dependency1,dependency2,....

entrypoint: The name of the starting service.

Definition: The load factor of a
service is the total number of units of load it handles when the entry point receives 1 unit of load.

Propagation:
When a service receives $X$ units of load, it sends $X$ units to each of its immediate dependencies simultaneously.
If multiple paths lead to the same service, the loads from those paths are summed.

Constraints:
The graph is a DAG (no cycles).
If a dependency is listed but not defined in the service_list, ignore it.
A service might have no dependencies (e.g.,service=).

Output: A list of strings in the format service_name*load_factor, sorted alphabetically by service_name,
including only the services reachable from the entry point.

Solution Strategy: Topological Sort / DPSince this is a DAG,
we can solve this using a Topological Sort or Dynamic Programming (Memoization). Because we only care about services
reachable from a specific entrypoint, a recursive DFS with memoization is often the cleanest approach.Parse the input:
Store the graph in an adjacency list (e.g., unordered_map<string, vector<string>>).Initialize load: The entrypoint
starts with a load of 1.Traverse:For the current service, if it has a load of $L$, add $L$ to the load factor of each of
its children.Since a node can be reached via multiple paths, we need to ensure we process all "parents" before
"children" to get the final sum, or simply use memoization to count paths.Format Output: Sort the keys and join with the
calculated load factors.
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>
#include <set>
using namespace std;

class LoadBalancer {
    unordered_map<string, vector<string>> adj;
    unordered_map<string, int> load_factors;

public:
    void solve(vector<string>& service_list, string entrypoint) {
        // 1. Parse Input
        for (const string& s : service_list) {
            size_t eq_pos = s.find('=');
            string service = s.substr(0, eq_pos);
            string deps_str = s.substr(eq_pos + 1);

            stringstream ss(deps_str);
            string dep;
            while (getline(ss, dep, ',')) {
                if (!dep.empty()) {
                    adj[service].push_back(dep);
                }
            }
            // Ensure the service exists in the map even if it has no deps
            if (adj.find(service) == adj.end()) {
                adj[service] = {};
            }
        }

        // 2. Calculate Load Factors (DFS with summation)
        // Note: In a DAG, the load factor of a service is the number of
        // distinct paths from the entrypoint to that service.
        load_factors[entrypoint] = 1;

        // We use a topological-like approach or simple BFS/DFS
        // to propagate load because it's a DAG.
        vector<string> order = get_topo_order(entrypoint);

        for (const string& u : order) {
            int current_load = load_factors[u];
            if (adj.count(u)) {
                for (const string& v : adj[u]) {
                    // Ignore non-existent services as per instructions
                    if (adj.count(v)) {
                        load_factors[v] += current_load;
                    }
                }
            }
        }

        // 3. Prepare and Sort Output
        vector<string> results;
        for (auto const& [name, load] : load_factors) {
            results.push_back(name + "*" + to_string(load));
        }
        sort(results.begin(), results.end());

        for (const string& res : results) {
            cout << res << endl;
        }
    }

private:
    // Helper to get nodes in topological order starting from entrypoint
    vector<string> get_topo_order(string start) {
        // Only consider nodes reachable from entrypoint
        set<string> reachable;
        reachable.insert(start);
        vector<string> q = {start};
        int head = 0;
        while (head < q.size()) {
            string u = q[head++];
            for (const string& v : adj[u]) {
                if (adj.count(v) && reachable.find(v) == reachable.end()) {
                    reachable.insert(v);
                    q.push_back(v);
                }
            }
        }

        unordered_map<string, int> in_degree;
        for (const string& u : reachable) {
            for (const string& v : adj[u]) {
                if (reachable.count(v)) {
                    in_degree[v]++;
                }
            }
        }

        vector<string> topo_q;
        if (in_degree[start] == 0)
            topo_q.push_back(start);

        head = 0;
        vector<string> order;
        while (head < topo_q.size()) {
            string u = topo_q[head++];
            order.push_back(u);
            for (const string& v : adj[u]) {
                if (reachable.count(v)) {
                    in_degree[v]--;
                    if (in_degree[v] == 0)
                        topo_q.push_back(v);
                }
            }
        }
        return order;
    }
};

int main() {
    vector<string> services = {"A=B,C", "B=C,D", "C=D", "D="};
    string entry = "A";
    LoadBalancer lb;
    lb.solve(services, entry);
    return 0;
}