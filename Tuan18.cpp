#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Canh { int u, v, w; };
string ten[30]; int sn = 0; vector<Canh> ds;

int id(string s) {
    for(int i=0; i<sn; i++) if(ten[i]==s) return i;
    ten[sn] = s; return sn++;
}
int tim(int i, int cha[]) { return cha[i] == -1 ? i : cha[i] = tim(cha[i], cha); }

int main() {
    system("chcp 65001 > nul");
    auto add = [](string u, string v, int w){ ds.push_back({id(u), id(v), w}); };
    add("Hà nội", "Hải dương", 55); add("Hải dương", "Hải phòng", 45);
    add("Hà nội", "Phủ lý", 60); add("Hà nội", "Hoà Bình", 75);

    sort(ds.begin(), ds.end(), [](Canh a, Canh b){ return a.w < b.w; });
    int cha[30], tong = 0; fill(cha, cha+sn, -1);

    for(auto& e : ds) {
        int g1 = tim(e.u, cha), g2 = tim(e.v, cha);
        if(g1 != g2) {
            cout << ten[e.u] << "-" << ten[e.v] << ":" << e.w << "\n";
            tong += e.w; cha[g1] = g2;
        }
    }
    cout << tong << "\n";
    return 0;
}