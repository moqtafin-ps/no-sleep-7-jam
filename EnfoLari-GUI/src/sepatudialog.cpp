#include "sepatudialog.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>

SepatuDialog::SepatuDialog(Sepatu *sepatu, QWidget *parent)
    : QDialog(parent), currentSepatu(sepatu)
{
    setupUI();
}

SepatuDialog::~SepatuDialog()
{
}

void SepatuDialog::setupUI()
{
    setModal(true);
    setMinimumWidth(400);

    if (currentSepatu)
    {
        setWindowTitle("Edit Sepatu");
    }
    else
    {
        setWindowTitle("Tambah Sepatu");
    }

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QFormLayout *formLayout = new QFormLayout();

    // ID
    spinId = new QSpinBox(this);
    spinId->setRange(1, 99999);
    if (currentSepatu)
    {
        spinId->setValue(currentSepatu->getIdSepatu());
        spinId->setEnabled(false); // ID cannot be changed
    }
    formLayout->addRow("ID:", spinId);

    // Nama
    editNama = new QLineEdit(this);
    if (currentSepatu)
    {
        editNama->setText(currentSepatu->getNamaSepatu());
    }
    formLayout->addRow("Nama Sepatu:", editNama);

    // Harga
    spinHarga = new QDoubleSpinBox(this);
    spinHarga->setRange(0, 1000000);
    spinHarga->setDecimals(0);
    spinHarga->setSuffix(" Rp");
    if (currentSepatu)
    {
        spinHarga->setValue(currentSepatu->getHargaSewa());
    }
    formLayout->addRow("Harga Sewa/Hari:", spinHarga);

    // Ukuran
    spinUkuran = new QSpinBox(this);
    spinUkuran->setRange(20, 50);
    if (currentSepatu)
    {
        spinUkuran->setValue(currentSepatu->getUkuran());
    }
    formLayout->addRow("Ukuran:", spinUkuran);

    // Stok
    spinStok = new QSpinBox(this);
    spinStok->setRange(0, 1000);
    if (currentSepatu)
    {
        spinStok->setValue(currentSepatu->getStok());
    }
    formLayout->addRow("Stok:", spinStok);

    mainLayout->addLayout(formLayout);
    mainLayout->addSpacing(20);

    // Buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    btnOk = new QPushButton(currentSepatu ? "Update" : "Tambah", this);
    btnCancel = new QPushButton("Batal", this);

    buttonLayout->addStretch();
    buttonLayout->addWidget(btnOk);
    buttonLayout->addWidget(btnCancel);

    mainLayout->addLayout(buttonLayout);

    // Connect signals
    connect(btnOk, &QPushButton::clicked, this, &SepatuDialog::onOkClicked);
    connect(btnCancel, &QPushButton::clicked, this, &SepatuDialog::onCancelClicked);
}

int SepatuDialog::getId() const
{
    return spinId->value();
}

QString SepatuDialog::getNama() const
{
    return editNama->text().trimmed();
}

double SepatuDialog::getHarga() const
{
    return spinHarga->value();
}

int SepatuDialog::getUkuran() const
{
    return spinUkuran->value();
}

int SepatuDialog::getStok() const
{
    return spinStok->value();
}

void SepatuDialog::onOkClicked()
{
    if (editNama->text().trimmed().isEmpty())
    {
        QMessageBox::warning(this, "Input Tidak Valid",
                             "Nama sepatu tidak boleh kosong!");
        return;
    }

    if (spinHarga->value() <= 0)
    {
        QMessageBox::warning(this, "Input Tidak Valid",
                             "Harga sewa harus lebih dari 0!");
        return;
    }

    accept();
}

void SepatuDialog::onCancelClicked()
{
    reject();
}