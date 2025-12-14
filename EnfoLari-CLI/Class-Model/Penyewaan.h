///////////////////////////////////////////////////////////
//  Penyewaan.h
//  Implementation of the Class Penyewaan
//  Created on:      14-Dec-2025 4:46:05 AM
//  Original author: RAFIQ
///////////////////////////////////////////////////////////

#if !defined(EA_30F2BCC2_DD04_4be6_BAF0_D3BDC98C678D__INCLUDED_)
#define EA_30F2BCC2_DD04_4be6_BAF0_D3BDC98C678D__INCLUDED_

#include "Penyewa.h"
#include "Sepatu.h"

class Penyewaan
{

public:
	Penyewaan();
	Penyewaan(int id, Penyewa p, Sepatu s, string tSewa, int lSewa, double total);
	virtual ~Penyewaan();
	static Penyewaan * cariPenyewaan(vector<Penyewaan>& data, int idSewa);
	void cekStatusPenyewaan(const vector<Penyewaan> & penyewaans, Penyewa * currentPenyewa);
	const int getIdSewa();
	const int getLamaSewa();
	const Penyewa getPenyewa();
	const Sepatu getSepatu();
	const string getStatusSewa();
	const string getTanggalSewa();
	const double getTotalHarga();
	static void loadPenyewaan(const string& file, vector<Penyewaan>& penyewaans);
	static void savePenyewaan(const string& file, const vector<Penyewaan>& penyewaans);
	void sewaSepatu(vector<Penyewaan> & penyewaans, vector<Sepatu> & sepatus, Penyewa * currentPenyewa);
	void updateStatus(string status);

private:
	int idSewa;
	int lamaSewa;
	Sepatu* m_Sepatu;
	Penyewa penyewa;
	Sepatu sepatu;
	/**
	 * "Dipinjam" atau "Dikemabalikan"
	 */
	string statusSewa;
	string tanggalSewa;
	double totalHarga;

};
#endif // !defined(EA_30F2BCC2_DD04_4be6_BAF0_D3BDC98C678D__INCLUDED_)
