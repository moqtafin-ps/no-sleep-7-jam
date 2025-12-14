///////////////////////////////////////////////////////////
//  Admin.h
//  Implementation of the Class Admin
//  Created on:      14-Dec-2025 4:46:05 AM
//  Original author: RAFIQ
///////////////////////////////////////////////////////////

#if !defined(EA_A968F80C_EF78_4596_9C34_AE314E19EFE9__INCLUDED_)
#define EA_A968F80C_EF78_4596_9C34_AE314E19EFE9__INCLUDED_

#include "Sepatu.h"
#include "Penyewaan.h"

class Admin
{

public:
	Sepatu *m_Sepatu;
	Penyewaan *m_Penyewaan;

	Admin();
	Admin(int id, string u, string p);
	virtual ~Admin();
	static void defaultAdmin(vector<Admin>& data);
	const int getIdAdmin();
	const string getPassword();
	const string getUsername();
	void kelolaPenyewaan(vector<Sepatu>& sepatus, vector<Penyewaan>& penyewaans);
	void kelolaSepatu(vector<Sepatu>& sepatus);
	static void loadAdmin(vector<Admin>& admins, const string& file);
	static Admin * login(vector<Admin>& admins);
	static void saveAdmin(const vector<Admin>& admins, const string& file);

private:
	int idAdmin;
	string password;
	string username;

};
#endif // !defined(EA_A968F80C_EF78_4596_9C34_AE314E19EFE9__INCLUDED_)
