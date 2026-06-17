#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

const int N = 11;
const int INF = 1e9;
const string city[N] = {
    "Ha Noi", "Son Tay", "Hoa Binh", "Phu Ly", "Hung Yen",
    "Hai Duong", "Hai Phong", "Uong Bi", "Bac Giang", "Bac Ninh", "Thai Nguyen"
};

struct Canh {
    int v, weight;
};

void them_Canh(vector<Canh> adj[], int u, int v, int w) {
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
}

void Dijkstra(const vector<Canh> adj[], int start, int dest) {
    vector<int> dist(N, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;

        for (auto edge : adj[u]) {
            if (dist[u] + edge.weight < dist[edge.v]) {
                dist[edge.v] = dist[u] + edge.weight;
                pq.push({dist[edge.v], edge.v});
            }
        }
    }
    cout << "Khoang cach ngan nhat tu " << city[start] << " den " << city[dest] << " la: " << dist[dest] << " km\n";
}

int main() {
    vector<Canh> adj[N];
    them_Canh(adj, 0, 1, 42);  
    them_Canh(adj, 0, 5, 58);  
    them_Canh(adj, 5, 6, 45); 
    them_Canh(adj, 6, 7, 40); 

    Dijkstra(adj, 0, 7); 
    return 0;
}