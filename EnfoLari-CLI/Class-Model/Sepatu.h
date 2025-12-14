///////////////////////////////////////////////////////////
//  Sepatu.h
//  Implementation of the Class Sepatu
//  Created on:      14-Dec-2025 4:46:06 AM
//  Original author: RAFIQ
///////////////////////////////////////////////////////////

#if !defined(EA_BD149029_A7FA_4e75_A8ED_FD12B9E92479__INCLUDED_)
#define EA_BD149029_A7FA_4e75_A8ED_FD12B9E92479__INCLUDED_

class Sepatu
{

public:
	Sepatu();
	Sepatu(int id, string nama, double harga, int uk, int st);
	virtual ~Sepatu();
	static Sepatu * cariSepatu(vector<Sepatu>& data, int idSepatu);
	static void editSepatu(vector<Sepatu> & data);
	const double getHargaSewa();
	const int getIdSepatu();
	const string getNamaSepatu();
	const int getStok();
	const int getUkuran();
	static void hapusSepatu(vector<Sepatu> & data);
	static void loadSepatu(const string& file, vector<Sepatu>& sepatus);
	static void saveSepatu(const string& file, const vector<Sepatu>& sepatus);
	void setHargaSewa(double harga);
	void setNamaSepatu(string nama);
	void setStok(int st);
	void setUkuran(int uk);
	static void tambahSepatu(vector<Sepatu> & data);
	static void tampilkanDaftar(const vector<Sepatu>& sepatus);

private:
	double hargaSewa;
	int idSepatu;
	string namaSepatu;
	int stok;
	int ukuran;

};
#endif // !defined(EA_BD149029_A7FA_4e75_A8ED_FD12B9E92479__INCLUDED_)
