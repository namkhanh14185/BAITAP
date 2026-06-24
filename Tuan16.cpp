#include <iostream>
#include <string>
#include <vector>
#include <cctype>

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

string chuan_hoa(string ten) {
    string ket_qua = "";
    bool viet_hoa = true;
    for (size_t i = 0; i < ten.length(); i++) {
        if (isspace(ten[i])) {
            ket_qua += ten[i];
            viet_hoa = true;
        } else {
            if (viet_hoa) {
                ket_qua += toupper(ten[i]);
                viet_hoa = false;
            } else {
                ket_qua += tolower(ten[i]);
            }
        }
    }
    return ket_qua;
}

int lay_hoac_them_nut(DoThi& do_thi, const string& ten) {
    string ten_chuan = chuan_hoa(ten);
    for (int i = 0; i < do_thi.so_nut; i++) {
        if (do_thi.ten_tinh[i] == ten_chuan) {
            return i;
        }
    }
    do_thi.ten_tinh[do_thi.so_nut] = ten_chuan;
    do_thi.so_nut++;
    return do_thi.so_nut - 1;
}

void them_canh(DoThi& do_thi, const string& ten_goc, const string& ten_ngon, int trong_so) {
    int goc = lay_hoac_them_nut(do_thi, ten_goc);
    int ngon = lay_hoac_them_nut(do_thi, ten_ngon);

    do_thi.ke[goc].push_back({ngon, trong_so});
    do_thi.ke[ngon].push_back({goc, trong_so});
}

void dijkstra(DoThi& do_thi, const string& ten_bat_dau, const string& ten_ket_thuc) {
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

    string s_chuan = chuan_hoa(ten_bat_dau);
    string e_chuan = chuan_hoa(ten_ket_thuc);
    cout << "=== TÌM ĐƯỜNG ĐI NGẮN NHẤT TỪ " << s_chuan << " ĐẾN " << e_chuan << " ===\n";
    if (khoang_cach[ket_thuc] == INF) {
        cout << "❌ Không tìm thấy đường đi giữa hai tỉnh.\n";
        return;
    }

    int duong_di[MAX_NODES];
    int dem = 0;
    int nut_hien_tai = ket_thuc;

    while (nut_hien_tai != -1) {
        duong_di[dem++] = nut_hien_tai;
        nut_hien_tai = truy_vet[nut_hien_tai];
    }

    cout << "👉 Lộ trình tối ưu: ";
    for (int i = dem - 1; i >= 0; i--) {
        cout << do_thi.ten_tinh[duong_di[i]];
        if (i > 0) cout << " -> ";
    }
    cout << "\nTotal quãng đường: " << khoang_cach[ket_thuc] << " km\n";
}

int main() {
    DoThi do_thi;

    them_canh(do_thi, "hà nội", "HẢI DƯƠNG", 55);
    them_canh(do_thi, "Hải Dương", "hưng yên", 40);
    them_canh(do_thi, "Hưng Yên", "Phủ Lý", 30);
    them_canh(do_thi, "Hà Nội", "phủ lý", 60);

    dijkstra(do_thi, "HÀ NỘI", "phủ lý");

    return 0;
}