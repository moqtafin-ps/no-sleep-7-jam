#include "penyewawindow.h"
#include "rentaldialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QLabel>

PenyewaWindow::PenyewaWindow(Penyewa *penyewa, QVector<Sepatu> &s,
                             QVector<Penyewaan> &p, QWidget *parent)
    : QMainWindow(parent), currentPenyewa(penyewa), sepatus(s), penyewaans(p)
{
    setWindowTitle("EnfoLari - Dashboard Penyewa");
    setMinimumSize(800, 600);
    setupUI();
    refreshSepatuTable();
    refreshStatusTable();
}

PenyewaWindow::~PenyewaWindow()
{
}

void PenyewaWindow::setupUI()
{
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Welcome label
    QLabel *lblWelcome = new QLabel("Selamat Datang, " + currentPenyewa->getNama(), this);
    QFont font = lblWelcome->font();
    font.setPointSize(12);
    font.setBold(true);
    lblWelcome->setFont(font);
    mainLayout->addWidget(lblWelcome);

    // Tab widget
    tabWidget = new QTabWidget(this);

    // ===== Browse Shoes Tab =====
    QWidget *sepatuTab = new QWidget();
    QVBoxLayout *sepatuLayout = new QVBoxLayout(sepatuTab);

    tableSepatu = new QTableWidget(this);
    tableSepatu->setColumnCount(5);
    tableSepatu->setHorizontalHeaderLabels({"ID", "Nama", "Harga/Hari", "Ukuran", "Stok"});
    tableSepatu->horizontalHeader()->setStretchLastSection(true);
    tableSepatu->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableSepatu->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QHBoxLayout *sepatuButtonLayout = new QHBoxLayout();
    btnRentSepatu = new QPushButton("Sewa Sepatu", this);
    btnRefreshSepatu = new QPushButton("Refresh", this);

    sepatuButtonLayout->addWidget(btnRentSepatu);
    sepatuButtonLayout->addWidget(btnRefreshSepatu);
    sepatuButtonLayout->addStretch();

    sepatuLayout->addWidget(tableSepatu);
    sepatuLayout->addLayout(sepatuButtonLayout);

    tabWidget->addTab(sepatuTab, "Daftar Sepatu");

    // ===== Rental Status Tab =====
    QWidget *statusTab = new QWidget();
    QVBoxLayout *statusLayout = new QVBoxLayout(statusTab);

    tableStatus = new QTableWidget(this);
    tableStatus->setColumnCount(7);
    tableStatus->setHorizontalHeaderLabels({"ID Sewa", "Sepatu", "Ukuran", "Tanggal", "Lama (hari)", "Status", "Total (Rp)"});
    tableStatus->horizontalHeader()->setStretchLastSection(true);
    tableStatus->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableStatus->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QHBoxLayout *statusButtonLayout = new QHBoxLayout();
    btnRefreshStatus = new QPushButton("Refresh", this);

    statusButtonLayout->addWidget(btnRefreshStatus);
    statusButtonLayout->addStretch();

    statusLayout->addWidget(tableStatus);
    statusLayout->addLayout(statusButtonLayout);

    tabWidget->addTab(statusTab, "Status Penyewaan");

    mainLayout->addWidget(tabWidget);

    // Logout button
    btnLogout = new QPushButton("Logout", this);
    mainLayout->addWidget(btnLogout);

    setCentralWidget(centralWidget);

    // Connect signals
    connect(btnRentSepatu, &QPushButton::clicked, this, &PenyewaWindow::onRentSepatuClicked);
    connect(btnRefreshSepatu, &QPushButton::clicked, this, &PenyewaWindow::onRefreshSepatuClicked);
    connect(btnRefreshStatus, &QPushButton::clicked, this, &PenyewaWindow::onRefreshStatusClicked);
    connect(btnLogout, &QPushButton::clicked, this, &PenyewaWindow::onLogoutClicked);
}

void PenyewaWindow::refreshSepatuTable()
{
    tableSepatu->setRowCount(0);

    for (int i = 0; i < sepatus.size(); ++i)
    {
        const Sepatu &s = sepatus[i];
        int row = tableSepatu->rowCount();
        tableSepatu->insertRow(row);

        tableSepatu->setItem(row, 0, new QTableWidgetItem(QString::number(s.getIdSepatu())));
        tableSepatu->setItem(row, 1, new QTableWidgetItem(s.getNamaSepatu()));
        tableSepatu->setItem(row, 2, new QTableWidgetItem(QString::number(s.getHargaSewa(), 'f', 0)));
        tableSepatu->setItem(row, 3, new QTableWidgetItem(QString::number(s.getUkuran())));
        tableSepatu->setItem(row, 4, new QTableWidgetItem(QString::number(s.getStok())));
    }
}

void PenyewaWindow::refreshStatusTable()
{
    tableStatus->setRowCount(0);

    for (int i = 0; i < penyewaans.size(); ++i)
    {
        const Penyewaan &p = penyewaans[i];

        // Only show rentals for current user
        if (p.getPenyewa().getIdUser() == currentPenyewa->getIdUser())
        {
            int row = tableStatus->rowCount();
            tableStatus->insertRow(row);

            tableStatus->setItem(row, 0, new QTableWidgetItem(QString::number(p.getIdSewa())));
            tableStatus->setItem(row, 1, new QTableWidgetItem(p.getSepatu().getNamaSepatu()));
            tableStatus->setItem(row, 2, new QTableWidgetItem(QString::number(p.getSepatu().getUkuran())));
            tableStatus->setItem(row, 3, new QTableWidgetItem(p.getTanggalSewa()));
            tableStatus->setItem(row, 4, new QTableWidgetItem(QString::number(p.getLamaSewa())));
            tableStatus->setItem(row, 5, new QTableWidgetItem(p.getStatusSewa()));
            tableStatus->setItem(row, 6, new QTableWidgetItem(QString::number(p.getTotalHarga(), 'f', 0)));
        }
    }
}

void PenyewaWindow::onRentSepatuClicked()
{
    int currentRow = tableSepatu->currentRow();
    if (currentRow < 0)
    {
        QMessageBox::warning(this, "Peringatan", "Pilih sepatu yang ingin disewa!");
        return;
    }

    int id = tableSepatu->item(currentRow, 0)->text().toInt();
    Sepatu *sepatu = Sepatu::cariSepatu(sepatus, id);

    if (!sepatu)
    {
        QMessageBox::warning(this, "Gagal", "Sepatu tidak ditemukan!");
        return;
    }

    if (sepatu->getStok() <= 0)
    {
        QMessageBox::warning(this, "Stok Habis", "Maaf, stok sepatu ini habis!");
        return;
    }

    RentalDialog dialog(currentPenyewa, sepatu, this);
    if (dialog.exec() == QDialog::Accepted)
    {
        QString tanggalSewa = dialog.getTanggalSewa();
        int lamaSewa = dialog.getLamaSewa();
        double totalHarga = sepatu->getHargaSewa() * lamaSewa;

        int idSewa = penyewaans.size() + 1;
        Penyewaan newRental(idSewa, *currentPenyewa, *sepatu, tanggalSewa, lamaSewa, totalHarga);
        penyewaans.append(newRental);

        // Reduce stock
        sepatu->setStok(sepatu->getStok() - 1);

        refreshSepatuTable();
        refreshStatusTable();

        QMessageBox::information(this, "Sukses",
                                 QString("Penyewaan berhasil!\nTotal: Rp %1").arg(totalHarga, 0, 'f', 0));
    }
}

void PenyewaWindow::onRefreshSepatuClicked()
{
    refreshSepatuTable();
}

void PenyewaWindow::onRefreshStatusClicked()
{
    refreshStatusTable();
}

void PenyewaWindow::onLogoutClicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this,
                                                              "Konfirmasi", "Apakah Anda yakin ingin logout?",
                                                              QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        emit windowClosed();
        close();
    }
}