#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>

using namespace std;
#define VO_CUNG 1e9

struct Canh { int u, v, w; bool operator<(const Canh& o) const { return w < o.w; } };

map<string, int> chuyen_ten;
map<int, string> chuyen_so;
int so_nut = 0;

int lay_id(string s) {
    if (chuyen_ten.find(s) == chuyen_ten.end()) {
        chuyen_ten[s] = so_nut; chuyen_so[so_nut] = s; so_nut++;
    }
    return chuyen_ten[s];
}

int tim_goc(int i, vector<int>& cha) { return cha[i] == -1 ? i : cha[i] = tim_goc(cha[i], cha); }

int main() {
    system("chcp 65001 > nul");
    vector<Canh> ds;
    auto them = [&](string u, string v, int w) { ds.push_back({lay_id(u), lay_id(v), w}); };
    them("Hà nội", "Hải dương", 55); them("Hải dương", "Hải phòng", 45);
    them("Hà nội", "Phủ lý", 60); them("Hà nội", "Hoà Bình", 75);

    sort(ds.begin(), ds.end());
    vector<int> cha(so_nut, -1);
    vector<vector<int>> mt(so_nut, vector<int>(so_nut, VO_CUNG));
    int tong = 0, dem = 0;

    for (auto& e : ds) {
        int g1 = tim_goc(e.u, cha), g2 = tim_goc(e.v, cha);
        if (g1 != g2) {
            mt[e.u][e.v] = e.w; mt[e.v][e.u] = e.w;
            tong += e.w; dem++; cha[g1] = g2;
        }
    }
    cout << "\n" << tong << "\n            ";
    for (int i = 0; i < so_nut; i++) cout << setw(12) << chuyen_so[i];
    cout << "\n";
    for (int i = 0; i < so_nut; i++) {
        cout << setw(12) << chuyen_so[i];
        for (int j = 0; j < so_nut; j++) {
            if (mt[i][j] == VO_CUNG) cout << setw(12) << "-";
            else cout << setw(12) << mt[i][j];
        }
        cout << "\n";
    }
    return 0;
}