#include <bits/stdc++.h>
using namespace std;

struct HangHoa
{
    int MaHangHoa;
    char TenHangHoa[100];
    char LoaiHang[100];
    int SoLuong;
    float GiaTien;
};
struct NodeHangHoa
{
    HangHoa data;
    NodeHangHoa *next;
    NodeHangHoa *pre;
};
struct ListHangHoa
{
    NodeHangHoa *head;
    NodeHangHoa *tail;
};
void taoListHangHoa(ListHangHoa &lHangHoa)
{
    lHangHoa.head = NULL;
    lHangHoa.tail = NULL;
}
NodeHangHoa *taoNodeHangHoa(HangHoa hh)
{
    NodeHangHoa *nodeHH = new NodeHangHoa;
    if (nodeHH == NULL)
    {
        cout << "Ko du bo nho ";
        return NULL;
    }
    else
    {
        nodeHH->data = hh;
        nodeHH->next = NULL;
        nodeHH->pre = NULL;
    }
    return nodeHH;
}

//
void giaodienHangHoa()
{
    cout << "\n***************************************************DANH SACH HANG HOA***************************************************\n"
         << endl;
    cout << setw(20) << "Ma hang hoa"
         << setw(30) << "Ten hang hoa"
         << setw(30) << "Loai hang hoa"
         << setw(20) << "So luong"
         << setw(20) << "Don gia\n";
}

// addTail
void themCuoiHangHoa(ListHangHoa &lHangHoa, NodeHangHoa *p)
{
    if (lHangHoa.head == NULL)
    {
        lHangHoa.head = lHangHoa.tail = p;
    }
    else
    {
        p->pre = lHangHoa.tail;
        lHangHoa.tail->next = p;
        lHangHoa.tail = p;
    }
}
// 1. Nhap

void nhapRiengHangHoa(HangHoa &hh)
{
    cin.ignore();
    cout << "Nhap ma hang hoa : ";
    cin >> hh.MaHangHoa;
    cin.ignore();
    cout << "Nhap ten hang hoa : ";
    cin.getline(hh.TenHangHoa, 100);
    cout << "Nhap loai hang hoa : ";
    cin.getline(hh.LoaiHang, 100);
    cout << "Nhap so luong hang hoa : ";
    cin >> hh.SoLuong;
    cout << "Nhap gia tien hang hoa : ";
    cin >> hh.GiaTien;
    cout << endl;
}
void nhapHangHoa(ListHangHoa &lHangHoa)
{
    int n;
    cout << "Nhap so luong :  ";
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        HangHoa hh;
        nhapRiengHangHoa(hh);
        NodeHangHoa *nodeHH = taoNodeHangHoa(hh);
        themCuoiHangHoa(lHangHoa, nodeHH);
    }
}
// 2. Xuat
void xuatHangHoa(ListHangHoa lHangHoa)
{
    giaodienHangHoa();
    for (NodeHangHoa *nodeHH = lHangHoa.head; nodeHH != NULL; nodeHH = nodeHH->next)
    {
        cout << setw(20) << nodeHH->data.MaHangHoa << setw(30) << nodeHH->data.TenHangHoa << setw(30) << nodeHH->data.LoaiHang << setw(20) << nodeHH->data.SoLuong << setw(20) << nodeHH->data.GiaTien << endl;
    }
    cout << "\n*************************************************************************************************************************\n";
    cout << endl;
}

// 3. Sua hang hoa theo ma
NodeHangHoa *timHangHoaTheoMa(ListHangHoa lHangHoa, int maCanTim)
{
    for (NodeHangHoa *p = lHangHoa.head; p != NULL; p = p->next)
    {
        if (p->data.MaHangHoa == maCanTim)
        {
            return p;
        }
    }
    return NULL;
}

void suaHangHoaTheoMa(ListHangHoa &lHangHoa, int maHangHoa)
{
    NodeHangHoa *p = timHangHoaTheoMa(lHangHoa, maHangHoa);
    if (p != NULL)
    {
        HangHoa hh;
        nhapRiengHangHoa(hh);
        p->data = hh;
        xuatHangHoa(lHangHoa);
    }
    else
    {
        cout << "Ko co hang hoa co ma " << maHangHoa << ", ko the sua" << endl;
    }
}
// 4. Ghi file
void luuHangHoa(ListHangHoa lHangHoa)
{
    FILE *f;
    f = fopen("HANGHOA.dat", "wb");
    for (NodeHangHoa *k = lHangHoa.head; k != NULL; k = k->next)
    {
        fwrite(&k->data, sizeof(HangHoa), 1, f);
    }
    fclose(f);
    cout << "Ghi file thanh cong!" << endl;
}
// 5. Đọc file
void docHangHoa(ListHangHoa &lHangHoa)
{
    FILE *f;
    taoListHangHoa(lHangHoa);
    f = fopen("HANGHOA.dat", "rb");
    if (f == NULL)
        cout << "Ko mo duoc FILE !" << endl;
    else
    {
        HangHoa h;
        while (fread(&h, sizeof(HangHoa), 1, f) == 1)
        {
            themCuoiHangHoa(lHangHoa, taoNodeHangHoa(h));
        }
    }
    fclose(f);
    cout << "Doc FILE thanh cong!" << endl;
    xuatHangHoa(lHangHoa);
}
// 6. Tìm HH theo mã
void ketquaTimKiemTheoMa(ListHangHoa lHangHoa, int maCanTim)
{
    NodeHangHoa *p = timHangHoaTheoMa(lHangHoa, maCanTim);
    if (p != NULL)
    {
        cout << "Tim thay !";
        cout << "Hang hoa co ma " << p->data.MaHangHoa << " la : " << p->data.TenHangHoa << endl;
    }
    else
    {
        cout << "Ko tim thay hang hoa co ma " << maCanTim << " ! ";
    }
}
// 7. hiện các sản phẩm đồng giá
void xoaHangHoaDau(ListHangHoa &lHangHoa)
{
    NodeHangHoa *p;
    // neu ds ko null
    if (lHangHoa.head != NULL)
    {
        p = lHangHoa.head;
        lHangHoa.head = lHangHoa.head->next;
        lHangHoa.head->pre = NULL;
        // p->next = NULL;
        delete p;
        // sau khi xoa, neu danh sach NULL
        if (lHangHoa.head == NULL)
            lHangHoa.tail = NULL;
    }
}
void xoaHangHoaCuoi(ListHangHoa &lHangHoa)
{
    NodeHangHoa *p;
    if (lHangHoa.head != NULL)
    {
        p = lHangHoa.tail;
        lHangHoa.tail = lHangHoa.tail->pre;
        lHangHoa.tail->next = NULL;
        delete p;
        if (lHangHoa.tail == NULL)
            lHangHoa.head = NULL;
    }
}
void xoaHangHoaTheoMa(ListHangHoa &lHangHoa, int maCanXoa)
{
    NodeHangHoa *p = timHangHoaTheoMa(lHangHoa, maCanXoa);
    // neu tim thay
    if (p != NULL)
    {
        cout << "Tim thay !\n";
        // neu node o cuoi=>xoa cuoi
        if (p->next == NULL)
        {
            xoaHangHoaCuoi(lHangHoa);
            cout << "Xoa thanh cong !" << endl;
            xuatHangHoa(lHangHoa);
            return;
        }
        // neu node o dau =>xoa dau
        if (p->pre == NULL)
        {
            xoaHangHoaDau(lHangHoa);
            cout << "Xoa thanh cong !" << endl;
            xuatHangHoa(lHangHoa);
            return;
        }
        // neu node o giua
        p->pre->next = p->next;
        p->next->pre = p->pre;
        // gan pre vs next cua p ve null
        p->next = NULL;
        p->pre = NULL;
        delete p;
        cout << "Xoa thanh cong !" << endl;
        xuatHangHoa(lHangHoa);
    }
    else
    {
        cout << "Ko tim thay ! ";
    }
}
// 8. Sắp xếp tăng dần theo số lượng hàng hoá
void sapxepTheoSoLuong(ListHangHoa &lHangHoa)
{
    NodeHangHoa *h, *k;
    h = lHangHoa.head;
    while (h != NULL)
    {
        k = h->next;
        while (k != NULL)
        {
            if (k->data.SoLuong < h->data.SoLuong)
            {
                swap(k->data, h->data);
            }
            k = k->next;
        }
        h = h->next;
    }
    xuatHangHoa(lHangHoa);
}
// 9. Đếm số hàng hoá theo loại hàng
int demHangHoaTheoLoaiHang(ListHangHoa lHangHoa)
{
    cin.ignore();
    char loaiHang[100];
    cout << "Nhap loai hang hoa can dem : ";
    cin.getline(loaiHang, 100);
    NodeHangHoa *p = lHangHoa.head;
    int sum = 0;
    while (p != NULL)
    {
        if (strcmp(loaiHang, p->data.LoaiHang) == 0)
        {
            sum += p->data.SoLuong;
        }
        p = p->next;
    }
    return sum;
}
// 10. Tính tổng tất cả số lượng hàng hoá
int tinhTongHangHoa(ListHangHoa lHangHoa)
{
    NodeHangHoa *p = lHangHoa.head;
    int sum = 0;
    while (p != NULL)
    {
        sum += p->data.SoLuong;
        p = p->next;
    }
    return sum;
}

// Hiện hàng hoá đồng giá
void hienSanPhamDongGia(ListHangHoa lHangHoa, int gia)
{
    NodeHangHoa *p;
    p = lHangHoa.head;
    int dem = 0;
    if (lHangHoa.head != NULL)
    {
        giaodienHangHoa();
        while (p != NULL)
        {
            if (p->data.GiaTien == gia)
            {
                dem++;
                cout << setw(20) << p->data.MaHangHoa
                     << setw(30) << p->data.TenHangHoa
                     << setw(30) << p->data.LoaiHang
                     << setw(20) << p->data.SoLuong
                     << setw(20) << p->data.GiaTien << endl;
            }
            p = p->next;
        }
    }
    else
    {
        cout << "\n\tDanh sach rong  " << endl;
    }
    if (dem == 0)
        cout << "Ko co san phan nao co gia " << gia;
}
// 11. Them hang hoa Q truoc hang hoa P
void themDauHangHoa(ListHangHoa &lHangHoa, NodeHangHoa *p)
{
    if (lHangHoa.head == NULL)
    {
        lHangHoa.head = lHangHoa.tail = p;
    }
    else
    {
        p->next = lHangHoa.head;
        lHangHoa.head->pre = p;
        lHangHoa.head = p;
    }
}

void them_Q_Truoc_P(ListHangHoa &lHangHoa, NodeHangHoa *q, NodeHangHoa *p)
{
    // neu p la node dau
    if (p->pre == NULL)
    {
        themDauHangHoa(lHangHoa, q);
    }
    else
    {
        q->next = p;
        q->pre = p->pre;
        p->pre->next = q;
        p->pre = q;
    }
}

void themHangHoa_Q_Truoc_P(ListHangHoa &lHangHoa, int maHangHoa)
{
    NodeHangHoa *q = new NodeHangHoa();
    NodeHangHoa *p = timHangHoaTheoMa(lHangHoa, maHangHoa);
    if (p != NULL)
    {
        HangHoa hh;
        nhapRiengHangHoa(hh);
        q = taoNodeHangHoa(hh);
        them_Q_Truoc_P(lHangHoa, q, p);
        cout << "Danh sach hang hoa sau khi them : ";
        xuatHangHoa(lHangHoa);
    }

    else
    {
        cout << "Ko tim thay hang hoa co ma " << maHangHoa << ", ko the them";
    }
}

// 12. Them moi 1 hang hoa va tu dong sap xep theo ma
void themHangHoaTuDongSapXep(ListHangHoa &lHangHoa)
{
    HangHoa hh;
    cout << "Nhap thong tin hang hoa moi\n";
    nhapRiengHangHoa(hh);
    NodeHangHoa *q = taoNodeHangHoa(hh);

    for (NodeHangHoa *p = lHangHoa.head; p != NULL; p = p->next)
    {
        // neu p la node dau
        if (p->data.MaHangHoa > q->data.MaHangHoa && p->pre == NULL)
        {
            themDauHangHoa(lHangHoa, q);
            break;
        }
        // neu p la node cuoi
        if (p->data.MaHangHoa <= q->data.MaHangHoa && p->next == NULL)
        {
            themCuoiHangHoa(lHangHoa, q);
            break;
        }
        //
        if (p->data.MaHangHoa < q->data.MaHangHoa && p->next->data.MaHangHoa > q->data.MaHangHoa)
        {
            q->next = p->next;
            q->pre = p;
            p->next->pre = q;
            p->next = q;
            break;
        }
    }
}

// 11.Sap xep theo ten hang hoa
void sapXepHangHoaTheoTen(ListHangHoa &lHangHoa)
{
    HangHoa hh;
    if (lHangHoa.head == NULL)
    {
        cout << "Danh sach rong ";
        return;
    }
    else
    {
        NodeHangHoa *node1, *node2;
        char tempTen1[100], tempTen2[100];
        for (node1 = lHangHoa.head; node1 != NULL; node1 = node1->next)
        {
            for (node2 = node1->next; node2 != NULL; node2 = node2->next)
            {
                strcpy(tempTen1, node1->data.TenHangHoa);
                strcpy(tempTen2, node2->data.TenHangHoa);
                if (strcmp(tempTen1, tempTen2) > 0)
                {
                    hh = node1->data;
                    node1->data = node2->data;
                    node2->data = hh;
                }
            }
        }
        xuatHangHoa(lHangHoa);
    }
}

void sapXepTheoLoaiHangWhile(ListHangHoa &lHangHoa)
{
    NodeHangHoa *p, *q, *curr;
    HangHoa temp;
    for (p = lHangHoa.head->next; p != NULL; p = p->next)
    {
        temp = p->data;
        curr = p;
        q = p->pre;
        while (q != NULL && strcmp(q->data.LoaiHang, temp.LoaiHang) > 0)
        {
            curr->data = q->data;
            curr = q;
            q = q->pre;
        }
        curr->data = temp;
    }
    xuatHangHoa(lHangHoa);
}

void sapXepTheoLoaiHangFor(ListHangHoa &lHangHoa)
{
    for (NodeHangHoa *i = lHangHoa.head; i != NULL; i = i->next)
    {
        for (NodeHangHoa *j = i->next; j != NULL; j = j->next)
        {
            if (strcmp(i->data.LoaiHang, j->data.LoaiHang) > 0)
            {
                swap(i->data, j->data);
            }
        }
    }
    xuatHangHoa(lHangHoa);
}

// 12. Hien danh sach hang hoa theo co don gia < x
void hienHangHoaTheoDonGia(ListHangHoa lHangHoa)
{
    float donGia;
    int dem = 0;
    NodeHangHoa *nodeHH = lHangHoa.head;
    cout << "Nhap don gia can tim kiem : ";
    cin >> donGia;
    cout << "Danh sach hang hoa co don gia nho hon " << donGia << endl;
    if (lHangHoa.head != NULL)
    {
        giaodienHangHoa();
        while (nodeHH != NULL)
        {
            if (nodeHH->data.GiaTien < donGia)
            {
                dem++;
                cout << setw(20) << nodeHH->data.MaHangHoa << setw(30) << nodeHH->data.TenHangHoa << setw(30) << nodeHH->data.LoaiHang << setw(20) << nodeHH->data.SoLuong << setw(20) << nodeHH->data.GiaTien << endl;
            }
            nodeHH = nodeHH->next;
        }
    }
    else
    {
        cout << "Danh sach rong\n";
    }

    if (dem == 0)
    {
        cout << "\nKo co hang hoa noa co don gia nho hon " << donGia;
    }
}

//--------------------------------------------------------------------------------------------------------------------------
struct Date
{
    int ngay, thang, nam;
};

struct HoaDon
{
    int MaHoaDon;
    int SoLuongHangHoa;
    float TongTien;
    int hinhThucThanhToan;
    Date NgayLapHoaDon;
};
struct NodeHoaDon
{
    HoaDon data;
    NodeHoaDon *next;
    NodeHoaDon *pre;
};
struct ListHoaDon
{
    NodeHoaDon *head;
    NodeHoaDon *tail;
};
void taoListHoaDon(ListHoaDon &lHoaDon)
{
    lHoaDon.head = NULL;
    lHoaDon.tail = NULL;
}
NodeHoaDon *taoNodeHoaDon(HoaDon hd)
{
    NodeHoaDon *nodeHD = new NodeHoaDon();
    if (nodeHD == NULL)
    {
        cout << "Ko du bo nho";
        return NULL;
    }
    else
    {
        nodeHD->data = hd;
        nodeHD->next = NULL;
        nodeHD->pre = NULL;
    }
    return nodeHD;
}

// them cuoi
void themCuoiHoaDon(ListHoaDon &lHoaDon, NodeHoaDon *p)
{
    if (lHoaDon.head == NULL)
    {
        lHoaDon.head = lHoaDon.tail = p;
    }
    else
    {
        lHoaDon.tail->next = p;
        p->pre = lHoaDon.tail;
        lHoaDon.tail = p;
    }
}
// nhap
void nhapNgayThangNam(Date &date)
{
    cout << "Nhap ngay : ";
    cin >> date.ngay;
    cout << "Nhap thang : ";
    cin >> date.thang;
    cout << "Nhap nam : ";
    cin >> date.nam;
}

// 1. nhap hoa don

void nhapRiengHoaDon(HoaDon &hd)
{
    cout << "\nNhap ma hoa don : ";
    cin >> hd.MaHoaDon;
    cout << "Nhap thoi gian lap hoa don \n";
    nhapNgayThangNam(hd.NgayLapHoaDon);
    cout << "Nhap so luong hang hoa : ";
    cin >> hd.SoLuongHangHoa;
    cout << "Nhap tong tien hoa don :";
    cin >> hd.TongTien;
    do
    {
        cout << "Hinh thuc thanh toan (0-Chuyen khoan| 1-Tien mat) : ";
        cin >> hd.hinhThucThanhToan;
    } while (hd.hinhThucThanhToan != 0 && hd.hinhThucThanhToan != 1);
    cout << endl;
}
void nhapHoaDon(ListHoaDon &lHoaDon)
{
    int sl;
    cout << "Nhap so luong hoa don : ";
    cin >> sl;
    int i = 1;
    while (i <= sl)
    {
        HoaDon hd;
        cout << "\nNhap ma hoa don : ";
        cin >> hd.MaHoaDon;
        cout << "Nhap thoi gian lap hoa don \n";
        nhapNgayThangNam(hd.NgayLapHoaDon);
        cout << "Nhap so luong hang hoa : ";
        cin >> hd.SoLuongHangHoa;
        cout << "Nhap tong tien hoa don :";
        cin >> hd.TongTien;
        do
        {
            cout << "Hinh thuc thanh toan (0-Chuyen khoan| 1-Tien mat) : ";
            cin >> hd.hinhThucThanhToan;
        } while (hd.hinhThucThanhToan != 0 && hd.hinhThucThanhToan != 1);
        cout << endl;
        NodeHoaDon *p = taoNodeHoaDon(hd);
        themCuoiHoaDon(lHoaDon, p);
        i++;
    }
}

// 2. xuat hoa don
void giaoDienXuatHoaDon(NodeHoaDon *p)
{
    cout << "\n---------------MA HOA DON " << p->data.MaHoaDon << "------------------\n";
    cout << "So luong hang hoa : " << p->data.SoLuongHangHoa << endl;
    cout << "Tong tien :" << p->data.TongTien << endl;
    if (p->data.hinhThucThanhToan == 0)
    {
        cout << "Hinh thuc thanh toan : Chuyen khoan" << endl;
    }
    if (p->data.hinhThucThanhToan == 1)
    {
        cout << "Hinh thuc thanh toan : Tien mat" << endl;
    }
    cout << setw(45) << "Thoi gian\n " << setw(35) << p->data.NgayLapHoaDon.ngay << "/" << p->data.NgayLapHoaDon.thang << "/" << p->data.NgayLapHoaDon.nam << endl;
    cout << "---------------------------------------------\n";
}

void xuatHoaDon(ListHoaDon lHoaDon)
{
    NodeHoaDon *p = lHoaDon.head;
    while (p != NULL)
    {
        giaoDienXuatHoaDon(p);
        p = p->next;
    }
}

// 4. luu file hoa don
void luuHoaDon(ListHoaDon lHoaDon)
{
    FILE *f;
    f = fopen("HOADON.dat", "wb");
    for (NodeHoaDon *k = lHoaDon.head; k != NULL; k = k->next)
    {
        fwrite(&k->data, sizeof(HoaDon), 1, f);
    }
    fclose(f);
    cout << "Ghi file thanh cong!" << endl;
}

// 5. doc file hoa don
void docHoaDon(ListHoaDon &lHoaDon)
{
    FILE *f;
    taoListHoaDon(lHoaDon);
    f = fopen("HOADON.dat", "rb");
    if (f == NULL)
        cout << "Ko mo duoc FILE !" << endl;
    else
    {
        HoaDon h;
        while (fread(&h, sizeof(HoaDon), 1, f) == 1)
        {
            themCuoiHoaDon(lHoaDon, taoNodeHoaDon(h));
        }
    }
    fclose(f);
    cout << "Doc FILE thanh cong!" << endl;
    xuatHoaDon(lHoaDon);
}

// 6. tim kiem hoa don theo ma
NodeHoaDon *timKiemHoaDonTheoMa(ListHoaDon lHoaDon, int maHoaDon)
{

    NodeHoaDon *nodeCanTim = new NodeHoaDon;
    for (NodeHoaDon *p = lHoaDon.head; p != NULL; p = p->next)
    {
        if (p->data.MaHoaDon == maHoaDon)
        {
            nodeCanTim = p;
            return nodeCanTim;
        }
    }
    return NULL;
}

// 7. Xoa hoa don theo ma
void xoaHoaDonDau(ListHoaDon &lHoaDon)
{
    NodeHoaDon *p;
    // neu ds ko null
    if (lHoaDon.head != NULL)
    {
        p = lHoaDon.head;
        lHoaDon.head->next->pre = NULL;
        lHoaDon.head = lHoaDon.head->next;

        delete p;
        // sau khi xoa, neu danh dach NULL
        if (lHoaDon.head->next == NULL)
        {
            lHoaDon.tail = NULL;
        }
    }
    xuatHoaDon(lHoaDon);
    cout << "XOA THANH CONG !";
}
void xoaHoaDonCuoi(ListHoaDon &lHoaDon)
{
    NodeHoaDon *p;
    if (lHoaDon.head != NULL)
    {
        p = lHoaDon.tail;
        p->pre->next = NULL;
        lHoaDon.tail = p->pre;
        delete p;
        if (lHoaDon.tail->pre == NULL)
        {
            lHoaDon.head = NULL;
        }
    }
    xuatHoaDon(lHoaDon);
    cout << "XOA THANH CONG !";
}

void xoaHoaDonTheoMa(ListHoaDon &lHoaDon, int maCanXoa)
{
    // tim kiem hoa don co ma
    NodeHoaDon *p = timKiemHoaDonTheoMa(lHoaDon, maCanXoa);
    if (p != NULL)
    {
        cout << "Tim thay hoa don co ma " << maCanXoa << endl;
        // neu node o cuoi
        if (p->next == NULL)
        {
            xoaHoaDonCuoi(lHoaDon);
            return;
        }
        // neu hoa don o dau
        if (p->pre == NULL)
        {
            xoaHoaDonDau(lHoaDon);
            return;
        }
        // neu hoa don giua
        p->pre->next = p->next;
        p->next->pre = p->pre;
        // gan pre vs next cua node can xoa ve null
        p->next = NULL;
        p->pre = NULL;
        delete p;
        xuatHoaDon(lHoaDon);
        cout << "Xoa thanh cong " << endl;
    }
    else
    {
        cout << "Ko tim thay hoa don co ma " << maCanXoa << endl;
    }
}
// 8. Sap xep theo tong tien hoa don
void sapXepHoaDonTheoSoLuongHang(ListHoaDon &lHoaDon)
{
    HoaDon temp;
    NodeHoaDon *a = new NodeHoaDon();
    NodeHoaDon *b = new NodeHoaDon();
    for (a = lHoaDon.head; a != NULL; a = a->next)
    {
        for (b = a->next; b != NULL; b = b->next)
        {
            if (a->data.SoLuongHangHoa < b->data.SoLuongHangHoa)
            {
                temp = a->data;
                a->data = b->data;
                b->data = temp;
            }
        }
    }
    cout << "Danh sach hoa don sau khi sap xep : \n";
    xuatHoaDon(lHoaDon);
}

// 9. Dem hoa don co trong nam xac dinh
void demHoaDonTrongNam(ListHoaDon lHoaDon)
{
    Date date;
    nhapNgayThangNam(date);
    int dem = 0;
    for (NodeHoaDon *p = lHoaDon.head; p != NULL; p = p->next)
    {
        if (p->data.NgayLapHoaDon.ngay == date.ngay && p->data.NgayLapHoaDon.thang == date.thang && p->data.NgayLapHoaDon.nam == date.nam)
        {
            dem++;
        }
    }
    if (dem == 0)
        cout << "Ko co hoa don nao duoc lap vao  " << date.ngay << "/" << date.thang << "/" << date.nam << endl;
    else
        cout << "So hoa don co trong nam " << date.ngay << "/" << date.thang << "/" << date.nam << ": " << dem << endl;
}
// 10. Tinh tong tien tat ca hoa don co trong nam nao do
void tongTienHoaDonTrongNam(ListHoaDon lHoaDon)
{
    int namCanTinh, sum = 0;
    cout << "Nhap nam can tinh : ";
    cin >> namCanTinh;
    for (NodeHoaDon *p = lHoaDon.head; p != NULL; p = p->next)
    {
        if (p->data.NgayLapHoaDon.nam == namCanTinh)
        {
            sum = sum + p->data.TongTien;
            cout << "Hoa don " << p->data.MaHoaDon << " : " << p->data.TongTien << endl;
        }
    }
    if (sum == 0)
        cout << "Ko co hoa don nao duoc lap vao nam " << namCanTinh << endl;
    else

        cout << "Tong tien hoa don co trong nam " << namCanTinh << ": " << sum << endl;
}
// 13. Sua hoa don theo ma
void suaHoaDonTheoMa(ListHoaDon &lHoaDon, int maHoaDon)
{
    NodeHoaDon *p = timKiemHoaDonTheoMa(lHoaDon, maHoaDon);
    if (p != NULL)
    {
        HoaDon hd;
        nhapRiengHoaDon(hd);
        p->data = hd;
        xuatHoaDon(lHoaDon);
    }
    else
    {
        cout << "Ko co hoa don co ma " << maHoaDon << endl;
    }
}
// 12. Tinh tong tien hoa don tu a->b
void xuatHoaDonTuNgayADenNgayB(ListHoaDon lHoaDon)
{
    Date ngayBatDau, ngayKetThuc;
    cout << "Nhap  thoi gian bat dau\n ";
    nhapNgayThangNam(ngayBatDau);
    cout << "Nhap thoi gian ket thuc\n";
    nhapNgayThangNam(ngayKetThuc);
    cout << "Danh sach hoa don tu " << ngayBatDau.ngay << "/" << ngayBatDau.thang << "/" << ngayBatDau.nam << " - " << ngayKetThuc.ngay << "/" << ngayKetThuc.thang << "/" << ngayKetThuc.nam << endl;
    for (NodeHoaDon *p = lHoaDon.head; p != NULL; p = p->next)
    {
        if (p->data.NgayLapHoaDon.nam >= ngayBatDau.nam && p->data.NgayLapHoaDon.nam <= ngayKetThuc.nam)
        {
            if (p->data.NgayLapHoaDon.nam == ngayBatDau.nam && p->data.NgayLapHoaDon.thang < ngayBatDau.thang)
                continue;
            if (p->data.NgayLapHoaDon.nam == ngayKetThuc.nam && p->data.NgayLapHoaDon.thang > ngayKetThuc.thang)
                continue;
            if (p->data.NgayLapHoaDon.nam == ngayBatDau.nam && p->data.NgayLapHoaDon.thang == ngayBatDau.thang && p->data.NgayLapHoaDon.ngay < ngayBatDau.ngay)
                continue;
            if (p->data.NgayLapHoaDon.nam == ngayKetThuc.nam && p->data.NgayLapHoaDon.thang == ngayKetThuc.thang && p->data.NgayLapHoaDon.ngay > ngayKetThuc.ngay)
                continue;
            giaoDienXuatHoaDon(p);
        }
    }
}
// 13. Them 1 hoa don vao sau 1 hoa don
void themDauHoaDon(ListHoaDon &lHoaDon, NodeHoaDon *p)
{
    if (lHoaDon.head == NULL)
    {
        lHoaDon.head = lHoaDon.tail = p;
    }
    else
    {
        p->next = lHoaDon.head;
        lHoaDon.head->pre = p;
        lHoaDon.head = p;
        p->pre = NULL; //?? ko can thiet
    }
}
void them_Q_Sau_P(ListHoaDon &lHoaDon, NodeHoaDon *q, NodeHoaDon *p)
{
    // p la node cuoi
    if (p->next == NULL)
    {
        themCuoiHoaDon(lHoaDon, q);
    }
    else
    {
        q->next = p->next;
        q->pre = p;
        p->next->pre = q;
        p->next = q;
    }
}
void themHoaDon_Q_Sau_P(ListHoaDon &lHoaDon)
{
    // P la node co trong danh sach
    int maHoaDon;
    NodeHoaDon *q = new NodeHoaDon();
    cout << "Nhap ma hoa don can tim co trong danh sach : ";
    cin >> maHoaDon;
    NodeHoaDon *p = timKiemHoaDonTheoMa(lHoaDon, maHoaDon);
    if (p != NULL)
    {

        HoaDon hd;
        nhapRiengHoaDon(hd);
        q = taoNodeHoaDon(hd);
        them_Q_Sau_P(lHoaDon, q, p);
        xuatHoaDon(lHoaDon);
    }
    else
    {
        cout << "Ko tim thay hoa don co ma " << maHoaDon << ", ko the them \n";
    }
}
void menu(ListHangHoa &lHangHoa, ListHoaDon &lHoaDon)
{
    int luaChonDoiTuong;
    do
    {
        cout << "-----------------QUAN LY------------------\n";
        cout << " 1.Hang hoa \n";
        cout << " 2.Hoa don \n";
        cout << "-----------------------------------------\n";
        cout << "Chon doi tuong can quan ly :";
        cin >> luaChonDoiTuong;

        switch (luaChonDoiTuong)
        {
        case 1:
        {
            int luaChon, maHangHoa;
            do
            {
                cout << "\n\t\t====================================HANG HOA====================================\n";
                cout << "\t\t0. Thoat !\n";
                cout << "\t\t1. Nhap thong tin hang hoa\n";
                cout << "\t\t2. Xuat thong tin hang hoa\n";
                cout << "\t\t3. Sua thong tin hang hoa theo ma\n";
                cout << "\t\t4. Ghi file HangHoa\n";
                cout << "\t\t5. Doc file HangHoa\n";
                cout << "\t\t6. Tim kiem hang hoa theo ma\n";
                cout << "\t\t7. Xoa hang hoa theo ma\n";
                cout << "\t\t8. Sap xep tang dan theo so luong hang hoa\n";
                cout << "\t\t9. Dem hang hoa theo loai hang\n";
                cout << "\t\t10. Tinh tong so luong tat ca hang hoa\n";
                // cout << "\t\t11. Them 1 hang hoa vao truoc 1 hang hoa\n";
                // // cout << "\t\t12. Them moi 1 hang hoa va tu dong sap xep theo ma\n";
                // // cout << "\t\t13. Sap xep hang hoa theo ten a->z\n";
                // // cout << "\t\t14. Sap xep hang hoa theo loai hang\n";

                cout << "\t\t11. Sap xep hang hoa theo ten \n";
                cout << "\t\t12. Hien danh sach hang hoa co don gia < x \n";

                cout << "\n\t\t================================================================================\n";

                cout << "NHAP LUA CHON : ";
                cin >> luaChon;
                switch (luaChon)
                {
                case 1:
                    nhapHangHoa(lHangHoa);
                    break;
                case 2:
                    xuatHangHoa(lHangHoa);
                    break;
                case 3:
                    cout << "Nhap ma hang hoa can sua : ";
                    cin >> maHangHoa;
                    suaHangHoaTheoMa(lHangHoa, maHangHoa);
                    break;
                case 4:
                    luuHangHoa(lHangHoa);
                    break;
                case 5:
                    docHangHoa(lHangHoa);
                    break;
                case 6:
                    cout << "Nhap ma hang hoa can tim : ";
                    cin >> maHangHoa;
                    ketquaTimKiemTheoMa(lHangHoa, maHangHoa);
                    break;
                case 7:
                    cout << "Nhap ma hang hoa can xoa : ";
                    cin >> maHangHoa;
                    xoaHangHoaTheoMa(lHangHoa, maHangHoa);
                    break;
                case 8:
                    sapxepTheoSoLuong(lHangHoa);
                    break;
                case 9:
                {
                    int kq = demHangHoaTheoLoaiHang(lHangHoa);
                    if (kq != 0)
                    {
                        cout << "Tong hang hoa cua loai can dem la : " << kq << endl;
                        break;
                    }
                    else
                    {
                        cout << "Khong co loai hang hoa can tim !" << endl;
                        break;
                    }
                }
                case 10:
                    cout << "Tong so luong tat ca hang hoa la : " << tinhTongHangHoa(lHangHoa) << endl;
                    break;
                // case 11:
                //     cout << "Nhap ma hang hoa co trong danh sach : ";
                //     cin >> maHangHoa;
                //     themHangHoa_Q_Truoc_P(lHangHoa, maHangHoa);
                //     break;
                // case 12:
                //     themHangHoaTuDongSapXep(lHangHoa);
                //     xuatHangHoa(lHangHoa);
                //     break;
                case 11:
                    sapXepHangHoaTheoTen(lHangHoa);
                    break;
                // case 14:
                //     // sapXepTheoLoaiHang(lHangHoa);
                //     sapXepTheoLoaiHangFor(lHangHoa);
                //     break;
                case 12:
                    hienHangHoaTheoDonGia(lHangHoa);
                    break;
                case 0:
                    cout << "Ban da thoat khoi chuong trinh !\n";
                    break;
                }
            } while (luaChon != 0);
            break;
        }
        case 2:
        {
            int luaChon, maHoaDon;
            NodeHoaDon *p;
            do
            {
                cout << "\n\t\t====================================HOA DON====================================\n";
                cout << "\t\t0. Thoat !\n";
                cout << "\t\t1. Nhap thong tin hoa don\n";
                cout << "\t\t2. Xuat thong tin hoa don\n";
                cout << "\t\t3. Sua thong tin hoa don theo ma\n";
                cout << "\t\t4. Ghi file HoaDon\n";
                cout << "\t\t5. Doc file HoaDon\n";
                cout << "\t\t6. Tim kiem hoa don theo ma\n";
                cout << "\t\t7. Xoa hoa don cuoi\n";
                cout << "\t\t8. Sap xep giam dan theo so luong hang hoa trong hoa don\n";
                cout << "\t\t9. Dem so luong hoa don co trong nam xac dinh \n";
                cout << "\t\t10. Tinh tong tien tat ca hoa don co trong nam nao do\n ";
                // cout << "\t\t11. Xuat hoa don tu ngay a den ngay b \n";
                // cout << "\t\t12. Them 1 hoa don sau 1 hoa don \n";
                // cout << "\t\t13. Them 1 hoa don vao dau \n";

                cout << "\n\t\t================================================================================\n";
                cout << "Nhap lua chon :";
                cin >> luaChon;
                switch (luaChon)
                {
                case 1:
                    nhapHoaDon(lHoaDon);
                    break;
                case 2:
                    xuatHoaDon(lHoaDon);
                    break;
                case 3:
                    cout << "Nhap ma hoa don can sua : ";
                    cin >> maHoaDon;
                    suaHoaDonTheoMa(lHoaDon, maHoaDon);
                    break;
                case 4:
                    luuHoaDon(lHoaDon);
                    break;
                case 5:
                    docHoaDon(lHoaDon);
                    break;
                case 6:
                    cout << "Nhap ma hoa don can tim : ";
                    cin >> maHoaDon;
                    p = timKiemHoaDonTheoMa(lHoaDon, maHoaDon);
                    if (p != NULL)
                    {
                        cout << "Tim thay hoa don co ma " << maHoaDon << " co tong tien la : " << p->data.TongTien;
                    }
                    else
                    {
                        cout << "Ko tim thay hoa don co ma " << maHoaDon;
                    }
                    break;
                case 7:
                    // xoaHoaDonDau(lHoaDon);
                    xoaHoaDonCuoi(lHoaDon);
                    // cout << "Nhap ma hoa don can xoa : ";
                    // cin >> maHoaDon;
                    // xoaHoaDonTheoMa(lHoaDon, maHoaDon);
                    break;
                case 8:
                    sapXepHoaDonTheoSoLuongHang(lHoaDon);
                    break;
                case 9:
                    demHoaDonTrongNam(lHoaDon);
                    break;
                case 10:
                    tongTienHoaDonTrongNam(lHoaDon);
                    break;
                case 11:
                    xuatHoaDonTuNgayADenNgayB(lHoaDon);
                    break;
                case 12:
                    themHoaDon_Q_Sau_P(lHoaDon);
                    break;
                case 13:
                {
                    HoaDon hd;
                    nhapRiengHoaDon(hd);
                    p = taoNodeHoaDon(hd);
                    themDauHoaDon(lHoaDon, p);
                    xuatHoaDon(lHoaDon);
                    break;
                }
                case 0:
                    cout << "Ban da thoat khoi chuong trinh !";
                    break;
                }
            } while (luaChonDoiTuong != 0);
        }
        case 0:
            cout << "\n Ban da thoat khoi chuong trinh ! ";
            break;
        }
    } while (luaChonDoiTuong != 0);
}

int main()
{
    ListHangHoa lHangHoa;
    taoListHangHoa(lHangHoa);

    ListHoaDon lHoaDon;
    taoListHoaDon(lHoaDon);

    menu(lHangHoa, lHoaDon);

    return 0;
}
