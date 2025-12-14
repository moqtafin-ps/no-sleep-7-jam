#include "logindialog.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QMessageBox>

LoginDialog::LoginDialog(DialogType type, QWidget *parent)
    : QDialog(parent), dialogType(type)
{
    setupUI();
}

LoginDialog::~LoginDialog()
{
}

void LoginDialog::setupUI()
{
    setModal(true);
    setMinimumWidth(350);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QFormLayout *formLayout = new QFormLayout();

    // Title
    lblTitle = new QLabel(this);
    QFont titleFont = lblTitle->font();
    titleFont.setPointSize(12);
    titleFont.setBold(true);
    lblTitle->setFont(titleFont);
    lblTitle->setAlignment(Qt::AlignCenter);

    switch (dialogType)
    {
    case LoginAdmin:
        setWindowTitle("Login Admin");
        lblTitle->setText("Login sebagai Admin");
        break;
    case LoginPenyewa:
        setWindowTitle("Login Penyewa");
        lblTitle->setText("Login sebagai Penyewa");
        break;
    case Register:
        setWindowTitle("Registrasi Penyewa");
        lblTitle->setText("Registrasi Penyewa Baru");
        break;
    }

    mainLayout->addWidget(lblTitle);
    mainLayout->addSpacing(20);

    // Form fields
    if (dialogType == Register)
    {
        editNama = new QLineEdit(this);
        editKontak = new QLineEdit(this);
        formLayout->addRow("Nama:", editNama);
        formLayout->addRow("Kontak:", editKontak);
    }

    editUsername = new QLineEdit(this);
    editPassword = new QLineEdit(this);
    editPassword->setEchoMode(QLineEdit::Password);

    formLayout->addRow("Username:", editUsername);
    formLayout->addRow("Password:", editPassword);

    mainLayout->addLayout(formLayout);
    mainLayout->addSpacing(20);

    // Buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    btnOk = new QPushButton(dialogType == Register ? "Daftar" : "Login", this);
    btnCancel = new QPushButton("Batal", this);

    buttonLayout->addStretch();
    buttonLayout->addWidget(btnOk);
    buttonLayout->addWidget(btnCancel);

    mainLayout->addLayout(buttonLayout);

    // Connect signals
    connect(btnOk, &QPushButton::clicked, this, &LoginDialog::onOkClicked);
    connect(btnCancel, &QPushButton::clicked, this, &LoginDialog::onCancelClicked);

    // Set focus
    editUsername->setFocus();
}

QString LoginDialog::getUsername() const
{
    return editUsername->text().trimmed();
}

QString LoginDialog::getPassword() const
{
    return editPassword->text().trimmed();
}

QString LoginDialog::getNama() const
{
    if (dialogType == Register && editNama)
        return editNama->text().trimmed();
    return QString();
}

QString LoginDialog::getKontak() const
{
    if (dialogType == Register && editKontak)
        return editKontak->text().trimmed();
    return QString();
}

void LoginDialog::onOkClicked()
{
    if (dialogType == Register)
    {
        if (editNama->text().trimmed().isEmpty() ||
            editKontak->text().trimmed().isEmpty() ||
            editUsername->text().trimmed().isEmpty() ||
            editPassword->text().trimmed().isEmpty())
        {
            QMessageBox::warning(this, "Input Tidak Lengkap",
                                 "Semua field harus diisi!");
            return;
        }
    }
    else
    {
        if (editUsername->text().trimmed().isEmpty() ||
            editPassword->text().trimmed().isEmpty())
        {
            QMessageBox::warning(this, "Input Tidak Lengkap",
                                 "Username dan password harus diisi!");
            return;
        }
    }

    accept();
}

void LoginDialog::onCancelClicked()
{
    reject();
}