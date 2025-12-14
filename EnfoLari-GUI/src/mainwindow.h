#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include "core/admin.h"
#include "core/penyewa.h"
#include "core/sepatu.h"
#include "core/penyewaan.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onRegisterClicked();
    void onLoginPenyewaClicked();
    void onLoginAdminClicked();

private:
    void setupUI();
    void loadAllData();
    void saveAllData();

    // UI Components
    QPushButton *btnRegister;
    QPushButton *btnLoginPenyewa;
    QPushButton *btnLoginAdmin;
    QPushButton *btnExit;
    QLabel *lblTitle;

    // Data
    QVector<Admin> admins;
    QVector<Penyewa> penyewas;
    QVector<Sepatu> sepatus;
    QVector<Penyewaan> penyewaans;

    // File paths
    const QString DATA_ADMIN = "data/admin.txt";
    const QString DATA_PENYEWA = "data/penyewa.txt";
    const QString DATA_SEPATU = "data/sepatu.txt";
    const QString DATA_PENYEWAAN = "data/penyewaan.txt";

protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif // MAINWINDOW_H
