#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

#define VO_CUNG 1e9
#define SO_NUT_TOI_DA 30

struct Canh {
    int ma_lang_gieng;
    int trong_so;
};

struct CanhKruskal {
    int u, v, w;
    bool operator<(const CanhKruskal& khac) const { return w < khac.w; }
};

class QuanLyGiaoThong {
private:
    string ten_tinh[SO_NUT_TOI_DA];
    vector<Canh> ke[SO_NUT_TOI_DA];
    int so_nut = 0;

    int lay_hoac_them_nut(const string& ten) {
        for (int i = 0; i < so_nut; i++) {
            if (ten_tinh[i] == ten) return i;
        }
        ten_tinh[so_nut] = ten;
        so_nut++;
        return so_nut - 1;
    }

    int tim_goc(int i, int cha[]) {
        if (cha[i] == -1) return i;
        return cha[i] = tim_goc(cha[i], cha);
    }

    void gop_nhom(int x, int y, int cha[]) {
        int goc_x = tim_goc(x, cha);
        int goc_y = tim_goc(y, cha);
        if (goc_x != goc_y) cha[goc_x] = goc_y;
    }

    void in_ma_tran(const int mt[SO_NUT_TOI_DA][SO_NUT_TOI_DA]) {
        cout << "\n" << setw(12) << " ";
        for (int i = 0; i < so_nut; i++) cout << setw(12) << ten_tinh[i];
        cout << "\n";
        for (int i = 0; i < so_nut; i++) {
            cout << setw(12) << ten_tinh[i];
            for (int j = 0; j < so_nut; j++) {
                if (mt[i][j] == VO_CUNG) cout << setw(12) << "-";
                else cout << setw(12) << mt[i][j];
            }
            cout << "\n";
        }
    }

public:
    void them_duong_di(const string& u, const string& v, int w) {
        int g = lay_hoac_them_nut(u);
        int n = lay_hoac_them_nut(v);
        ke[g].push_back({n, w});
        ke[n].push_back({g, w});
    }

    void prim(const string& ten_bat_dau) {
        int s = -1;
        for (int i = 0; i < so_nut; i++) if (ten_tinh[i] == ten_bat_dau) s = i;
        if (s == -1) return;

        int gia_tri[SO_NUT_TOI_DA], cha[SO_NUT_TOI_DA], mt[SO_NUT_TOI_DA][SO_NUT_TOI_DA];
        bool da_xet[SO_NUT_TOI_DA] = {false};
        for (int i = 0; i < so_nut; i++) {
            gia_tri[i] = VO_CUNG; cha[i] = -1;
            for (int j = 0; j < so_nut; j++) mt[i][j] = VO_CUNG;
        }
        gia_tri[s] = 0;
        int tong = 0;

        for (int dem = 0; dem < so_nut; dem++) {
            int min_k = VO_CUNG, u = -1;
            for (int v = 0; v < so_nut; v++) {
                if (!da_xet[v] && gia_tri[v] < min_k) { min_k = gia_tri[v]; u = v; }
            }
            if (u == -1) break;
            da_xet[u] = true;
            tong += gia_tri[u];
            if (cha[u] != -1) { mt[u][cha[u]] = gia_tri[u]; mt[cha[u]][u] = gia_tri[u]; }

            for (auto& c : ke[u]) {
                if (!da_xet[c.ma_lang_gieng] && c.trong_so < gia_tri[c.ma_lang_gieng]) {
                    cha[c.ma_lang_gieng] = u;
                    gia_tri[c.ma_lang_gieng] = c.trong_so;
                }
            }
        }
        cout << "\n" << tong;
        in_ma_tran(mt);
    }

    void kruskal() {
        vector<CanhKruskal> ds_canh;
        for (int u = 0; u < so_nut; u++) {
            for (auto& c : ke[u]) {
                if (u < c.ma_lang_gieng) ds_canh.push_back({u, c.ma_lang_gieng, c.trong_so});
            }
        }
        sort(ds_canh.begin(), ds_canh.end());
        int cha[SO_NUT_TOI_DA], mt[SO_NUT_TOI_DA][SO_NUT_TOI_DA];
        for (int i = 0; i < so_nut; i++) {
            cha[i] = -1;
            for (int j = 0; j < so_nut; j++) mt[i][j] = VO_CUNG;
        }
        int tong = 0, dem = 0;
        for (auto& e : ds_canh) {
            if (dem == so_nut - 1) break;
            int g_u = tim_goc(e.u, cha), g_v = tim_goc(e.v, cha);
            if (g_u != g_v) {
                mt[e.u][e.v] = e.w; mt[e.v][e.u] = e.w;
                tong += e.w; dem++;
                gop_nhom(g_u, g_v, cha);
            }
        }
        cout << "\n" << tong;
        in_ma_tran(mt);
    }
};

int main() {
    system("chcp 65001 > nul");
    QuanLyGiaoThong ql;
    ql.them_duong_di("Hà nội", "Hải dương", 55);
    ql.them_duong_di("Hải dương", "Hải phòng", 45);
    ql.them_duong_di("Hà nội", "Phủ lý", 60);
    ql.them_duong_di("Hà nội", "Hoà Bình", 75);
    ql.them_duong_di("Hoà Bình", "Phủ lý", 65);

    ql.prim("Hoà Bình");
    ql.kruskal();
    return 0;
}