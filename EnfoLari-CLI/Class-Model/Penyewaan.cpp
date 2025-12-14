///////////////////////////////////////////////////////////
//  Penyewaan.cpp
//  Implementation of the Class Penyewaan
//  Created on:      14-Dec-2025 4:46:06 AM
//  Original author: RAFIQ
///////////////////////////////////////////////////////////

#include "Penyewaan.h"




Penyewaan::Penyewaan(){

}


Penyewaan::Penyewaan(int id, Penyewa p, Sepatu s, string tSewa, int lSewa, double total){

}


Penyewaan::~Penyewaan(){

}


Penyewaan * Penyewaan::cariPenyewaan(vector<Penyewaan>& data, int idSewa){

	return  NULL;
}


void Penyewaan::cekStatusPenyewaan(const vector<Penyewaan> & penyewaans, Penyewa * currentPenyewa){

}


const int Penyewaan::getIdSewa(){

	return 0;
}


const int Penyewaan::getLamaSewa(){

	return 0;
}


const Penyewa Penyewaan::getPenyewa(){

	return  NULL;
}


const Sepatu Penyewaan::getSepatu(){

	return  NULL;
}


const string Penyewaan::getStatusSewa(){

	return  NULL;
}


const string Penyewaan::getTanggalSewa(){

	return  NULL;
}


const double Penyewaan::getTotalHarga(){

	return 0;
}


void Penyewaan::loadPenyewaan(const string& file, vector<Penyewaan>& penyewaans){

}


void Penyewaan::savePenyewaan(const string& file, const vector<Penyewaan>& penyewaans){

}


void Penyewaan::sewaSepatu(vector<Penyewaan> & penyewaans, vector<Sepatu> & sepatus, Penyewa * currentPenyewa){

}


void Penyewaan::updateStatus(string status){

}