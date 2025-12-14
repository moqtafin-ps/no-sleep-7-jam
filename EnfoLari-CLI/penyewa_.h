///////////////////////////////////////////////////////////
//  Penyewa.h
//  Implementation of the Class Penyewa
//  Created on:      07-Dec-2025 2:23:05 AM
//  Original author: RAFIQ
///////////////////////////////////////////////////////////

#ifndef EA_1756EBEA_58BC_4482_8D25_15784BB0AABB__INCLUDED_
#define EA_1756EBEA_58BC_4482_8D25_15784BB0AABB__INCLUDED_

#include <string>
#include <vector>
using namespace std;

class Penyewaan;
class Sepatu;

class Penyewa
{
public:
    virtual ~Penyewa();

    // Constructor
    Penyewa();
    Penyewa(int id, string n, string k, string u, string p);

    // Getter
    int getIdUser() const;
    string getKontak() const;
    string getNama() const;
    string getPassword() const;
    string getUsername() const;

    // Setter
    void setKontak(string k);
    void setNama(string n);
    void setPassword(string p);
    void setUsername(string u);

    // Static methods untuk pengelolaan penyewa
    static Penyewa *cariPenyewa(vector<Penyewa> &data, int idUser);
    static void loadPenyewa(const string &file, vector<Penyewa> &penyewas);
    static void savePenyewa(const string &file, const vector<Penyewa> &penyewas);
    static void registrasi(vector<Penyewa> &penyewas);
    static Penyewa *login(vector<Penyewa> &penyewas);

private:
    int idUser;
    string kontak;
    string nama;
    Penyewaan *m_Penyewaan; // Asosiasi: penyewa melakukan penyewaan
    string password;
    string username;
};

#endif // !defined(EA_1756EBEA_58BC_4482_8D25_15784BB0AABB__INCLUDED_)