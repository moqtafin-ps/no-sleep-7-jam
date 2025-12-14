///////////////////////////////////////////////////////////
//  Penyewa.cpp
//  Implementation of the Class Penyewa
//  Created on:      14-Dec-2025 4:46:05 AM
//  Original author: RAFIQ
///////////////////////////////////////////////////////////

#include "Penyewa.h"

Penyewa::Penyewa() {}

Penyewa::Penyewa(int id, string n, string k, string u, string p) {}

Penyewa::Penyewa(int id, string n, string k) {}

Penyewa::~Penyewa() {}

Penyewa *Penyewa::cariPenyewa(vector<Penyewa> &data, int idUser) { return NULL; }

const int Penyewa::getIdUser() { return 0; }

const string Penyewa::getKontak() { return NULL; }

const string Penyewa::getNama() { return NULL; }

const string Penyewa::getPassword() { return NULL }

const string Penyewa::getUsername() { return NULL; }

void Penyewa::loadPenyewa(const string &file, vector<Penyewa> &penyewas) {}

Penyewa *Penyewa::login(vector<Penyewa> &penyewas) { return NULL; }

void Penyewa::registrasi(vector<Penyewa> &penyewas) {}

void Penyewa::savePenyewa(const string &file, const vector<Penyewa> &penyewas) {}

void Penyewa::setKontak(string k) {}

void Penyewa::setNama(string n) {}

void Penyewa::setPassword(string p) {}

void Penyewa::setUsername(string u) {}