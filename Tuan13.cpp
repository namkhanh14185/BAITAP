#include <iostream>
using namespace std;

struct Node {
    int du_lieu;
    Node* trai;
    Node* phai;
    Node(int gia_tri) {
        du_lieu = gia_tri;
        trai = nullptr;
        phai = nullptr;
    }
};

void add_node(Node* &goc, int gia_tri) {
    if (goc == nullptr) {
        goc = new Node(gia_tri);
        return;
    }
    if (gia_tri < goc->du_lieu) add_node(goc->trai, gia_tri);
    else add_node(goc->phai, gia_tri);
}

Node* initial_bst(int a[], int so_phan_tu) {
    Node* goc = nullptr;
    for (int i = 0; i < so_phan_tu; i++) add_node(goc, a[i]);
    return goc;
}

Node* Search(Node* goc, int khoa, int &so_buoc) {
    while (goc != nullptr) {
        so_buoc++;
        if (goc->du_lieu == khoa) return goc;
        if (khoa < goc->du_lieu) goc = goc->trai;
        else goc = goc->phai;
    }
    return nullptr;
}

int main() {
    int a[] = {2001, 2002, 2006, 2007, 2003, 2004, 2005, 2001, 1999, 2004};
    int so_phan_tu = sizeof(a) / sizeof(a[0]);
    Node* goc = initial_bst(a, so_phan_tu);
    int muc_tieu = 2004;
    int so_buoc = 0;
    Node* ket_qua = Search(goc, muc_tieu, so_buoc);
    if (ket_qua != nullptr) cout << ket_qua->du_lieu << " " << so_buoc << endl;
    else cout << -1 << " " << so_buoc << endl;
    return 0;
}