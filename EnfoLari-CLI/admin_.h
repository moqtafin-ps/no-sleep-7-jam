///////////////////////////////////////////////////////////
//  Admin.h
//  Implementation of the Class Admin
//  Created on:      07-Dec-2025 2:23:02 AM
//  Original author: RAFIQ
///////////////////////////////////////////////////////////

#ifndef EA_03727710_2153_4ff9_BB8A_19A0747A9B6B__INCLUDED_
#define EA_03727710_2153_4ff9_BB8A_19A0747A9B6B__INCLUDED_

#include "sepatu_.h"
#include "penyewaan_.h"
#include <string>
#include <vector>
using namespace std;

class Admin
{
public:
    virtual ~Admin();

    // Constructor
    Admin();
    Admin(int id, string u, string p);

    // Getter
    int getIdAdmin() const;
    string getPassword() const;
    string getUsername() const;

    // Fungsi utama
    void kelolaPenyewaan(vector<Penyewaan> &penyewaans, vector<Sepatu> &sepatus);
    void kelolaSepatu(vector<Sepatu> &sepatus);

    // Static methods untuk pengelolaan admin
    static void loadAdmin(const string &file, vector<Admin> &admins);
    static void saveAdmin(const string &file, const vector<Admin> &admins);
    static void defaultAdmin(vector<Admin> &data);
    static Admin *login(vector<Admin> &admins);

private:
    int idAdmin;
    string password;
    string username;
    Sepatu *m_Sepatu;       // Asosiasi: admin mengelola sepatu
    Penyewaan *m_Penyewaan; // Asosiasi: admin mengelola penyewaan
};

#endif // !defined(EA_03727710_2153_4ff9_BB8A_19A0747A9B6B__INCLUDED_)