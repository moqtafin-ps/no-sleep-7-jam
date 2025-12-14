#include "penyewa.h"
#include <QFile>
#include <QTextStream>

Penyewa::Penyewa()
    : idUser(0), nama(""), kontak(""), username(""), password("")
{
}

Penyewa::Penyewa(int id, const QString &n, const QString &k, 
                 const QString &u, const QString &p)
    : idUser(id), nama(n), kontak(k), username(u), password(p)
{
}

Penyewa::~Penyewa()
{
}

int Penyewa::getIdUser() const
{
    return idUser;
}

QString Penyewa::getNama() const
{
    return nama;
}

QString Penyewa::getKontak() const
{
    return kontak;
}

QString Penyewa::getUsername() const
{
    return username;
}

QString Penyewa::getPassword() const
{
    return password;
}

void Penyewa::setNama(const QString &n)
{
    nama = n;
}

void Penyewa::setKontak(const QString &k)
{
    kontak = k;
}

void Penyewa::setUsername(const QString &u)
{
    username = u;
}

void Penyewa::setPassword(const QString &p)
{
    password = p;
}

void Penyewa::loadPenyewa(const QString &filePath, QVector<Penyewa> &penyewas)
{
    penyewas.clear();
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
            QString kontak = parts[2];
            QString username = parts[3];
            QString password = parts[4];
            penyewas.append(Penyewa(id, nama, kontak, username, password));
        }
    }
    file.close();
}

void Penyewa::savePenyewa(const QString &filePath, const QVector<Penyewa> &penyewas)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    for (const Penyewa &p : penyewas)
    {
        out << p.getIdUser() << ","
            << p.getNama() << ","
            << p.getKontak() << ","
            << p.getUsername() << ","
            << p.getPassword() << "\n";
    }
    file.close();
}

Penyewa* Penyewa::cariPenyewa(QVector<Penyewa> &penyewas, int idUser)
{
    for (int i = 0; i < penyewas.size(); ++i)
    {
        if (penyewas[i].getIdUser() == idUser)
            return &penyewas[i];
    }
    return nullptr;
}

Penyewa* Penyewa::authenticate(QVector<Penyewa> &penyewas, const QString &username, const QString &password)
{
    for (int i = 0; i < penyewas.size(); ++i)
    {
        if (penyewas[i].getUsername() == username && penyewas[i].getPassword() == password)
        {
            return &penyewas[i];
        }
    }
    return nullptr;
}

bool Penyewa::registrasi(QVector<Penyewa> &penyewas, const QString &nama, 
                        const QString &kontak, const QString &username, const QString &password)
{
    // Check if username already exists
    for (const Penyewa &p : penyewas)
    {
        if (p.getUsername() == username)
            return false;
    }

    int id = penyewas.size() + 1;
    Penyewa newPenyewa(id, nama, kontak, username, password);
    penyewas.append(newPenyewa);
    return true;
}
