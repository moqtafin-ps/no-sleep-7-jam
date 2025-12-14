

#include <ctime>
#include <iostream>
#include <string>
#include <vector>

#include "admin_.h"
#include "penyewa_.h"
#include "sepatu_.h"
#include "penyewaan_.h"

using namespace std;

// Global data vectors
vector<Admin> admins;
vector<Penyewa> penyewas;
vector<Sepatu> sepatus;
vector<Penyewaan> penyewaans;

// File paths
const string DATA_PENYEWA = "penyewa.txt";
const string DATA_SEPATU = "sepatu.txt";
const string DATA_PENYEWAAN = "penyewaan.txt";
const string DATA_ADMIN = "admin.txt";

// Helper functions
void delayMs(int ms)
{
    clock_t start = clock();
    while (clock() < start + ms * (CLOCKS_PER_SEC / 1000))
    {
    }
}

void loadingDots(int durasiMs = 500)
{
    for (int i = 0; i < 3; i++)
    {
        cout << ".";
        cout.flush();
        delayMs(durasiMs);
    }
    cout << "\n";
}

// Menu untuk admin setelah login
void menuAdmin()
{
    Admin *currentAdmin = Admin::login(admins);

    if (currentAdmin == nullptr)
    {
        return; // Login gagal, kembali ke main menu
    }

    char menuA;
    do
    {
        cout << "\n=== Menu Admin ===\n";
        cout << "1. Kelola Sepatu\n";
        cout << "2. Kelola Penyewaan\n";
        cout << "3. Logout\n";
        cout << "Pilihan: ";
        cin >> menuA;

        switch (menuA)
        {
        case '1':
            currentAdmin->kelolaSepatu(sepatus);
            Sepatu::saveSepatu(DATA_SEPATU, sepatus);
            break;
        case '2':
            currentAdmin->kelolaPenyewaan(penyewaans, sepatus);
            Penyewaan::savePenyewaan(DATA_PENYEWAAN, penyewaans);
            Sepatu::saveSepatu(DATA_SEPATU, sepatus);
            break;
        case '3':
            cout << "Loading";
            loadingDots();
            break;
        default:
            cout << "Pilihan tidak valid!\n";
            break;
        }

    } while (menuA != '3');
}

// Menu untuk penyewa setelah login
void menuPenyewa()
{
    Penyewa *currentPenyewa = Penyewa::login(penyewas);

    if (currentPenyewa == nullptr)
    {
        return; // Login gagal, kembali ke main menu
    }

    char menuP;
    do
    {
        cout << "\n=== Menu Penyewa ===\n";
        cout << "1. Daftar Sepatu\n";
        cout << "2. Sewa Sepatu\n";
        cout << "3. Cek Status Penyewaan\n";
        cout << "4. Logout\n";
        cout << "Pilihan: ";
        cin >> menuP;

        switch (menuP)
        {
        case '1':
            Sepatu::tampilkanDaftar(sepatus);
            break;

        case '2':
            Penyewaan::sewaSepatu(currentPenyewa, sepatus, penyewaans);
            Penyewaan::savePenyewaan(DATA_PENYEWAAN, penyewaans);
            Sepatu::saveSepatu(DATA_SEPATU, sepatus);
            break;

        case '3':
            Penyewaan::cekStatusPenyewaan(currentPenyewa, penyewaans);
            break;

        case '4':
            cout << "Loading";
            loadingDots();
            break;

        default:
            cout << "Pilihan tidak valid!\n";
            break;
        }

    } while (menuP != '4');
}

// Main program
int main()
{
    // Load semua data
    Admin::defaultAdmin(admins);
    Penyewa::loadPenyewa(DATA_PENYEWA, penyewas);
    Sepatu::loadSepatu(DATA_SEPATU, sepatus);
    Penyewaan::loadPenyewaan(DATA_PENYEWAAN, penyewaans, penyewas, sepatus);

    char mainChoice;
    do
    {
        cout << "\n=== Menu Utama Penyewaan Sepatu EnfoLari ===";
        cout << "\n1. Registrasi Penyewa";
        cout << "\n2. Login Penyewa";
        cout << "\n3. Login Admin";
        cout << "\n4. Simpan & Keluar";
        cout << "\nPilihan: ";
        cin >> mainChoice;

        switch (mainChoice)
        {
        case '1':
            Penyewa::registrasi(penyewas);
            Penyewa::savePenyewa(DATA_PENYEWA, penyewas);
            break;
        case '2':
            menuPenyewa();
            break;
        case '3':
            menuAdmin();
            break;
        case '4':
            cout << "Sedang menyimpan data";
            loadingDots();
            cout << "Data berhasil disimpan.\n";
            break;
        default:
            cout << "Pilihan tidak valid!\n";
            break;
        }
    } while (mainChoice != '4');

    // Save data sebelum keluar
    Penyewa::savePenyewa(DATA_PENYEWA, penyewas);
    Sepatu::saveSepatu(DATA_SEPATU, sepatus);
    Penyewaan::savePenyewaan(DATA_PENYEWAAN, penyewaans);
    Admin::saveAdmin(DATA_ADMIN, admins);

    cout << "Program selesai.\n";
    return 0;
}