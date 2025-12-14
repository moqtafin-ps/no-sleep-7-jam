///////////////////////////////////////////////////////////
//  Sepatu.cpp
//  Implementation of the Class Sepatu
//  Created on:      07-Dec-2025 2:23:08 AM
//  Original author: RAFIQ
///////////////////////////////////////////////////////////

#include "sepatu_.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
using namespace std;

Sepatu::~Sepatu()
{
}

Sepatu::Sepatu()
{
    idSepatu = 0;
    namaSepatu = "";
    hargaSewa = 0.0;
    ukuran = 0;
    stok = 0;
}

Sepatu::Sepatu(int id, string nama, double harga, int uk, int st)
{
    idSepatu = id;
    namaSepatu = nama;
    ukuran = uk;
    hargaSewa = harga;
    stok = st;
}

void Sepatu::editSepatu(vector<Sepatu> &data)
{
    tampilkanDaftar(data);

    int id;
    cout << "\nMasukkan ID Sepatu yang ingin diedit: ";
    cin >> id;

    Sepatu *s = cariSepatu(data, id);
    if (s == nullptr)
    {
        cout << "ID tidak ditemukan!\n";
        return;
    }

    cout << "\nEdit Data Sepatu ID: " << s->idSepatu << "\n";

    string namaBaru;
    int ukuranBaru, stokBaru;
    double hargaBaru;

    cout << "Ketikkan '-1' jika tidak ingin mengganti.\nNama baru: ";
    cin.ignore();
    getline(cin, namaBaru);
    if (namaBaru != "-1")
    {
        s->setNamaSepatu(namaBaru);
    }

    cout << "Harga sewa baru: ";
    cin >> hargaBaru;
    if (hargaBaru != -1)
    {
        s->setHargaSewa(hargaBaru);
    }

    cout << "Ukuran baru: ";
    cin >> ukuranBaru;
    if (ukuranBaru != -1)
    {
        s->setUkuran(ukuranBaru);
    }

    cout << "Stok baru: ";
    cin >> stokBaru;
    if (stokBaru != -1)
    {
        s->setStok(stokBaru);
    }

    cout << "Sepatu berhasil diedit!\n";
}

double Sepatu::getHargaSewa() const
{
    return hargaSewa;
}

int Sepatu::getIdSepatu() const
{
    return idSepatu;
}

string Sepatu::getNamaSepatu() const
{
    return namaSepatu;
}

int Sepatu::getStok() const
{
    return stok;
}

int Sepatu::getUkuran() const
{
    return ukuran;
}

void Sepatu::setHargaSewa(double harga)
{
    hargaSewa = harga;
}

void Sepatu::setNamaSepatu(string nama)
{
    namaSepatu = nama;
}

void Sepatu::setStok(int st)
{
    stok = st;
}

void Sepatu::setUkuran(int uk)
{
    ukuran = uk;
}

void Sepatu::loadSepatu(const string &file, vector<Sepatu> &sepatus)
{
    sepatus.clear();
    ifstream f(file);
    if (!f.is_open())
        return;

    string line;
    while (getline(f, line))
    {
        if (line.empty())
            continue;
        stringstream ss(line);

        int id, harga, stok, ukuran;
        string nama;

        ss >> id;
        ss.ignore();
        getline(ss, nama, ',');
        ss >> harga;
        ss.ignore();
        ss >> ukuran;
        ss.ignore();
        ss >> stok;

        sepatus.emplace_back(id, nama, harga, ukuran, stok);
    }
}

void Sepatu::saveSepatu(const string &file, const vector<Sepatu> &sepatus)
{
    ofstream f(file);
    if (!f.is_open())
        return;

    for (const auto &s : sepatus)
    {
        f << s.getIdSepatu() << ","
          << s.getNamaSepatu() << ","
          << s.getHargaSewa() << ","
          << s.getUkuran() << ","
          << s.getStok() << "\n";
    }
}

Sepatu *Sepatu::cariSepatu(vector<Sepatu> &data, int idSepatu)
{
    for (auto &s : data)
        if (s.getIdSepatu() == idSepatu)
            return &s;
    return nullptr;
}

void Sepatu::tampilkanDaftar(const vector<Sepatu> &sepatus)
{
    if (sepatus.empty())
    {
        cout << "Belum ada data sepatu.\n";
        return;
    }

    cout << "\n==================== Daftar Sepatu ====================\n";
    cout << "ID |         Nama         | Harga/Hari | Ukuran | Stok\n";
    cout << "-------------------------------------------------------\n";
    for (const auto &s : sepatus)
    {
        cout << left << setw(2) << s.getIdSepatu()
             << " | " << setw(20) << s.getNamaSepatu()
             << " | " << setw(10) << s.getHargaSewa()
             << " | " << setw(6) << s.getUkuran()
             << " | " << left << s.getStok()
             << "\n";
    }
    cout << "-------------------------------------------------------\n";
}

void Sepatu::tambahSepatu(vector<Sepatu> &data)
{
    int id;
    cout << "\nMasukkan ID Sepatu Baru: ";
    cin >> id;

    // Cek apakah ID sudah ada
    if (cariSepatu(data, id) != nullptr)
    {
        cout << "ID sudah digunakan!\n";
        return;
    }

    string nama;
    double harga;
    int ukuran, stok;

    cout << "Nama sepatu: ";
    cin.ignore();
    getline(cin, nama);

    cout << "Masukkan Harga Sewa: ";
    cin >> harga;

    cout << "Masukkan Ukuran Sepatu: ";
    cin >> ukuran;

    cout << "Masukkan Stok: ";
    cin >> stok;

    Sepatu s(id, nama, harga, ukuran, stok);
    data.push_back(s);
    cout << "Sepatu berhasil ditambahkan!\n";
}

void Sepatu::hapusSepatu(vector<Sepatu> &data)
{
    tampilkanDaftar(data);
    if (!data.empty())
    {
        int id;
        cout << "Masukkan 0 untuk kembali.\nMasukkan ID Sepatu yang ingin dihapus: ";
        cin >> id;

        if (id == 0)
        {
            cout << "Kembali ke menu sebelumnya...\n";
            return;
        }

        for (auto it = data.begin(); it != data.end(); ++it)
        {
            if (it->getIdSepatu() == id)
            {
                data.erase(it);
                cout << "Sepatu berhasil dihapus!\n";
                return;
            }
        }

        cout << "ID tidak ditemukan!\n";
    }
    else
        return;
}