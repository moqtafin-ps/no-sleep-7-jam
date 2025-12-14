#include "mainwindow.h"
#include "logindialog.h"
#include "adminwindow.h"
#include "penyewawindow.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("EnfoLari - Sistem Penyewaan Sepatu");
    setMinimumSize(400, 300);

    loadAllData();
    setupUI();
}

MainWindow::~MainWindow()
{
    saveAllData();
}

void MainWindow::setupUI()
{
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    // Title
    lblTitle = new QLabel("Selamat Datang di\nSewa Sepatu EnfoLari", this);
    QFont titleFont = lblTitle->font();
    titleFont.setPointSize(16);
    titleFont.setBold(true);
    lblTitle->setFont(titleFont);
    lblTitle->setAlignment(Qt::AlignCenter);
    lblTitle->setStyleSheet(
        "color: #2c3e50; "
        "background-color: #ecf0f1; "
        "padding: 20px; "
        "border-radius: 10px;"
        );

    // Buttons
    btnRegister = new QPushButton("Registrasi Penyewa", this);
    btnLoginPenyewa = new QPushButton("Login Penyewa", this);
    btnLoginAdmin = new QPushButton("Login Admin", this);
    btnExit = new QPushButton("Keluar", this);

    // Set button sizes
    QSize buttonSize(250, 40);
    btnRegister->setMinimumSize(buttonSize);
    btnLoginPenyewa->setMinimumSize(buttonSize);
    btnLoginAdmin->setMinimumSize(buttonSize);
    btnExit->setMinimumSize(buttonSize);

    // Add widgets to layout
    layout->addStretch();
    layout->addWidget(lblTitle);
    layout->addSpacing(30);
    layout->addWidget(btnRegister, 0, Qt::AlignCenter);
    layout->addWidget(btnLoginPenyewa, 0, Qt::AlignCenter);
    layout->addWidget(btnLoginAdmin, 0, Qt::AlignCenter);
    layout->addSpacing(20);
    layout->addWidget(btnExit, 0, Qt::AlignCenter);
    layout->addStretch();

    // Connect signals
    connect(btnRegister, &QPushButton::clicked, this, &MainWindow::onRegisterClicked);
    connect(btnLoginPenyewa, &QPushButton::clicked, this, &MainWindow::onLoginPenyewaClicked);
    connect(btnLoginAdmin, &QPushButton::clicked, this, &MainWindow::onLoginAdminClicked);
    connect(btnExit, &QPushButton::clicked, this, &QMainWindow::close);

    setCentralWidget(centralWidget);
}

void MainWindow::loadAllData()
{
    Admin::defaultAdmin(admins);
    Penyewa::loadPenyewa(DATA_PENYEWA, penyewas);
    Sepatu::loadSepatu(DATA_SEPATU, sepatus);
    Penyewaan::loadPenyewaan(DATA_PENYEWAAN, penyewaans, penyewas, sepatus);
}

void MainWindow::saveAllData()
{
    Admin::saveAdmin(DATA_ADMIN, admins);
    Penyewa::savePenyewa(DATA_PENYEWA, penyewas);
    Sepatu::saveSepatu(DATA_SEPATU, sepatus);
    Penyewaan::savePenyewaan(DATA_PENYEWAAN, penyewaans);
}

void MainWindow::onRegisterClicked()
{
    LoginDialog dialog(LoginDialog::Register, this);
    if (dialog.exec() == QDialog::Accepted)
    {
        QString nama = dialog.getNama();
        QString kontak = dialog.getKontak();
        QString username = dialog.getUsername();
        QString password = dialog.getPassword();

        if (Penyewa::registrasi(penyewas, nama, kontak, username, password))
        {
            Penyewa::savePenyewa(DATA_PENYEWA, penyewas);
            QMessageBox::information(this, "Sukses",
                                     "Registrasi berhasil! Silakan login.");
        }
        else
        {
            QMessageBox::warning(this, "Gagal",
                                 "Username sudah digunakan!");
        }
    }
}

void MainWindow::onLoginPenyewaClicked()
{
    LoginDialog dialog(LoginDialog::LoginPenyewa, this);
    if (dialog.exec() == QDialog::Accepted)
    {
        QString username = dialog.getUsername();
        QString password = dialog.getPassword();

        Penyewa *penyewa = Penyewa::authenticate(penyewas, username, password);
        if (penyewa)
        {
            PenyewaWindow *window = new PenyewaWindow(penyewa, sepatus, penyewaans, this);
            window->setAttribute(Qt::WA_DeleteOnClose);
            window->show();
            this->hide();

            connect(window, &PenyewaWindow::windowClosed, this, [this]()
                    {
                saveAllData();
                loadAllData();
                this->show(); });
        }
        else
        {
            QMessageBox::warning(this, "Login Gagal",
                                 "Username atau password salah!");
        }
    }
}

void MainWindow::onLoginAdminClicked()
{
    LoginDialog dialog(LoginDialog::LoginAdmin, this);
    if (dialog.exec() == QDialog::Accepted)
    {
        QString username = dialog.getUsername();
        QString password = dialog.getPassword();

        Admin *admin = Admin::authenticate(admins, username, password);
        if (admin)
        {
            AdminWindow *window = new AdminWindow(admin, sepatus, penyewaans, penyewas, this);
            window->setAttribute(Qt::WA_DeleteOnClose);
            window->show();
            this->hide();

            connect(window, &AdminWindow::windowClosed, this, [this]()
                    {
                saveAllData();
                loadAllData();
                this->show(); });
        }
        else
        {
            QMessageBox::warning(this, "Login Gagal",
                                 "Username atau password salah!");
        }
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton reply = QMessageBox::question(this,
                                                              "Konfirmasi",
                                                              "Apakah Anda yakin ingin keluar?",
                                                              QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        saveAllData();
        event->accept();
    }
    else
    {
        event->ignore();
    }
}
