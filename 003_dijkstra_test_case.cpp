#include <bits/stdc++.h>
using namespace std;

// Fungsi Dijkstra dengan validasi exception (TC-04 & TC-05)
vector<int> dijkstra(const vector<vector<vector<int>>> &adj, int src, vector<int> &parent) {
    int V = adj.size();

    // Validasi TC-04: Indeks kota awal di luar batas
    if (src < 0 || src >= V) {
        throw out_of_range("Indeks kota awal (" + to_string(src) + ") tidak valid!");
    }

    // Validasi TC-05: Bobot jarak negatif
    for (int u = 0; u < V; u++) {
        for (const auto &edge : adj[u]) {
            if (edge[1] < 0) {
                throw invalid_argument("Jarak antarkota tidak boleh bernilai negatif (" + to_string(edge[1]) + " km)!");
            }
        }
    }

    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
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

void showRoute(const vector<int> &parent, int destination, const string cities[]) {
    vector<int> path;
    for (int current = destination; current != -1; current = parent[current]) {
        path.push_back(current);
    }
    reverse(path.begin(), path.end());

    for (int i = 0; i < path.size(); i++) {
        cout << cities[path[i]];
        if (i < path.size() - 1)
            cout << " -> ";
    }
}

// Fungsi pembungkus untuk menjalankan setiap skenario Test Case
void runTestCase(string tcName, const vector<vector<vector<int>>> &adj, int src, const string cities[]) {
    cout << "\n========================================\n";
    cout << "PENGUJIAN: " << tcName << endl;
    cout << "========================================\n";

    try {
        vector<int> parent;
        vector<int> dist = dijkstra(adj, src, parent);

        int nearest = -1;
        cout << "Lokasi awal: " << cities[src] << "\n\nDaftar jarak destinasi Jawa Timur:\n";

        // Mengecek kota Jatim (indeks 2-7) dan mengecualikan kota asal (i != src) untuk TC-03
        for (int i = 2; i < 8; i++) {
            if (i == src) continue;

            if (dist[i] == INT_MAX) {
                cout << "- " << cities[i] << " : Tidak Terjangkau (Jalur Putus)\n";
            }
        }

        // Validasi TC-02: Jika seluruh kota tujuan terisolasi
        if (nearest == -1) {
            throw runtime_error("Semua destinasi di Jawa Timur tidak terjangkau dari lokasi awal!");
        }

        cout << "\n[HASIL] Destinasi terdekat : " << cities[nearest] << " (" << dist[nearest] << " km)\n";
        cout << "[RUTE]  Rute perjalanan    : ";
        showRoute(parent, nearest, cities);
        cout << endl;

    } catch (const exception &e) {
        cout << "[EXCEPTION TERTANGANI] " << e.what() << endl;
    }
}

int main() {
    string cities[] = {
        "Yogyakarta", "Solo", "Ngawi", "Madiun",
        "Kediri", "Malang", "Surabaya", "Banyuwangi"
    };

    vector<vector<vector<int>>> adjNormal = {
        {{1, 65}},                         // 0: Yogyakarta
        {{0, 65}, {2, 100}},               // 1: Solo
        {{1, 100}, {3, 32}},               // 2: Ngawi
        {{2, 32}, {4, 80}, {6, 160}},      // 3: Madiun
        {{3, 80}, {5, 105}},               // 4: Kediri
        {{4, 105}, {6, 90}},               // 5: Malang
        {{3, 160}, {5, 90}, {7, 290}},     // 6: Surabaya
        {{6, 290}}                         // 7: Banyuwangi
    };

    // TC-01: Perjalanan Normal dari Yogyakarta (src = 0)
    runTestCase("TC-01 (Normal - Berangkat dari Yogyakarta)", adjNormal, 0, cities);

    // TC-02: Jalur Solo-Ngawi terputus total (Akses ke Jatim terisolasi)
    vector<vector<vector<int>>> adjPutus = adjNormal;
    adjPutus[1] = {{0, 65}}; // Hapus koneksi Solo -> Ngawi
    adjPutus[2] = {{3, 32}}; // Hapus koneksi Ngawi -> Solo
    runTestCase("TC-02 (Jalur Utama Solo-Ngawi Terputus)", adjPutus, 0, cities);

    // TC-03: Perubahan titik awal berangkat dari Madiun (src = 3)
    runTestCase("TC-03 (Berangkat dari Madiun)", adjNormal, 3, cities);

    // TC-04: Input lokasi awal tidak valid (src = 10)
    runTestCase("TC-04 (Exception - Indeks Kota Awal Invalid)", adjNormal, 10, cities);

    // TC-05: Input bobot jarak negatif (-65 km)
    vector<vector<vector<int>>> adjNegatif = adjNormal;
    adjNegatif[0] = {{1, -65}};
    runTestCase("TC-05 (Exception - Bobot Jarak Negatif)", adjNegatif, 0, cities);

    return 0;
}