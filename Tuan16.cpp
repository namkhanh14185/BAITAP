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

void liet_ke_tinh(DoThi& do_thi) {
    cout << "=== DANH SÁCH CÁC TỈNH TRONG HỆ THỐNG ===\n";
    for (int i = 0; i < do_thi.so_nut; i++) {
        cout << "- " << do_thi.ten_tinh[i] << "\n";
    }
}

void tim_tinh_lan_can(DoThi& do_thi, const string& ten) {
    int id = -1;
    for (int i = 0; i < do_thi.so_nut; i++) {
        if (do_thi.ten_tinh[i] == ten) {
            id = i;
            break;
        }
    }
    if (id == -1) {
        cout << "Không tìm thấy tỉnh " << ten << " trong hệ thống.\n";
        return;
    }
    cout << "CÁC TỈNH LÂN CẬN CỦA " << ten << " ===\n";
    for (const Canh& canh : do_thi.ke[id]) {
        cout << "-> " << do_thi.ten_tinh[canh.id_lang_gieng] << " (" << canh.trong_so << " km)\n";
    }
}

int main() {
    system("chcp 65001 > nul");

    DoThi do_thi;

    them_canh(do_thi, "Hà nội", "Hải dương", 55);
    them_canh(do_thi, "Hải dương", "Hưng yên", 40);
    them_canh(do_thi, "Hà nội", "Phủ lý", 60);

    liet_ke_tinh(do_thi);
    cout << "\n";
    tim_tinh_lan_can(do_thi, "Hà nội");

    return 0;
}