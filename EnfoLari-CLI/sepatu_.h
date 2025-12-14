///////////////////////////////////////////////////////////
//  Sepatu.h
//  Implementation of the Class Sepatu
//  Created on:      07-Dec-2025 2:23:08 AM
//  Original author: RAFIQ
///////////////////////////////////////////////////////////

#ifndef EA_F64D53B3_8476_479b_8942_0BDA93A82420__INCLUDED_
#define EA_F64D53B3_8476_479b_8942_0BDA93A82420__INCLUDED_

#include <vector>
#include <string>
using namespace std;

class Sepatu
{
public:
    virtual ~Sepatu();

    // Constructor
    Sepatu();
    Sepatu(int id, string nama, double harga, int uk, int st);

    // Getter
    double getHargaSewa() const;
    int getIdSepatu() const;
    string getNamaSepatu() const;
    int getStok() const;
    int getUkuran() const;

    // Setter
    void setHargaSewa(double harga);
    void setNamaSepatu(string nama);
    void setStok(int st);
    void setUkuran(int uk);

    // Method utama

    // Static methods untuk pengelolaan sepatu
    static Sepatu *cariSepatu(vector<Sepatu> &data, int idSepatu);
    static void loadSepatu(const string &file, vector<Sepatu> &sepatus);
    static void saveSepatu(const string &file, const vector<Sepatu> &sepatus);
    static void tampilkanDaftar(const vector<Sepatu> &sepatus);
    static void tambahSepatu(vector<Sepatu> &data);
    static void editSepatu(vector<Sepatu> &data);
    static void hapusSepatu(vector<Sepatu> &data);

private:
    double hargaSewa;
    int idSepatu;
    string namaSepatu;
    int stok;
    int ukuran;
};

#endif // !defined(EA_F64D53B3_8476_479b_8942_0BDA93A82420__INCLUDED_)