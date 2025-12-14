#include "penyewaan.h"
#include <QFile>
#include <QTextStream>

Penyewaan::Penyewaan()
    : idSewa(0), statusSewa(""), tanggalSewa(""), lamaSewa(0), totalHarga(0.0)
{
}

Penyewaan::Penyewaan(int id, const Penyewa &p, const Sepatu &s, 
                     const QString &tSewa, int lSewa, double total)
    : idSewa(id), statusSewa("Dipinjam"), tanggalSewa(tSewa), 
      lamaSewa(lSewa), totalHarga(total), penyewa(p), sepatu(s)
{
}

Penyewaan::~Penyewaan()
{
}

int Penyewaan::getIdSewa() const
{
    return idSewa;
}

QString Penyewaan::getStatusSewa() const
{
    return statusSewa;
}

QString Penyewaan::getTanggalSewa() const
{
    return tanggalSewa;
}

int Penyewaan::getLamaSewa() const
{
    return lamaSewa;
}

double Penyewaan::getTotalHarga() const
{
    return totalHarga;
}

Penyewa Penyewaan::getPenyewa() const
{
    return penyewa;
}

Sepatu Penyewaan::getSepatu() const
{
    return sepatu;
}

void Penyewaan::updateStatus(const QString &status)
{
    statusSewa = status;
}

void Penyewaan::loadPenyewaan(const QString &filePath, QVector<Penyewaan> &penyewaans,
                             QVector<Penyewa> &penyewas, QVector<Sepatu> &sepatus)
{
    penyewaans.clear();
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
        if (parts.size() >= 7)
        {
            int idSewa = parts[0].toInt();
            int idPenyewa = parts[1].toInt();
            int idSepatu = parts[2].toInt();
            QString tanggalSewa = parts[3];
            int lamaSewa = parts[4].toInt();
            QString status = parts[5];
            double totalHarga = parts[6].toDouble();

            Penyewa *p = Penyewa::cariPenyewa(penyewas, idPenyewa);
            Sepatu *s = Sepatu::cariSepatu(sepatus, idSepatu);

            if (p && s)
            {
                Penyewaan penyewaan(idSewa, *p, *s, tanggalSewa, lamaSewa, totalHarga);
                penyewaan.updateStatus(status);
                penyewaans.append(penyewaan);
            }
        }
    }
    file.close();
}

void Penyewaan::savePenyewaan(const QString &filePath, const QVector<Penyewaan> &penyewaans)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    for (const Penyewaan &p : penyewaans)
    {
        out << p.getIdSewa() << ","
            << p.getPenyewa().getIdUser() << ","
            << p.getSepatu().getIdSepatu() << ","
            << p.getTanggalSewa() << ","
            << p.getLamaSewa() << ","
            << p.getStatusSewa() << ","
            << p.getTotalHarga() << "\n";
    }
    file.close();
}

Penyewaan* Penyewaan::cariPenyewaan(QVector<Penyewaan> &penyewaans, int idSewa)
{
    for (int i = 0; i < penyewaans.size(); ++i)
    {
        if (penyewaans[i].getIdSewa() == idSewa)
            return &penyewaans[i];
    }
    return nullptr;
}
