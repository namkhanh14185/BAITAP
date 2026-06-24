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

void cap_nhat_canh(DoThi& do_thi, const string& ten_goc, const string& ten_ngon, int trong_so_moi) {
    int goc = -1, ngon = -1;
    for (int i = 0; i < do_thi.so_nut; i++) {
        if (do_thi.ten_tinh[i] == ten_goc) goc = i;
        if (do_thi.ten_tinh[i] == ten_ngon) ngon = i;
    }
    if (goc == -1 || ngon == -1) return;

    for (size_t i = 0; i < do_thi.ke[goc].size(); i++) {
        if (do_thi.ke[goc][i].id_lang_gieng == ngon) {
            do_thi.ke[goc][i].trong_so = trong_so_moi;
            break;
        }
    }
    for (size_t i = 0; i < do_thi.ke[ngon].size(); i++) {
        if (do_thi.ke[ngon][i].id_lang_gieng == goc) {
            do_thi.ke[ngon][i].trong_so = trong_so_moi;
            break;
        }
    }
}

void hien_thi_duong_di(DoThi& do_thi, const string& ten_goc, const string& ten_ngon) {
    int goc = -1, ngon = -1;
    for (int i = 0; i < do_thi.so_nut; i++) {
        if (do_thi.ten_tinh[i] == ten_goc) goc = i;
        if (do_thi.ten_tinh[i] == ten_ngon) ngon = i;
    }
    if (goc == -1 || ngon == -1) return;

    for (const Canh& canh : do_thi.ke[goc]) {
        if (canh.id_lang_gieng == ngon) {
            cout << "Quãng đường " << ten_goc << " - " << ten_ngon << ": " << canh.trong_so << " km\n";
            return;
        }
    }
}

int main() {
    system("chcp 65001 > nul");

    DoThi do_thi;

    them_canh(do_thi, "Hà nội", "Hải dương", 55);
    hien_thi_duong_di(do_thi, "Hà nội", "Hải dương");

    cap_nhat_canh(do_thi, "Hà nội", "Hải dương", 50);
    cout << "[Sau khi cập nhật]\n";
    hien_thi_duong_di(do_thi, "Hà nội", "Hải dương");

    return 0;
}