#ifndef PENYEWAWINDOW_H
#define PENYEWAWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QTabWidget>
#include "core/penyewa.h"
#include "core/sepatu.h"
#include "core/penyewaan.h"

class PenyewaWindow : public QMainWindow
{
    Q_OBJECT

public:
    PenyewaWindow(Penyewa *penyewa, QVector<Sepatu> &sepatus,
                  QVector<Penyewaan> &penyewaans, QWidget *parent = nullptr);
    ~PenyewaWindow();

signals:
    void windowClosed();

private slots:
    void onRentSepatuClicked();
    void onRefreshSepatuClicked();
    void onRefreshStatusClicked();
    void onLogoutClicked();

private:
    void setupUI();
    void refreshSepatuTable();
    void refreshStatusTable();

    Penyewa *currentPenyewa;
    QVector<Sepatu> &sepatus;
    QVector<Penyewaan> &penyewaans;

    QTabWidget *tabWidget;
    
    // Browse shoes
    QTableWidget *tableSepatu;
    QPushButton *btnRentSepatu;
    QPushButton *btnRefreshSepatu;
    
    // Rental status
    QTableWidget *tableStatus;
    QPushButton *btnRefreshStatus;
    
    QPushButton *btnLogout;
};

#endif // PENYEWAWINDOW_H
