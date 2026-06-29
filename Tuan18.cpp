#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

#define VO_CUNG 1e9
#define SO_NUT_TOI_DA 30

struct DoThiTinh {
    string ten_tinh[SO_NUT_TOI_DA];
    int ma_tran_ke[SO_NUT_TOI_DA][SO_NUT_TOI_DA];
    int so_nut = 0;
};

int lay_ma_so(DoThiTinh& dt, const string& ten) {
    for (int i = 0; i < dt.so_nut; i++) if (dt.ten_tinh[i] == ten) return i;
    dt.ten_tinh[dt.so_nut] = ten;
    return dt.so_nut++;
}

void khoi_tao(DoThiTinh& dt) {
    for (int i = 0; i < SO_NUT_TOI_DA; i++)
        for (int j = 0; j < SO_NUT_TOI_DA; j++)
            dt.ma_tran_ke[i][j] = (i == j) ? 0 : VO_CUNG;
}

void them_canh(DoThiTinh& dt, const string& u, const string& v, int ts) {
    int id_u = lay_ma_so(dt, u);
    int id_v = lay_ma_so(dt, v);
    dt.ma_tran_ke[id_u][id_v] = ts;
    dt.ma_tran_ke[id_v][id_u] = ts;
}

void in_ma_tran(DoThiTinh& dt, int mt[SO_NUT_TOI_DA][SO_NUT_TOI_DA]) {
    cout << "\n" << setw(12) << " ";
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

void prim_tinh(DoThiTinh& dt, const string& start) {
    int s = -1;
    for (int i = 0; i < dt.so_nut; i++) if (dt.ten_tinh[i] == start) s = i;
    if (s == -1) return;

    int gia_tri[SO_NUT_TOI_DA], cha[SO_NUT_TOI_DA], kq[SO_NUT_TOI_DA][SO_NUT_TOI_DA];
    bool da_xet[SO_NUT_TOI_DA] = {false};
    for (int i = 0; i < dt.so_nut; i++) {
        gia_tri[i] = VO_CUNG; cha[i] = -1;
        for (int j = 0; j < dt.so_nut; j++) kq[i][j] = VO_CUNG;
    }
    gia_tri[s] = 0; int tong = 0;

    for (int c = 0; c < dt.so_nut; c++) {
        int min_v = VO_CUNG, u = -1;
        for (int i = 0; i < dt.so_nut; i++) if (!da_xet[i] && gia_tri[i] < min_v) { min_v = gia_tri[i]; u = i; }
        if (u == -1) break;
        da_xet[u] = true; tong += gia_tri[u];
        if (cha[u] != -1) { kq[u][cha[u]] = gia_tri[u]; kq[cha[u]][u] = gia_tri[u]; }

        for (int v = 0; v < dt.so_nut; v++) {
            if (dt.ma_tran_ke[u][v] != VO_CUNG && dt.ma_tran_ke[u][v] != 0 && !da_xet[v] && dt.ma_tran_ke[u][v] < gia_tri[v]) {
                cha[v] = u; gia_tri[v] = dt.ma_tran_ke[u][v];
            }
        }
    }
    cout << "\n" << tong; 
    in_ma_tran(dt, kq);
}

int main() {
    system("chcp 65001 > nul");
    DoThiTinh dt; khoi_tao(dt);
    them_canh(dt, "Hà nội", "Hải dương", 55);
    them_canh(dt, "Hải dương", "Hải phòng", 45);
    them_canh(dt, "Hà nội", "Phủ lý", 60);
    them_canh(dt, "Hà nội", "Hoà Bình", 75);
    them_canh(dt, "Hoà Bình", "Phủ lý", 65);

    prim_tinh(dt, "Hoà Bình");
    return 0;
}