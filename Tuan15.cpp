#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>

using namespace std;

class Graph {
private:
    map<string, vector<string>> adjList;

public:
    void themTuyenDuong(const string& tinhA, const string& tinhB) {
        adjList[tinhA].push_back(tinhB);
        adjList[tinhB].push_back(tinhA);
    }
    void duyetBảnDo(const string& diemBatDau) {
        map<string, bool> visited;
        queue<string> q;

        visited[diemBatDau] = true;
        q.push(diemBatDau);

        cout << "Bat dau hanh trinh tu: " << diemBatDau << " ---\n";
        while (!q.empty()) {
            string u = q.front();
            q.pop();

            cout << " > Da ghe tham: " << u << "\n";

            for (const string& v : adjList[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
    }
};

int main() {
    Graph banDoMienBac;

    banDoMienBac.themTuyenDuong("Ha Noi", "Bac Ninh");
    banDoMienBac.themTuyenDuong("Ha Noi", "Thai Nguyen");
    banDoMienBac.themTuyenDuong("Bac Ninh", "Bac Giang");
    banDoMienBac.themTuyenDuong("Bac Giang", "Uong Bi");
    banDoMienBac.duyetBảnDo("Ha Noi");

    return 0;
}