#include "sepatu.h"
#include <QFile>
#include <QTextStream>

Sepatu::Sepatu()
    : idSepatu(0), namaSepatu(""), hargaSewa(0.0), ukuran(0), stok(0)
{
}

Sepatu::Sepatu(int id, const QString &nama, double harga, int uk, int st)
    : idSepatu(id), namaSepatu(nama), hargaSewa(harga), ukuran(uk), stok(st)
{
}

Sepatu::~Sepatu()
{
}

int Sepatu::getIdSepatu() const
{
    return idSepatu;
}

QString Sepatu::getNamaSepatu() const
{
    return namaSepatu;
}

double Sepatu::getHargaSewa() const
{
    return hargaSewa;
}

int Sepatu::getUkuran() const
{
    return ukuran;
}

int Sepatu::getStok() const
{
    return stok;
}

void Sepatu::setNamaSepatu(const QString &nama)
{
    namaSepatu = nama;
}

void Sepatu::setHargaSewa(double harga)
{
    hargaSewa = harga;
}

void Sepatu::setUkuran(int uk)
{
    ukuran = uk;
}

void Sepatu::setStok(int st)
{
    stok = st;
}

void Sepatu::loadSepatu(const QString &filePath, QVector<Sepatu> &sepatus)
{
    sepatus.clear();
    QFile file(filePath);
    
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine().trimmed();
        if (line.isEmpty())
            continue;

        QStringList parts = line.split(',');
        if (parts.size() >= 5)
        {
            int id = parts[0].toInt();
            QString nama = parts[1];
            double harga = parts[2].toDouble();
            int ukuran = parts[3].toInt();
            int stok = parts[4].toInt();
            sepatus.append(Sepatu(id, nama, harga, ukuran, stok));
        }
    }
    file.close();
}

void Sepatu::saveSepatu(const QString &filePath, const QVector<Sepatu> &sepatus)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    for (const Sepatu &s : sepatus)
    {
        out << s.getIdSepatu() << ","
            << s.getNamaSepatu() << ","
            << s.getHargaSewa() << ","
            << s.getUkuran() << ","
            << s.getStok() << "\n";
    }
    file.close();
}

Sepatu* Sepatu::cariSepatu(QVector<Sepatu> &sepatus, int idSepatu)
{
    for (int i = 0; i < sepatus.size(); ++i)
    {
        if (sepatus[i].getIdSepatu() == idSepatu)
            return &sepatus[i];
    }
    return nullptr;
}
