#include "rentaldialog.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QMessageBox>
#include <QDate>

RentalDialog::RentalDialog(Penyewa *penyewa, Sepatu *sepatu, QWidget *parent)
    : QDialog(parent), currentPenyewa(penyewa), currentSepatu(sepatu)
{
    setupUI();
}

RentalDialog::~RentalDialog()
{
}

void RentalDialog::setupUI()
{
    setModal(true);
    setMinimumWidth(450);
    setWindowTitle("Sewa Sepatu");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Info section
    QGroupBox *infoBox = new QGroupBox("Informasi Sepatu", this);
    QVBoxLayout *infoLayout = new QVBoxLayout(infoBox);

    lblInfo = new QLabel(this);
    lblInfo->setText(QString("<b>Nama:</b> %1<br>"
                             "<b>Ukuran:</b> %2<br>"
                             "<b>Stok Tersedia:</b> %3")
                         .arg(currentSepatu->getNamaSepatu())
                         .arg(currentSepatu->getUkuran())
                         .arg(currentSepatu->getStok()));
    infoLayout->addWidget(lblInfo);

    lblHarga = new QLabel(this);
    lblHarga->setText(QString("<b>Harga Sewa:</b> Rp %1 / hari")
                          .arg(currentSepatu->getHargaSewa(), 0, 'f', 0));
    QFont hargaFont = lblHarga->font();
    hargaFont.setPointSize(10);
    lblHarga->setFont(hargaFont);
    infoLayout->addWidget(lblHarga);

    mainLayout->addWidget(infoBox);
    mainLayout->addSpacing(10);

    // Rental details
    QGroupBox *rentalBox = new QGroupBox("Detail Penyewaan", this);
    QFormLayout *formLayout = new QFormLayout(rentalBox);

    // Tanggal sewa
    dateEdit = new QDateEdit(QDate::currentDate(), this);
    dateEdit->setCalendarPopup(true);
    dateEdit->setDisplayFormat("dd-MM-yyyy");
    dateEdit->setMinimumDate(QDate::currentDate());
    formLayout->addRow("Tanggal Sewa:", dateEdit);

    // Lama sewa
    spinLamaSewa = new QSpinBox(this);
    spinLamaSewa->setRange(1, 30);
    spinLamaSewa->setValue(1);
    spinLamaSewa->setSuffix(" hari");
    formLayout->addRow("Lama Sewa:", spinLamaSewa);

    mainLayout->addWidget(rentalBox);
    mainLayout->addSpacing(10);

    // Total
    QGroupBox *totalBox = new QGroupBox("Total Pembayaran", this);
    QVBoxLayout *totalLayout = new QVBoxLayout(totalBox);

    lblTotal = new QLabel(this);
    QFont totalFont = lblTotal->font();
    totalFont.setPointSize(14);
    totalFont.setBold(true);
    lblTotal->setFont(totalFont);
    lblTotal->setAlignment(Qt::AlignCenter);
    updateTotal();
    totalLayout->addWidget(lblTotal);

    mainLayout->addWidget(totalBox);
    mainLayout->addSpacing(20);

    // Buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    btnOk = new QPushButton("Sewa", this);
    btnCancel = new QPushButton("Batal", this);

    buttonLayout->addStretch();
    buttonLayout->addWidget(btnOk);
    buttonLayout->addWidget(btnCancel);

    mainLayout->addLayout(buttonLayout);

    // Connect signals
    connect(spinLamaSewa, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &RentalDialog::onLamaSewaChanged);
    connect(btnOk, &QPushButton::clicked, this, &RentalDialog::onOkClicked);
    connect(btnCancel, &QPushButton::clicked, this, &RentalDialog::onCancelClicked);
}

void RentalDialog::updateTotal()
{
    double total = currentSepatu->getHargaSewa() * spinLamaSewa->value();
    lblTotal->setText(QString("Rp %1").arg(total, 0, 'f', 0));
}

QString RentalDialog::getTanggalSewa() const
{
    return dateEdit->date().toString("dd-MM-yyyy");
}

int RentalDialog::getLamaSewa() const
{
    return spinLamaSewa->value();
}

void RentalDialog::onLamaSewaChanged(int /* days */)
{
    updateTotal();
}

void RentalDialog::onOkClicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this,
                                                              "Konfirmasi Penyewaan",
                                                              QString("Apakah Anda yakin ingin menyewa sepatu ini?\n\n"
                                                                      "Total yang harus dibayar: Rp %1")
                                                                  .arg(currentSepatu->getHargaSewa() * spinLamaSewa->value(), 0, 'f', 0),
                                                              QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        accept();
    }
}

void RentalDialog::onCancelClicked()
{
    reject();
}