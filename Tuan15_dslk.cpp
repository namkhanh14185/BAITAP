#include <iostream>
#include <string>
using namespace std;
const int N = 11;
const int INF = 1e9; 

const string city[N] = {
    "Ha Noi", "Son Tay", "Hoa Binh", "Phu Ly", "Hung Yen",
    "Hai Duong", "Hai Phong", "Uong Bi", "Bac Giang", "Bac Ninh", "Thai Nguyen"
};

struct Node {
    int vertex;
    int weight; 
    Node* next;
};

Node* head[N] = {nullptr};

void them_Canh(int u, int v, int w) {
    Node* p = new Node{v, w, head[u]};
    head[u] = p;

    p = new Node{u, w, head[v]};
    head[v] = p;
}
void Dijkstra(int start, int dest) {
    int dist[N];
    bool optimized[N] = {false}; 

    for (int i = 0; i < N; i++) dist[i] = INF;
    dist[start] = 0;

    for (int step = 0; step < N; step++) {
        int u = -1, min_d = INF;
        for (int i = 0; i < N; i++) {
            if (!optimized[i] && dist[i] < min_d) {
                min_d = dist[i];
                u = i;
            }
        }

        if (u == -1 || u == dest) break;
        optimized[u] = true;
        Node* temp = head[u];
        while (temp != nullptr) {
            int v = temp->vertex;
            int w = temp->weight;
            if (!optimized[v] && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
            temp = temp->next;
        }
    }

    cout << "Ket qua tim duong di\n";
    if (dist[dest] == INF) {
        cout << "Khong co duong di tu " << city[start] << " den " << city[dest] << "\n";
    } else {
        cout << "Quang duong ngan nhat tu [" << city[start] << "] den [" << city[dest] << "] la: " << dist[dest] << " km\n";
    }
}

void giai_phong() {
    for (int i = 0; i < N; i++) 
    {
        Node* temp = head[i];
        while (temp != nullptr) {
            Node* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
        head[i] = nullptr;
    }
}

int main() {
    them_Canh(0, 1, 42); them_Canh(0, 2, 76); them_Canh(0, 3, 60); 
    them_Canh(0, 5, 58); them_Canh(0, 9, 30); them_Canh(0, 10, 75); 
    them_Canh(3, 4, 35); them_Canh(4, 5, 25); them_Canh(5, 6, 45); 
    them_Canh(6, 7, 40); them_Canh(7, 8, 50); them_Canh(8, 9, 25); 
    them_Canh(9, 7, 85);
    Dijkstra(0, 7);

    giai_phong();
    return 0;
}