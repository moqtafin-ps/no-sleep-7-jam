#ifndef PENYEWA_H
#define PENYEWA_H

#include <QString>
#include <QVector>

class Penyewa
{
public:
    Penyewa();
    Penyewa(int id, const QString &nama, const QString &kontak, 
            const QString &username, const QString &password);
    ~Penyewa();

    // Getters
    int getIdUser() const;
    QString getNama() const;
    QString getKontak() const;
    QString getUsername() const;
    QString getPassword() const;

    // Setters
    void setNama(const QString &nama);
    void setKontak(const QString &kontak);
    void setUsername(const QString &username);
    void setPassword(const QString &password);

    // Static methods
    static void loadPenyewa(const QString &filePath, QVector<Penyewa> &penyewas);
    static void savePenyewa(const QString &filePath, const QVector<Penyewa> &penyewas);
    static Penyewa* cariPenyewa(QVector<Penyewa> &penyewas, int idUser);
    static Penyewa* authenticate(QVector<Penyewa> &penyewas, const QString &username, const QString &password);
    static bool registrasi(QVector<Penyewa> &penyewas, const QString &nama, 
                          const QString &kontak, const QString &username, const QString &password);

private:
    int idUser;
    QString nama;
    QString kontak;
    QString username;
    QString password;
};

#endif // PENYEWA_H
