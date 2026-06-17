#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int N = 11;
const string city[N] = {
    "Ha Noi", "Son Tay", "Hoa Binh", "Phu Ly", "Hung Yen",
    "Hai Duong", "Hai Phong", "Uong Bi", "Bac Giang", "Bac Ninh", "Thai Nguyen"
};

void them_Canh(vector<int> adj[], int u, int v) {
    adj[u].push_back(v); adj[v].push_back(u);
}

void BFS_TimDuong(const vector<int> adj[], int start, vector<int>& parent) {
    vector<bool> visited(N, false);
    queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                parent[v] = u;
                q.push(v);
            }
        }
    }
}

void in_DuongDi(int start, int dest, const vector<int>& parent) {
    if (parent[dest] == -1 && start != dest) {
        cout << "Khong co duong di tu " << city[start] << " den " << city[dest] << "\n";
        return;
    }
    vector<int> path;
    for (int v = dest; v != -1; v = parent[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());

    cout << "Duong di ngan nhat: ";
    for (size_t i = 0; i < path.size(); i++) {
        cout << city[path[i]] << (i == path.size() - 1 ? "" : " -> ");
    }
    cout << "\n";
}

int main() {
    vector<int> adj[N];
    for (int v : {1, 2, 3, 5, 9, 10}) them_Canh(adj, 0, v);
    them_Canh(adj, 3, 4); them_Canh(adj, 4, 5); them_Canh(adj, 5, 6);
    them_Canh(adj, 6, 7); them_Canh(adj, 7, 8); them_Canh(adj, 8, 9); them_Canh(adj, 9, 7);

    vector<int> parent(N, -1);
    BFS_TimDuong(adj, 0, parent);
    in_DuongDi(0, 7, parent); 
    return 0;
}