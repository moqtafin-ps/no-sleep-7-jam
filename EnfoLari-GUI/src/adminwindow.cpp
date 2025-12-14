#include "adminwindow.h"
#include "sepatudialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QCloseEvent>
#include <QLabel>

AdminWindow::AdminWindow(Admin *admin, QVector<Sepatu> &s,
                         QVector<Penyewaan> &p, QVector<Penyewa> &py,
                         QWidget *parent)
    : QMainWindow(parent), currentAdmin(admin), sepatus(s), penyewaans(p), penyewas(py)
{
    setWindowTitle("EnfoLari - Dashboard Admin");
    setMinimumSize(800, 600);
    setupUI();
    refreshSepatuTable();
    refreshRentalTable();
}

AdminWindow::~AdminWindow()
{
}

void AdminWindow::setupUI()
{
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Welcome label
    QLabel *lblWelcome = new QLabel("Selamat Datang, Admin " + currentAdmin->getUsername(), this);
    QFont font = lblWelcome->font();
    font.setPointSize(12);
    font.setBold(true);
    lblWelcome->setFont(font);
    mainLayout->addWidget(lblWelcome);

    // Tab widget
    tabWidget = new QTabWidget(this);

    // ===== Sepatu Management Tab =====
    QWidget *sepatuTab = new QWidget();
    QVBoxLayout *sepatuLayout = new QVBoxLayout(sepatuTab);

    tableSepatut = new QTableWidget(this);
    tableSepatut->setColumnCount(5);
    tableSepatut->setHorizontalHeaderLabels({"ID", "Nama", "Harga/Hari", "Ukuran", "Stok"});
    tableSepatut->horizontalHeader()->setStretchLastSection(true);
    tableSepatut->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableSepatut->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QHBoxLayout *sepatuButtonLayout = new QHBoxLayout();
    btnAddSepatu = new QPushButton("Tambah", this);
    btnEditSepatu = new QPushButton("Edit", this);
    btnDeleteSepatu = new QPushButton("Hapus", this);
    btnRefreshSepatu = new QPushButton("Refresh", this);

    sepatuButtonLayout->addWidget(btnAddSepatu);
    sepatuButtonLayout->addWidget(btnEditSepatu);
    sepatuButtonLayout->addWidget(btnDeleteSepatu);
    sepatuButtonLayout->addWidget(btnRefreshSepatu);
    sepatuButtonLayout->addStretch();

    sepatuLayout->addWidget(tableSepatut);
    sepatuLayout->addLayout(sepatuButtonLayout);

    tabWidget->addTab(sepatuTab, "Kelola Sepatu");

    // ===== Rental Management Tab =====
    QWidget *rentalTab = new QWidget();
    QVBoxLayout *rentalLayout = new QVBoxLayout(rentalTab);

    tableRental = new QTableWidget(this);
    tableRental->setColumnCount(7);
    tableRental->setHorizontalHeaderLabels({"ID Sewa", "Penyewa", "Sepatu", "Tanggal", "Lama (hari)", "Status", "Total (Rp)"});
    tableRental->horizontalHeader()->setStretchLastSection(true);
    tableRental->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableRental->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QHBoxLayout *rentalButtonLayout = new QHBoxLayout();
    btnReturnRental = new QPushButton("Kembalikan Sepatu", this);
    btnRefreshRental = new QPushButton("Refresh", this);

    rentalButtonLayout->addWidget(btnReturnRental);
    rentalButtonLayout->addWidget(btnRefreshRental);
    rentalButtonLayout->addStretch();

    rentalLayout->addWidget(tableRental);
    rentalLayout->addLayout(rentalButtonLayout);

    tabWidget->addTab(rentalTab, "Kelola Penyewaan");

    mainLayout->addWidget(tabWidget);

    // Logout button
    btnLogout = new QPushButton("Logout", this);
    mainLayout->addWidget(btnLogout);

    setCentralWidget(centralWidget);

    // Connect signals
    connect(btnAddSepatu, &QPushButton::clicked, this, &AdminWindow::onAddSepatuClicked);
    connect(btnEditSepatu, &QPushButton::clicked, this, &AdminWindow::onEditSepatuClicked);
    connect(btnDeleteSepatu, &QPushButton::clicked, this, &AdminWindow::onDeleteSepatuClicked);
    connect(btnRefreshSepatu, &QPushButton::clicked, this, &AdminWindow::onRefreshSepatuClicked);
    connect(btnReturnRental, &QPushButton::clicked, this, &AdminWindow::onReturnRentalClicked);
    connect(btnRefreshRental, &QPushButton::clicked, this, &AdminWindow::onRefreshRentalClicked);
    connect(btnLogout, &QPushButton::clicked, this, &AdminWindow::onLogoutClicked);
}

void AdminWindow::refreshSepatuTable()
{
    tableSepatut->setRowCount(0);

    for (int i = 0; i < sepatus.size(); ++i)
    {
        const Sepatu &s = sepatus[i];
        int row = tableSepatut->rowCount();
        tableSepatut->insertRow(row);

        tableSepatut->setItem(row, 0, new QTableWidgetItem(QString::number(s.getIdSepatu())));
        tableSepatut->setItem(row, 1, new QTableWidgetItem(s.getNamaSepatu()));
        tableSepatut->setItem(row, 2, new QTableWidgetItem(QString::number(s.getHargaSewa(), 'f', 0)));
        tableSepatut->setItem(row, 3, new QTableWidgetItem(QString::number(s.getUkuran())));
        tableSepatut->setItem(row, 4, new QTableWidgetItem(QString::number(s.getStok())));
    }
}

void AdminWindow::refreshRentalTable()
{
    tableRental->setRowCount(0);

    for (int i = 0; i < penyewaans.size(); ++i)
    {
        const Penyewaan &p = penyewaans[i];
        int row = tableRental->rowCount();
        tableRental->insertRow(row);

        tableRental->setItem(row, 0, new QTableWidgetItem(QString::number(p.getIdSewa())));
        tableRental->setItem(row, 1, new QTableWidgetItem(p.getPenyewa().getNama()));
        tableRental->setItem(row, 2, new QTableWidgetItem(p.getSepatu().getNamaSepatu()));
        tableRental->setItem(row, 3, new QTableWidgetItem(p.getTanggalSewa()));
        tableRental->setItem(row, 4, new QTableWidgetItem(QString::number(p.getLamaSewa())));
        tableRental->setItem(row, 5, new QTableWidgetItem(p.getStatusSewa()));
        tableRental->setItem(row, 6, new QTableWidgetItem(QString::number(p.getTotalHarga(), 'f', 0)));
    }
}

void AdminWindow::onAddSepatuClicked()
{
    SepatuDialog dialog(nullptr, this);
    if (dialog.exec() == QDialog::Accepted)
    {
        int id = dialog.getId();
        QString nama = dialog.getNama();
        double harga = dialog.getHarga();
        int ukuran = dialog.getUkuran();
        int stok = dialog.getStok();

        // Check if ID already exists
        if (Sepatu::cariSepatu(sepatus, id) != nullptr)
        {
            QMessageBox::warning(this, "Gagal", "ID sudah digunakan!");
            return;
        }

        sepatus.append(Sepatu(id, nama, harga, ukuran, stok));
        refreshSepatuTable();
        QMessageBox::information(this, "Sukses", "Sepatu berhasil ditambahkan!");
    }
}

void AdminWindow::onEditSepatuClicked()
{
    int currentRow = tableSepatut->currentRow();
    if (currentRow < 0)
    {
        QMessageBox::warning(this, "Peringatan", "Pilih sepatu yang ingin diedit!");
        return;
    }

    int id = tableSepatut->item(currentRow, 0)->text().toInt();
    Sepatu *sepatu = Sepatu::cariSepatu(sepatus, id);

    if (sepatu)
    {
        SepatuDialog dialog(sepatu, this);
        if (dialog.exec() == QDialog::Accepted)
        {
            sepatu->setNamaSepatu(dialog.getNama());
            sepatu->setHargaSewa(dialog.getHarga());
            sepatu->setUkuran(dialog.getUkuran());
            sepatu->setStok(dialog.getStok());

            refreshSepatuTable();
            QMessageBox::information(this, "Sukses", "Sepatu berhasil diedit!");
        }
    }
}

void AdminWindow::onDeleteSepatuClicked()
{
    int currentRow = tableSepatut->currentRow();
    if (currentRow < 0)
    {
        QMessageBox::warning(this, "Peringatan", "Pilih sepatu yang ingin dihapus!");
        return;
    }

    QMessageBox::StandardButton reply = QMessageBox::question(this,
                                                              "Konfirmasi", "Apakah Anda yakin ingin menghapus sepatu ini?",
                                                              QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        int id = tableSepatut->item(currentRow, 0)->text().toInt();

        for (int i = 0; i < sepatus.size(); ++i)
        {
            if (sepatus[i].getIdSepatu() == id)
            {
                sepatus.remove(i);
                refreshSepatuTable();
                QMessageBox::information(this, "Sukses", "Sepatu berhasil dihapus!");
                return;
            }
        }
    }
}

void AdminWindow::onRefreshSepatuClicked()
{
    refreshSepatuTable();
}

void AdminWindow::onReturnRentalClicked()
{
    int currentRow = tableRental->currentRow();
    if (currentRow < 0)
    {
        QMessageBox::warning(this, "Peringatan", "Pilih penyewaan yang ingin dikembalikan!");
        return;
    }

    int idSewa = tableRental->item(currentRow, 0)->text().toInt();
    Penyewaan *penyewaan = Penyewaan::cariPenyewaan(penyewaans, idSewa);

    if (penyewaan && penyewaan->getStatusSewa() == "Dipinjam")
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this,
                                                                  "Konfirmasi", "Tandai penyewaan ini sebagai dikembalikan?",
                                                                  QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes)
        {
            penyewaan->updateStatus("Dikembalikan");

            // Return stock
            int idSepatu = penyewaan->getSepatu().getIdSepatu();
            Sepatu *sepatu = Sepatu::cariSepatu(sepatus, idSepatu);
            if (sepatu)
            {
                sepatu->setStok(sepatu->getStok() + 1);
            }

            // Remove from active rentals
            for (int i = 0; i < penyewaans.size(); ++i)
            {
                if (penyewaans[i].getIdSewa() == idSewa)
                {
                    penyewaans.remove(i);
                    break;
                }
            }

            refreshRentalTable();
            refreshSepatuTable();
            QMessageBox::information(this, "Sukses",
                                     "Penyewaan telah dikembalikan dan stok diperbarui!");
        }
    }
    else
    {
        QMessageBox::warning(this, "Peringatan", "Penyewaan ini sudah dikembalikan!");
    }
}

void AdminWindow::onRefreshRentalClicked()
{
    refreshRentalTable();
}

void AdminWindow::onLogoutClicked()
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