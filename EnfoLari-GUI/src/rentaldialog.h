#ifndef RENTALDIALOG_H
#define RENTALDIALOG_H

#include <QDialog>
#include <QDateEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QLabel>
#include "core/penyewa.h"
#include "core/sepatu.h"

class RentalDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RentalDialog(Penyewa *penyewa, Sepatu *sepatu, QWidget *parent = nullptr);
    ~RentalDialog();

    QString getTanggalSewa() const;
    int getLamaSewa() const;

private slots:
    void onLamaSewaChanged(int days);
    void onOkClicked();
    void onCancelClicked();

private:
    void setupUI();
    void updateTotal();

    Penyewa *currentPenyewa;
    Sepatu *currentSepatu;
    
    QLabel *lblInfo;
    QLabel *lblHarga;
    QLabel *lblTotal;
    QDateEdit *dateEdit;
    QSpinBox *spinLamaSewa;
    QPushButton *btnOk;
    QPushButton *btnCancel;
};

#endif // RENTALDIALOG_H
