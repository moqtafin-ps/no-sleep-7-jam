///////////////////////////////////////////////////////////
//  Admin.cpp
//  Implementation of the Class Admin
//  Created on:      07-Dec-2025 2:23:02 AM
//  Original author: RAFIQ
///////////////////////////////////////////////////////////

#include "admin_.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <ctime>
using namespace std;

// Helper function for delay
static void delayMs(int ms)
{
    clock_t start = clock();
    while (clock() < start + ms * (CLOCKS_PER_SEC / 1000))
    {
    }
}

static void loadingDots(int durasiMs = 500)
{
    for (int i = 0; i < 3; i++)
    {
        cout << ".";
        cout.flush();
        delayMs(durasiMs);
    }
    cout << "\n";
}

Admin::~Admin()
{
}

Admin::Admin()
{
    idAdmin = 0;
    username = "";
    password = "";
    m_Sepatu = nullptr;
    m_Penyewaan = nullptr;
}

Admin::Admin(int id, string u, string p)
{
    idAdmin = id;
    username = u;
    password = p;
    m_Sepatu = nullptr;
    m_Penyewaan = nullptr;
}

void Admin::kelolaPenyewaan(vector<Penyewaan> &penyewaans, vector<Sepatu> &sepatus)
{

    if (penyewaans.empty())
    {
        cout << "Belum ada data penyewaan.\n";
        return;
    }
    cout << "\n============ Data Penyewaan ============\n";

    for (const auto &p : penyewaans)
    {
        cout << left << setw(16) << "ID Sewa" << ": " << p.getIdSewa() << "\n";
        cout << left << setw(16) << "Penyewa" << ": " << p.getPenyewa().getNama() << "\n";
        cout << left << setw(16) << "Sepatu" << ": " << p.getSepatu().getNamaSepatu() << "\n";
        cout << left << setw(16) << "Tanggal Sewa" << ": " << p.getTanggalSewa() << "\n";
        cout << left << setw(16) << "Lama Sewa" << ": " << p.getLamaSewa() << " hari\n";
        cout << left << setw(16) << "Status" << ": " << p.getStatusSewa() << "\n";
        cout << left << setw(16) << "Total Harga" << ": Rp. " << p.getTotalHarga() << "\n";
        cout << "----------------------------------------\n";
    }

    cout << "Apakah anda ingin memperbarui status penyewaan? (y/n): ";
    char x;
    cin >> x;

    if (x != 'y')
    {
        cout << "Kembali ke menu Admin";
        loadingDots();
        return;
    }

    int id;
    cout << "Masukkan ID Sewa yang ingin diperbarui: ";
    cin >> id;

    Penyewaan *ps = Penyewaan::cariPenyewaan(penyewaans, id);

    if (!ps)
    {
        cout << "Data penyewaan tidak ditemukan!\n";
        return;
    }

    ps->updateStatus("Dikembalikan");

    // Kembalikan stok sepatu
    int idSepatu = ps->getSepatu().getIdSepatu();
    Sepatu *sp = Sepatu::cariSepatu(sepatus, idSepatu);

    if (sp)
        sp->setStok(sp->getStok() + 1);

    cout << "Data sedang diproses";
    loadingDots();
    cout << "Status diperbarui & stok sepatu dikembalikan!\n";

    for (auto it = penyewaans.begin(); it != penyewaans.end(); ++it)
    {
        if (it->getIdSewa() == id)
        {
            penyewaans.erase(it);
            cout << "Data penyewaan telah dihapus dari daftar aktif.\n";
            break;
        }
    }
}

void Admin::kelolaSepatu(vector<Sepatu> &sepatus)
{
    char menuK;
    do
    {
        cout << "\n=== Menu Pengelolaan Sepatu Enfo ===\n";
        cout << "1. Tambah Sepatu\n";
        cout << "2. Edit Data Sepatu\n";
        cout << "3. Hapus Sepatu\n";
        cout << "4. Kembali\n";
        cout << "Pilihan: ";
        cin >> menuK;

        switch (menuK)
        {
        case '1':
            Sepatu::tambahSepatu(sepatus);
            break;
        case '2':
            Sepatu::editSepatu(sepatus);
            break;
        case '3':
            Sepatu::hapusSepatu(sepatus);
            break;
        case '4':
            cout << "Kembali ke menu Admin";
            loadingDots();
            break;
        default:
            cout << "Pilihan tidak valid!\n";
            break;
        }
    } while (menuK != '4');
}

int Admin::getIdAdmin() const
{
    return idAdmin;
}

string Admin::getPassword() const
{
    return password;
}

string Admin::getUsername() const
{
    return username;
}

void Admin::loadAdmin(const string &file, vector<Admin> &admins)
{
    ifstream f(file);
    if (!f.is_open())
        return;

    string line;
    while (getline(f, line))
    {
        if (line.empty())
            continue;
        stringstream ss(line);

        int id;
        string username, password;

        ss >> id;
        ss.ignore();
        getline(ss, username, ',');
        getline(ss, password, ',');

        admins.emplace_back(id, username, password);
    }
}

void Admin::saveAdmin(const string &file, const vector<Admin> &admins)
{
    ofstream f(file);
    if (!f.is_open())
        return;

    for (const auto &p : admins)
    {
        f << p.getIdAdmin() << ","
          << p.getUsername() << ","
          << p.getPassword() << "\n";
    }
}

void Admin::defaultAdmin(vector<Admin> &data)
{
    loadAdmin("admin.txt", data);
    if (data.empty())
    {
        Admin defaultAdmin(1, "admin", "admin123");
        data.push_back(defaultAdmin);
        cout << "\nDefault admin created (username: admin, password: admin123)\n";
    }
}

Admin *Admin::login(vector<Admin> &admins)
{
    string username, password;

    cout << "\n=== Login Admin ===\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    for (auto &a : admins)
    {
        if (a.getUsername() == username && a.getPassword() == password)
        {
            cout << "Login berhasil. Selamat datang Admin " << a.getUsername() << "!\n";
            return &a;
        }
    }

    cout << "Username atau password salah!\n";
    return nullptr;
}