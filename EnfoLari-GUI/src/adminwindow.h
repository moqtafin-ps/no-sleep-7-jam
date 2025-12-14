#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QTabWidget>
#include "core/admin.h"
#include "core/sepatu.h"
#include "core/penyewaan.h"
#include "core/penyewa.h"

class AdminWindow : public QMainWindow
{
    Q_OBJECT

public:
    AdminWindow(Admin *admin, QVector<Sepatu> &sepatus, 
                QVector<Penyewaan> &penyewaans, QVector<Penyewa> &penyewas,
                QWidget *parent = nullptr);
    ~AdminWindow();

signals:
    void windowClosed();

private slots:
    void onAddSepatuClicked();
    void onEditSepatuClicked();
    void onDeleteSepatuClicked();
    void onRefreshSepatuClicked();
    void onReturnRentalClicked();
    void onRefreshRentalClicked();
    void onLogoutClicked();

private:
    void setupUI();
    void refreshSepatuTable();
    void refreshRentalTable();

    Admin *currentAdmin;
    QVector<Sepatu> &sepatus;
    QVector<Penyewaan> &penyewaans;
    QVector<Penyewa> &penyewas;

    QTabWidget *tabWidget;
    
    // Sepatu management
    QTableWidget *tableSepatut;
    QPushButton *btnAddSepatu;
    QPushButton *btnEditSepatu;
    QPushButton *btnDeleteSepatu;
    QPushButton *btnRefreshSepatu;
    
    // Rental management
    QTableWidget *tableRental;
    QPushButton *btnReturnRental;
    QPushButton *btnRefreshRental;
    
    QPushButton *btnLogout;
};

#endif // ADMINWINDOW_H
