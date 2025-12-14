#ifndef SEPATUDIALOG_H
#define SEPATUDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include "core/sepatu.h"

class SepatuDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SepatuDialog(Sepatu *sepatu, QWidget *parent = nullptr);
    ~SepatuDialog();

    int getId() const;
    QString getNama() const;
    double getHarga() const;
    int getUkuran() const;
    int getStok() const;

private slots:
    void onOkClicked();
    void onCancelClicked();

private:
    void setupUI();

    Sepatu *currentSepatu; // nullptr for add, valid for edit

    QSpinBox *spinId;
    QLineEdit *editNama;
    QDoubleSpinBox *spinHarga;
    QSpinBox *spinUkuran;
    QSpinBox *spinStok;

    QPushButton *btnOk;
    QPushButton *btnCancel;
};

#endif // SEPATUDIALOG_H
