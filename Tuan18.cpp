#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

#define VO_CUNG 1e9
#define SO_NUT_TOI_DA 30

struct NutKe {
    int ma_so;
    int trong_so;
    NutKe* tiep_theo;
};

struct DoThiDong {
    string ten_tinh[SO_NUT_TOI_DA];
    NutKe* ke[SO_NUT_TOI_DA];
    int so_nut = 0;
};

struct CanhKruskal {
    int u, v, w;
    bool operator<(const CanhKruskal& khac) const { return w < khac.w; }
};

int lay_id(DoThiDong& dt, string ten) {
    for (int i = 0; i < dt.so_nut; i++) if (dt.ten_tinh[i] == ten) return i;
    dt.ke[dt.so_nut] = nullptr;
    dt.ten_tinh[dt.so_nut] = ten;
    return dt.so_nut++;
}

void them_canh_dong(DoThiDong& dt, string u, string v, int w) {
    int id_u = lay_id(dt, u), id_v = lay_id(dt, v);
    dt.ke[id_u] = new NutKe{id_v, w, dt.ke[id_u]};
    dt.ke[id_v] = new NutKe{id_u, w, dt.ke[id_v]};
}

int tim_goc(int i, int cha[]) { return cha[i] == -1 ? i : cha[i] = tim_goc(cha[i], cha); }

void kruskal_dong(DoThiDong& dt) {
    vector<CanhKruskal> ds;
    for (int i = 0; i < dt.so_nut; i++) {
        NutKe* t = dt.ke[i];
        while (t != nullptr) {
            if (i < t->ma_so) ds.push_back({i, t->ma_so, t->trong_so});
            t = t->tiep_theo;
        }
    }
    sort(ds.begin(), ds.end());
    int cha[SO_NUT_TOI_DA], mt[SO_NUT_TOI_DA][SO_NUT_TOI_DA];
    for (int i = 0; i < dt.so_nut; i++) {
        cha[i] = -1;
        for (int j = 0; j < dt.so_nut; j++) mt[i][j] = VO_CUNG;
    }
    int tong = 0, d = 0;
    for (auto& e : ds) {
        if (d == dt.so_nut - 1) break;
        int g1 = tim_goc(e.u, cha), g2 = tim_goc(e.v, cha);
        if (g1 != g2) {
            mt[e.u][e.v] = e.w; mt[e.v][e.u] = e.w;
            tong += e.w; d++; cha[g1] = g2;
        }
    }
    cout << "\n" << tong << "\n            ";
    for (int i = 0; i < dt.so_nut; i++) cout << setw(12) << dt.ten_tinh[i];
    cout << "\n";
    for (int i = 0; i < dt.so_nut; i++) {
        cout << setw(12) << dt.ten_tinh[i];
        for (int j = 0; j < dt.so_nut; j++) {
            if (mt[i][j] == VO_CUNG) cout << setw(12) << "-";
            else cout << setw(12) << mt[i][j];
        }
        cout << "\n";
    }
}

int main() {
    system("chcp 65001 > nul");
    DoThiDong dt;
    them_canh_dong(dt, "Hà nội", "Hải dương", 55);
    them_canh_dong(dt, "Hải dương", "Hải phòng", 45);
    them_canh_dong(dt, "Hà nội", "Phủ lý", 60);
    them_canh_dong(dt, "Hà nội", "Hoà Bình", 75);
    kruskal_dong(dt);
    return 0;
}