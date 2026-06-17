#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>

using namespace std;

map<string, vector<string>> adj; // Định nghĩa đồ thị bằng Tên -> Danh sách tên kề

void them_Canh(string u, string v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
}

void BFS_TheoTen(string start) {
    map<string, bool> visited;
    queue<string> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        string u = q.front();
        q.pop();

        cout << u << "\n";

        for (string v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
}

int main() {
    them_Canh("Ha Noi", "Son Tay");
    them_Canh("Ha Noi", "Hoa Binh");
    them_Canh("Ha Noi", "Hai Duong");
    them_Canh("Hai Duong", "Hai Phong");
    them_Canh("Hai Phong", "Uong Bi");

    cout << "Duyet BFS tim kiem theo ten tinh thanh:\n";
    BFS_TheoTen("Ha Noi");
    return 0;
}