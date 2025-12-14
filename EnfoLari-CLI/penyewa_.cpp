///////////////////////////////////////////////////////////
//  Penyewa.cpp
//  Implementation of the Class Penyewa
//  Created on:      07-Dec-2025 2:23:05 AM
//  Original author: RAFIQ
///////////////////////////////////////////////////////////

#include "penyewa_.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

Penyewa::~Penyewa()
{
}

Penyewa::Penyewa()
{
    idUser = 0;
    nama = "";
    kontak = "";
    username = "";
    password = "";
    m_Penyewaan = nullptr;
}

Penyewa::Penyewa(int id, string n, string k, string u, string p)
{
    idUser = id;
    nama = n;
    kontak = k;
    username = u;
    password = p;
    m_Penyewaan = nullptr;
}

int Penyewa::getIdUser() const
{
    return idUser;
}

string Penyewa::getKontak() const
{
    return kontak;
}

string Penyewa::getNama() const
{
    return nama;
}

void Penyewa::setKontak(string k)
{
    kontak = k;
}

void Penyewa::setNama(string n)
{
    nama = n;
}

string Penyewa::getPassword() const
{
    return password;
}

string Penyewa::getUsername() const
{
    return username;
}

void Penyewa::setPassword(string p)
{
    password = p;
}

void Penyewa::setUsername(string u)
{
    username = u;
}

void Penyewa::loadPenyewa(const string &file, vector<Penyewa> &penyewas)
{
    penyewas.clear();
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
        string nama, kontak, username, password;

        ss >> id;
        ss.ignore();
        getline(ss, nama, ',');
        getline(ss, kontak, ',');
        getline(ss, username, ',');
        getline(ss, password, ',');

        penyewas.emplace_back(id, nama, kontak, username, password);
    }
}

void Penyewa::savePenyewa(const string &file, const vector<Penyewa> &penyewas)
{
    ofstream f(file);
    if (!f.is_open())
        return;

    for (const auto &p : penyewas)
    {
        f << p.getIdUser() << ","
          << p.getNama() << ","
          << p.getKontak() << ","
          << p.getUsername() << ","
          << p.getPassword() << "\n";
    }
}

Penyewa *Penyewa::cariPenyewa(vector<Penyewa> &data, int idUser)
{
    for (auto &p : data)
        if (p.getIdUser() == idUser)
            return &p;
    return nullptr;
}

void Penyewa::registrasi(vector<Penyewa> &penyewas)
{
    int id = penyewas.size() + 1; // Auto generate ID
    string nama, kontak, username, password;

    cout << "\n\n=== Registrasi Penyewa ===\n";
    cout << "Nama: ";
    cin.ignore();
    getline(cin, nama);

    cout << "Kontak: ";
    getline(cin, kontak);

    cout << "Username: ";
    cin >> username;

    cout << "Password: ";
    cin >> password;

    Penyewa p(id, nama, kontak, username, password);
    penyewas.push_back(p);
    cout << "Registrasi berhasil! ID Anda: " << id << "\n";
}

Penyewa *Penyewa::login(vector<Penyewa> &penyewas)
{
    string username, password;

    cout << "\n=== Login Penyewa ===\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    for (auto &p : penyewas)
    {
        if (p.getUsername() == username && p.getPassword() == password)
        {
            cout << "Login berhasil. Selamat datang " << p.getNama() << "!\n";
            return &p;
        }
    }

    cout << "Username atau password salah!\n";
    return nullptr;
}