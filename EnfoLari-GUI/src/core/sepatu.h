#ifndef SEPATU_H
#define SEPATU_H

#include <QString>
#include <QVector>

class Sepatu
{
public:
    Sepatu();
    Sepatu(int id, const QString &nama, double harga, int ukuran, int stok);
    ~Sepatu();

    // Getters
    int getIdSepatu() const;
    QString getNamaSepatu() const;
    double getHargaSewa() const;
    int getUkuran() const;
    int getStok() const;

    // Setters
    void setNamaSepatu(const QString &nama);
    void setHargaSewa(double harga);
    void setUkuran(int ukuran);
    void setStok(int stok);

    // Static methods
    static void loadSepatu(const QString &filePath, QVector<Sepatu> &sepatus);
    static void saveSepatu(const QString &filePath, const QVector<Sepatu> &sepatus);
    static Sepatu* cariSepatu(QVector<Sepatu> &sepatus, int idSepatu);

private:
    int idSepatu;
    QString namaSepatu;
    double hargaSewa;
    int ukuran;
    int stok;
};

#endif // SEPATU_H
