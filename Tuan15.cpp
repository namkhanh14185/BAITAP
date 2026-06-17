#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

const int N = 11;
const string city[N] = {
    "Ha Noi", "Son Tay", "Hoa Binh", "Phu Ly", "Hung Yen",
    "Hai Duong", "Hai Phong", "Uong Bi", "Bac Giang", "Bac Ninh", "Thai Nguyen"
};

// Sử dụng danh sách kề thay cho ma trận kề
void them_Canh(vector<int> adj[], int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
}

void BFS(const vector<int> adj[], int start) {
    vector<bool> visited(N, false);
    queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        cout << city[u] << "\n";

        // Chỉ duyệt qua các đỉnh thực sự kề với u
        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
}

int main() {
    vector<int> adj[N]; // Mảng các vector

    for (int v : {1, 2, 3, 5, 9, 10}) them_Canh(adj, 0, v);
    them_Canh(adj, 3, 4); them_Canh(adj, 4, 5); them_Canh(adj, 5, 6);
    them_Canh(adj, 6, 7); them_Canh(adj, 7, 8); them_Canh(adj, 8, 9); them_Canh(adj, 9, 7);

    cout << "Duyet BFS (Danh sach ke) tu Ha Noi:\n";
    BFS(adj, 0);
    return 0;
}