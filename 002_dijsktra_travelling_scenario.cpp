#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// Fungsi Dijkstra
vector<int> dijkstra(vector<vector<vector<int>>> &adj, int src, vector<int> &parent) {
    int V = adj.size();

    priority_queue<
        vector<int>,
        vector<vector<int>>,
        greater<vector<int>>
    > pq;

    vector<int> dist(V, INT_MAX);

    dist[src] = 0;
    pq.push({0, src});

    parent.assign(V, -1);

    while (!pq.empty()) {
        int d = pq.top()[0];
        int u = pq.top()[1];
        pq.pop();

        if (d > dist[u])
            continue;

        for (const auto &x : adj[u]) {
            int v = x[0];
            int weight = x[1];

            if (dist[v] > d + weight) {
                dist[v] = d + weight;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

void showRoute(vector<int> &parent, int destination, string cities[]) {
    vector<int> path;

    int current = destination;

    while (current != -1) {
        path.push_back(current);
        current = parent[current];
    }

    reverse(path.begin(), path.end());

    for (int i = 0; i < path.size(); i++) {
        cout << cities[path[i]];

        if (i < path.size() - 1)
            cout << " -> ";
    }
}

int main() {
    string cities[] = {
        "Yogyakarta", "Solo", "Ngawi", "Madiun",
        "Kediri", "Malang", "Surabaya", "Banyuwangi"
    };

    vector<vector<vector<int>>> adj = {
        {{1, 65}},                         // Yogyakarta
        {{0, 65}, {2, 100}},               // Solo
        {{1, 100}, {3, 32}},               // Ngawi
        {{2, 32}, {4, 80}, {6, 160}},      // Madiun
        {{3, 80}, {5, 105}},               // Kediri
        {{4, 105}, {6, 90}},               // Malang
        {{3, 160}, {5, 90}, {7, 290}},     // Surabaya
        {{6, 290}}                         // Banyuwangi
    };

    int src = 0;

    vector<int> parent;

    vector<int> dist = dijkstra(adj, src, parent);
    int nearest = -1;

    for (int i = 2; i < 8; i++) {
        if (nearest == -1 || dist[i] < dist[nearest]) {
            nearest = i;
        }
    }

    cout << "=== GPS DESTINATION FINDER ===\n";
    cout << "Lokasi awal: " << cities[src] << endl;

    cout << "\nDaftar jarak destinasi:\n";

    for (int i = 2; i < 8; i++) {
        cout << cities[i] << " : "
             << dist[i] << " km" << endl;
    }

    cout << "\n=== HASIL PENCARIAN ===\n";

    cout << "Destinasi terdekat: "
         << cities[nearest] << endl;

    cout << "Total jarak: "
         << dist[nearest] << " km" << endl;

    cout << "Rute perjalanan: ";
    showRoute(parent, nearest, cities);

    cout << endl;

    return 0;
}