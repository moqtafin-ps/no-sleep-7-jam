///////////////////////////////////////////////////////////
//  Penyewaan.h
//  Implementation of the Class Penyewaan
//  Created on:      07-Dec-2025 2:23:06 AM
//  Original author: RAFIQ
///////////////////////////////////////////////////////////

#ifndef EA_F614829F_5EE2_435d_9BE7_B96D902AABA5__INCLUDED_
#define EA_F614829F_5EE2_435d_9BE7_B96D902AABA5__INCLUDED_

#include <string>
#include <vector>
#include "sepatu_.h"
#include "penyewa_.h"
using namespace std;

class Penyewaan
{
public:
    virtual ~Penyewaan();

    // Constructor
    Penyewaan();
    Penyewaan(int id, Penyewa p, Sepatu s, string tSewa, int lSewa, double total);

    // Getter
    int getIdSewa() const;
    string getStatusSewa() const;
    double getTotalHarga() const;
    string getTanggalSewa() const;
    int getLamaSewa() const;
    Penyewa getPenyewa() const;
    Sepatu getSepatu() const;

    // Method utama
    void updateStatus(string status);

    // Static methods untuk pengelolaan penyewaan
    static Penyewaan *cariPenyewaan(vector<Penyewaan> &data, int idSewa);
    static void savePenyewaan(const string &file, const vector<Penyewaan> &penyewaans);
    static void loadPenyewaan(const string &file, vector<Penyewaan> &penyewaans,
                              vector<Penyewa> &penyewas, vector<Sepatu> &sepatus);
    static void sewaSepatu(Penyewa *currentPenyewa, vector<Sepatu> &sepatus,
                           vector<Penyewaan> &penyewaans);
    static void cekStatusPenyewaan(Penyewa *currentPenyewa,
                                   const vector<Penyewaan> &penyewaans);

private:
    int idSewa;
    string statusSewa; //"Dipinjam" atau "Dikembalikan"
    int lamaSewa;
    string tanggalSewa;
    double totalHarga;

    Penyewa penyewa;
    Sepatu sepatu;
    Sepatu *m_Sepatu; // Asosiasi: penyewaan melibatkan sepatu
};

#endif // !defined(EA_F614829F_5EE2_435d_9BE7_B96D902AABA5__INCLUDED_)