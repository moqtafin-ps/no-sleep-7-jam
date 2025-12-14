#include "admin.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

Admin::Admin()
    : idAdmin(0), username(""), password("")
{
}

Admin::Admin(int id, const QString &u, const QString &p)
    : idAdmin(id), username(u), password(p)
{
}

Admin::~Admin()
{
}

int Admin::getIdAdmin() const
{
    return idAdmin;
}

QString Admin::getUsername() const
{
    return username;
}

QString Admin::getPassword() const
{
    return password;
}

void Admin::loadAdmin(const QString &filePath, QVector<Admin> &admins)
{
    admins.clear();
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
        if (parts.size() >= 3)
        {
            int id = parts[0].toInt();
            QString username = parts[1];
            QString password = parts[2];
            admins.append(Admin(id, username, password));
        }
    }
    file.close();
}

void Admin::saveAdmin(const QString &filePath, const QVector<Admin> &admins)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    for (const Admin &admin : admins)
    {
        out << admin.getIdAdmin() << ","
            << admin.getUsername() << ","
            << admin.getPassword() << "\n";
    }
    file.close();
}

void Admin::defaultAdmin(QVector<Admin> &admins)
{
    loadAdmin("data/admin.txt", admins);
    if (admins.isEmpty())
    {
        Admin defaultAdmin(1, "admin", "admin123");
        admins.append(defaultAdmin);
        qDebug() << "Default admin created (username: admin, password: admin123)";
    }
}

Admin* Admin::authenticate(QVector<Admin> &admins, const QString &username, const QString &password)
{
    for (int i = 0; i < admins.size(); ++i)
    {
        if (admins[i].getUsername() == username && admins[i].getPassword() == password)
        {
            return &admins[i];
        }
    }
    return nullptr;
}
