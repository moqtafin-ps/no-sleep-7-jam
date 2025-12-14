#ifndef ADMIN_H
#define ADMIN_H

#include <QString>
#include <QVector>

class Sepatu;
class Penyewaan;

class Admin
{
public:
    Admin();
    Admin(int id, const QString &username, const QString &password);
    ~Admin();

    // Getters
    int getIdAdmin() const;
    QString getUsername() const;
    QString getPassword() const;

    // Static methods for data management
    static void loadAdmin(const QString &filePath, QVector<Admin> &admins);
    static void saveAdmin(const QString &filePath, const QVector<Admin> &admins);
    static void defaultAdmin(QVector<Admin> &admins);
    static Admin* authenticate(QVector<Admin> &admins, const QString &username, const QString &password);

private:
    int idAdmin;
    QString username;
    QString password;
};

#endif // ADMIN_H
