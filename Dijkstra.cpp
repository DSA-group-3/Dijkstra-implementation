#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <limits>
#include <algorithm>
using namespace std;

const int INF = numeric_limits<int>::max();

struct Edge {
    int to, weight;
};

class Graph {
private:
    vector<string> names;
    map<string, int> id;
    vector< vector<Edge> > adj;

    int getId(const string& name) {
        map<string, int>::iterator it = id.find(name);
        if (it != id.end()) return it->second;
        int v = names.size();
        id[name] = v;
        names.push_back(name);
        adj.push_back(vector<Edge>());
        return v;
    }

public:
    void addEdge(const string& a, const string& b, int w) {
        int u = getId(a);
        int v = getId(b);
        Edge e1 = {v, w};
        Edge e2 = {u, w};
        adj[u].push_back(e1);
        adj[v].push_back(e2);
    }

    void dijkstra(const string& source) {
        int src = id[source];
        int n = names.size();
        vector<int> dist(n, INF);
        vector<int> parent(n, -1);

        priority_queue< pair<int,int>, vector< pair<int,int> >, greater< pair<int,int> > > pq;

        dist[src] = 0;
        pq.push(make_pair(0, src));

        while (!pq.empty()) {
            pair<int,int> top = pq.top();
            pq.pop();
            int d = top.first;
            int u = top.second;

            if (d > dist[u]) continue;

            for (size_t k = 0; k < adj[u].size(); k++) {
                int v = adj[u][k].to;
                int w = adj[u][k].weight;
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }

        cout << "Shortest distances from " << source << ":\n";
        for (int i = 0; i < n; i++) {
            if (i == src) continue;

            cout << "\n" << names[i] << " : ";
            if (dist[i] == INF) {
                cout << "unreachable\n";
                continue;
            }
            cout << dist[i] << " km\n";

            // Rebuild the path from destination back to source
            vector<int> path;
            for (int v = i; v != -1; v = parent[v]) path.push_back(v);
            reverse(path.begin(), path.end());

            cout << "   Path: ";
            for (size_t k = 0; k < path.size(); k++) {
                cout << names[path[k]];
                if (k + 1 < path.size()) cout << " -> ";
            }
            cout << "\n";
        }
    }
};

int main() {
    Graph g;

    // Blantyre region
    g.addEdge("Nchalo", "Blantyre (Limbe)", 80);
    g.addEdge("Nchalo", "Blantyre (Ginnery Corner)", 65);
    g.addEdge("Blantyre (Limbe)", "Zomba", 60);
    g.addEdge("Mulanje", "Blantyre (Ginnery Corner)", 75);
    g.addEdge("Blantyre (Town)", "Blantyre (Ginnery Corner)", 3);
    g.addEdge("Blantyre (Chichiri)", "Blantyre (Ginnery Corner)", 1);
    g.addEdge("Blantyre (Ginnery Corner)", "Balaka", 125);
    g.addEdge("Balaka", "Zomba", 82);
    g.addEdge("Blantyre (Ginnery Corner)", "Zomba", 66);
    g.addEdge("Blantyre (Ginnery Corner)", "Liwonde", 95);
    g.addEdge("Zomba", "Liwonde", 50);
    g.addEdge("Blantyre (Ginnery Corner)", "Mangochi", 175);
    g.addEdge("Liwonde", "Mangochi", 75);

    // Link between the two regions
    g.addEdge("Blantyre (Town)", "Ntcheu", 135);
    g.addEdge("Ntcheu", "Dedza", 70);

    // Lilongwe region
    g.addEdge("Dedza", "Lilongwe (Main Branch)", 90);
    g.addEdge("Dedza", "Salima", 96);
    g.addEdge("Salima", "Lilongwe (Main Branch)", 115);
    g.addEdge("Mchinji", "Lilongwe (Main Branch)", 110);
    g.addEdge("Lilongwe (City Centre)", "Lilongwe (Main Branch)", 5);
    g.addEdge("Lilongwe (Main Branch)", "Kanengo", 15);
    g.addEdge("Lilongwe (Main Branch)", "Mzuzu", 355);
    g.addEdge("Lilongwe (Main Branch)", "Mponela", 70);
    g.addEdge("Lilongwe (Main Branch)", "Kasungu", 125);
    g.addEdge("Kasungu", "Mzuzu", 230);

    g.dijkstra("Blantyre (Ginnery Corner)");

    return 0;
}
