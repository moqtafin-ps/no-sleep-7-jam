#ifndef PENYEWAAN_H
#define PENYEWAAN_H

#include "penyewa.h"
#include "sepatu.h"
#include <QString>
#include <QVector>

class Penyewaan
{
public:
    Penyewaan();
    Penyewaan(int id, const Penyewa &penyewa, const Sepatu &sepatu, 
              const QString &tanggalSewa, int lamaSewa, double totalHarga);
    ~Penyewaan();

    // Getters
    int getIdSewa() const;
    QString getStatusSewa() const;
    QString getTanggalSewa() const;
    int getLamaSewa() const;
    double getTotalHarga() const;
    Penyewa getPenyewa() const;
    Sepatu getSepatu() const;

    // Setters
    void updateStatus(const QString &status);

    // Static methods
    static void loadPenyewaan(const QString &filePath, QVector<Penyewaan> &penyewaans,
                             QVector<Penyewa> &penyewas, QVector<Sepatu> &sepatus);
    static void savePenyewaan(const QString &filePath, const QVector<Penyewaan> &penyewaans);
    static Penyewaan* cariPenyewaan(QVector<Penyewaan> &penyewaans, int idSewa);

private:
    int idSewa;
    QString statusSewa;
    QString tanggalSewa;
    int lamaSewa;
    double totalHarga;
    Penyewa penyewa;
    Sepatu sepatu;
};

#endif // PENYEWAAN_H
