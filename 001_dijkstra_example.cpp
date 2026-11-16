// Source code credit:
// https://www.geeksforgeeks.org/cpp/c-program-for-dijkstras-shortest-path-algorithm-greedy-algo-7/

// Mengimpor semua pustaka standar C++
#include <bits/stdc++.h>
using namespace std;

// Fungsi Dijkstra: mencari jarak terpendek dari simpul sumber ke semua simpul lain
// adj: daftar ketetanggaan graf, src: simpul sumber
vector<int> dijkstra(vector<vector<vector<int>>> &adj, int src)
{
    int V = adj.size(); // Jumlah simpul dalam graf

    // Antrian prioritas minimum yang menyimpan pasangan {jarak, simpul}
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;

    // Inisialisasi semua jarak ke tak hingga (INT_MAX)
    vector<int> dist(V, INT_MAX);

    // Jarak dari sumber ke dirinya sendiri adalah 0
    dist[src] = 0;
    pq.push({0, src}); // Masukkan simpul sumber ke antrian

    while (!pq.empty())
    {
        int d = pq.top()[0]; // Jarak terkecil dari antrian
        int u = pq.top()[1]; // Simpul terkait
        pq.pop();

        // Lewati entri yang sudah usang (jarak tidak terbaru)
        if (d > dist[u])
            continue;

        // Telusuri semua simpul berseberangan dari u
        for (const auto &x : adj[u])
        {
            int v = x[0];      // Simpul tetangga
            int weight = x[1]; // Bobot edge u -> v

            // Perbarui jarak jika ditemukan jalur yang lebih pendek
            if (dist[v] > d + weight)
            {
                dist[v] = d + weight;
                pq.push({dist[v], v}); // Masukkan simpul tetangga ke antrian
            }
        }
    }

    return dist; // Kembalikan vektor jarak terpendek
}

int main()
{
    // Definisi daftar ketetanggaan graf (5 simpul)
    vector<vector<vector<int>>> adj = {{{1, 4}, {2, 8}},
                                       {{0, 4}, {4, 6}, {2, 3}},
                                       {{0, 8}, {3, 2}, {1, 3}},
                                       {{2, 2}, {4, 10}},
                                       {{1, 6}, {3, 10}}};

    int src = 0; // Simpul sumber

    vector<int> dist = dijkstra(adj, src); // Hitung jarak terpendek dari sumber

    // Cetak hasil vektor jarak
    cout << "[";
    for (int i = 0; i < dist.size(); i++)
    {
        cout << dist[i];
        if (i < dist.size() - 1)
            cout << ", ";
    }
    cout << "]" << endl;

    return 0;
}
