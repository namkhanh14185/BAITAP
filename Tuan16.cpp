#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define INF 1e9
#define MAX_NODES 30

struct Canh {
    int id_lang_gieng;
    int trong_so;
};

struct DoThi {
    string ten_tinh[MAX_NODES];
    vector<Canh> ke[MAX_NODES];
    int so_nut = 0;
};

int lay_hoac_them_nut(DoThi& do_thi, const string& ten) {
    for (int i = 0; i < do_thi.so_nut; i++) {
        if (do_thi.ten_tinh[i] == ten) {
            return i;
        }
    }
    do_thi.ten_tinh[do_thi.so_nut] = ten;
    do_thi.so_nut++;
    return do_thi.so_nut - 1;
}

void them_canh(DoThi& do_thi, const string& ten_goc, const string& ten_ngon, int trong_so) {
    int goc = lay_hoac_them_nut(do_thi, ten_goc);
    int ngon = lay_hoac_them_nut(do_thi, ten_ngon);

    do_thi.ke[goc].push_back({ngon, trong_so});
    do_thi.ke[ngon].push_back({goc, trong_so});
}

int dijkstra_vong(DoThi& do_thi, const string& ten_bat_dau, const string& ten_ket_thuc, vector<int>& duong_di_phu) {
    int bat_dau = lay_hoac_them_nut(do_thi, ten_bat_dau);
    int ket_thuc = lay_hoac_them_nut(do_thi, ten_ket_thuc);
    int n = do_thi.so_nut;

    int khoang_cach[MAX_NODES];
    int truy_vet[MAX_NODES];
    bool da_duyet[MAX_NODES];

    for (int i = 0; i < n; i++) {
        khoang_cach[i] = INF;
        truy_vet[i] = -1;
        da_duyet[i] = false;
    }
    khoang_cach[bat_dau] = 0;

    for (int i = 0; i < n - 1; i++) {
        int kc_nho_nhat = INF;
        int u = -1;

        for (int j = 0; j < n; j++) {
            if (!da_duyet[j] && khoang_cach[j] < kc_nho_nhat) {
                kc_nho_nhat = khoang_cach[j];
                u = j;
            }
        }

        if (u == -1 || u == ket_thuc) break;
        da_duyet[u] = true;

        for (const Canh& canh : do_thi.ke[u]) {
            int v = canh.id_lang_gieng;
            int trong_so = canh.trong_so;

            if (!da_duyet[v] && khoang_cach[u] + trong_so < khoang_cach[v]) {
                khoang_cach[v] = khoang_cach[u] + trong_so;
                truy_vet[v] = u;
            }
        }
    }

    if (khoang_cach[ket_thuc] == INF) return INF;

    vector<int> tam;
    int nut_hien_tai = ket_thuc;
    while (nut_hien_tai != -1) {
        tam.push_back(nut_hien_tai);
        nut_hien_tai = truy_vet[nut_hien_tai];
    }
    for (int i = tam.size() - 1; i >= 0; i--) {
        duong_di_phu.push_back(tam[i]);
    }

    return khoang_cach[ket_thuc];
}

void tim_duong_qua_diem_trung_gian(DoThi& do_thi, const string& tinh_A, const string& tinh_B, const string& tinh_C) {
    vector<int> chang_1, chang_2;
    int kc1 = dijkstra_vong(do_thi, tinh_A, tinh_B, chang_1);
    int kc2 = dijkstra_vong(do_thi, tinh_B, tinh_C, chang_2);

    cout << "HÀNH TRÌNH TỪ " << tinh_A << " QUA " << tinh_B << " ĐẾN " << tinh_C << "\n";
    if (kc1 == INF || kc2 == INF) {
        cout << "Không thể thiết lập lộ trình này.\n";
        return;
    }

    cout << "Lộ trình đi: ";
    for (size_t i = 0; i < chang_1.size(); i++) {
        cout << do_thi.ten_tinh[chang_1[i]] << " -> ";
    }
    for (size_t i = 1; i < chang_2.size(); i++) {
        cout << do_thi.ten_tinh[chang_2[i]];
        if (i < chang_2.size() - 1) cout << " -> ";
    }
    cout << "\nTotal quãng đường: " << kc1 + kc2 << " km\n";
}

int main() {
    system("chcp 65001 > nul");

    DoThi do_thi;

    them_canh(do_thi, "Hà nội", "Hải dương", 55);
    them_canh(do_thi, "Hải dương", "Hải phòng", 45);
    them_canh(do_thi, "Hà nội", "Phủ lý", 60);

    tim_duong_qua_diem_trung_gian(do_thi, "Phủ lý", "Hà nội", "Hải phòng");

    return 0;
}