///////////////////////////////////////////////////////////
//  Penyewa.h
//  Implementation of the Class Penyewa
//  Created on:      14-Dec-2025 4:46:05 AM
//  Original author: RAFIQ
///////////////////////////////////////////////////////////

#if !defined(EA_4C89D9EE_516F_47b0_98D1_C777DFAF1DDD__INCLUDED_)
#define EA_4C89D9EE_516F_47b0_98D1_C777DFAF1DDD__INCLUDED_

#include "Penyewaan.h"

class Penyewa
{

public:
	Penyewaan *m_Penyewaan;

	Penyewa();
	Penyewa(int id, string n, string k, string u, string p);
	Penyewa(int id, string n, string k);
	virtual ~Penyewa();
	static Penyewa *cariPenyewa(vector<Penyewa> &data, int idUser);
	const int getIdUser();
	const string getKontak();
	const string getNama();
	const string getPassword();
	const string getUsername();
	static void loadPenyewa(const string &file, vector<Penyewa> &penyewas);
	static Penyewa *login(vector<Penyewa> &penyewas);
	static void registrasi(vector<Penyewa> &penyewas);
	static void savePenyewa(const string &file, const vector<Penyewa> &penyewas);
	void setKontak(string k);
	void setNama(string n);
	void setPassword(string p);
	void setUsername(string u);

private:
	int idUser;
	string kontak;
	string nama;
	string password;
	string username;
};
#endif // !defined(EA_4C89D9EE_516F_47b0_98D1_C777DFAF1DDD__INCLUDED_)
