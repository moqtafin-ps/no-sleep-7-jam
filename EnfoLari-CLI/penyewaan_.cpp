///////////////////////////////////////////////////////////
//  Penyewaan.cpp
//  Implementation of the Class Penyewaan
//  Created on:      07-Dec-2025 2:23:06 AM
//  Original author: RAFIQ
///////////////////////////////////////////////////////////

#include "penyewaan_.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
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

Penyewaan::~Penyewaan()
{
}

Penyewaan::Penyewaan()
{
    idSewa = 0;
    statusSewa = "";
    lamaSewa = 0;
    tanggalSewa = "";
    totalHarga = 0.0;
    m_Sepatu = nullptr;
}

Penyewaan::Penyewaan(int id, Penyewa p, Sepatu s, string tSewa, int lSewa, double total)
{
    idSewa = id;
    penyewa = p;
    sepatu = s;
    tanggalSewa = tSewa;
    lamaSewa = lSewa;
    totalHarga = total;
    statusSewa = "";
    m_Sepatu = nullptr;
}

void Penyewaan::updateStatus(string status) // "Dipinjam" atau "Dikembalikan"
{
    statusSewa = status;
}

int Penyewaan::getIdSewa() const
{
    return idSewa;
}

string Penyewaan::getStatusSewa() const
{
    return statusSewa;
}

double Penyewaan::getTotalHarga() const
{
    return totalHarga;
}

string Penyewaan::getTanggalSewa() const
{
    return tanggalSewa;
}

int Penyewaan::getLamaSewa() const
{
    return lamaSewa;
}

Penyewa Penyewaan::getPenyewa() const
{
    return penyewa;
}

Sepatu Penyewaan::getSepatu() const
{
    return sepatu;
}

void Penyewaan::savePenyewaan(const string &file, const vector<Penyewaan> &penyewaans)
{
    ofstream f(file);
    if (!f.is_open())
        return;

    for (const auto &p : penyewaans)
    {
        f << p.getIdSewa() << ","
          << p.getPenyewa().getIdUser() << ","
          << p.getSepatu().getIdSepatu() << ","
          << p.getTanggalSewa() << ","
          << p.getLamaSewa() << ","
          << p.getStatusSewa() << ","
          << p.getTotalHarga()
          << "\n";
    }
    f.close();
}

void Penyewaan::loadPenyewaan(const string &file, vector<Penyewaan> &penyewaans,
                              vector<Penyewa> &penyewas, vector<Sepatu> &sepatus)
{
    ifstream f(file);
    if (!f.is_open())
        return;

    penyewaans.clear();

    string line;
    while (getline(f, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);
        string temp;

        int idSewa, idPenyewa, idSepatu, lSewa;
        string tSewa, status;
        double total;

        getline(ss, temp, ',');
        idSewa = stoi(temp);
        getline(ss, temp, ',');
        idPenyewa = stoi(temp);
        getline(ss, temp, ',');
        idSepatu = stoi(temp);
        getline(ss, tSewa, ',');
        getline(ss, temp, ',');
        lSewa = stoi(temp);
        getline(ss, status, ',');
        getline(ss, temp, ',');
        total = stod(temp);

        Penyewa *p = Penyewa::cariPenyewa(penyewas, idPenyewa);
        Sepatu *s = Sepatu::cariSepatu(sepatus, idSepatu);

        if (p && s)
        {
            Penyewaan py(idSewa, *p, *s, tSewa, lSewa, total);
            py.updateStatus(status);
            penyewaans.push_back(py);
        }
    }

    f.close();
}

Penyewaan *Penyewaan::cariPenyewaan(vector<Penyewaan> &data, int idSewa)
{
    for (auto &ps : data)
        if (ps.getIdSewa() == idSewa)
            return &ps;
    return nullptr;
}

void Penyewaan::sewaSepatu(Penyewa *currentPenyewa, vector<Sepatu> &sepatus,
                           vector<Penyewaan> &penyewaans)
{
    // 1. Tampilkan sepatu
    Sepatu::tampilkanDaftar(sepatus);
    if (sepatus.empty())
    {
        cout << "Kembali ke menu sebelumnya...\n";
        return;
    }

    // 2. Pilih ID sepatu yang ingin disewa
    int idSepatu;
    cout << "Pilih ID Sepatu: ";
    cin >> idSepatu;

    // Sepatu yang dipilih
    Sepatu *dipilih = Sepatu::cariSepatu(sepatus, idSepatu);

    if (!dipilih)
    {
        cout << "ID tidak ditemukan!\n";
        return;
    }

    if (dipilih->getStok() <= 0)
    {
        cout << "Stok sepatu habis!\n";
        return;
    }

    // 3. Tanggal sewa dan lama sewa
    string tSewa;
    int lSewa;
    cout << "Tanggal sewa: ";
    cin.ignore();
    getline(cin, tSewa);
    cout << "Lama penyewaan (hari): ";
    cin >> lSewa;

    // 4. Hitung total harga
    double total = dipilih->getHargaSewa() * lSewa;

    // 5. Proses pembayaran
    cout << "Total harga pesanan anda adalah Rp." << dipilih->getHargaSewa()
         << " x " << lSewa << " = Rp." << total;
    delayMs(500);
    cout << "\nSelesaikan pembayaran untuk menyewa sepatu!";

    // 6. Buat penyewaan
    int idSewa = penyewaans.size() + 1;
    Penyewaan p(idSewa, *currentPenyewa, *dipilih, tSewa, lSewa, total);
    p.updateStatus("Dipinjam");

    char x;
    do
    {
        cout << "\n\nApakah anda sudah menyelesaikan pembayaran? (y/n): ";
        cin >> x;

        if (x == 'y')
        {
            cout << "Data anda sedang diproses";
            loadingDots();
            cout << "Sewa berhasil! Total dibayar: Rp. " << total << "\n";
        }
        else
        {
            cout << "\nSEGERA LAKUKAN PEMBAYARAN!!!";
        }
    } while (x != 'y');

    // 7. Tambahkan ke daftar penyewaan
    penyewaans.push_back(p);

    // 8. Kurangi stok sepatu
    dipilih->setStok(dipilih->getStok() - 1);
}

void Penyewaan::cekStatusPenyewaan(Penyewa *currentPenyewa,
                                   const vector<Penyewaan> &penyewaans)
{
    cout << "====== Cek Status Penyewaan ======\n";

    bool ada = false;

    for (const auto &p : penyewaans)
    {
        if (p.getPenyewa().getIdUser() == currentPenyewa->getIdUser())
        {
            ada = true;

            cout << left << setw(16) << "\nID Sewa" << ": " << p.getIdSewa();
            cout << left << setw(16) << "\nStatus" << ": " << p.getStatusSewa();
            cout << left << setw(16) << "\nTanggal Sewa" << ": " << p.getTanggalSewa();
            cout << left << setw(16) << "\nLama Sewa" << ": " << p.getLamaSewa() << " hari";
            cout << left << setw(16) << "\nTotal Harga" << ": Rp. " << p.getTotalHarga();

            cout << left << setw(16) << "\n------------- Sepatu -------------";
            cout << left << setw(16) << "\nNama" << ": " << p.getSepatu().getNamaSepatu();
            cout << left << setw(16) << "\nUkuran" << ": " << p.getSepatu().getUkuran();
            cout << left << setw(16) << "\nHarga Sewa" << ": Rp. " << p.getSepatu().getHargaSewa();
            cout << "\n----------------------------------\n";
        }
    }

    if (!ada)
    {
        cout << "Anda belum memiliki penyewaan.\n";
    }
}