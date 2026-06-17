#include <iostream>
#include <string>

using namespace std;

const int N = 11;

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
bool visited[N] = {false}; 

void them_Canh(int u, int v, int w) {
    Node* p = new Node{v, w, head[u]};
    head[u] = p;

    p = new Node{u, w, head[v]};
    head[v] = p;
}
void DFS(int u) {
    cout << city[u] << " -> ";
    visited[u] = true;

    Node* temp = head[u];
    while (temp != nullptr) {
        int v = temp->vertex;
        if (!visited[v]) {
            DFS(v); 
        }
        temp = temp->next;
    }
}

void giai_phong() {
    for (int i = 0; i < N; i++) {
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

    cout << "Duyet BFS (Danh sach ke) tu Ha Noi:\n";
    DFS(0);
    cout << "END\n";

    giai_phong();
    return 0;
}