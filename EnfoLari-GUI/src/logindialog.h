#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    enum DialogType {
        LoginAdmin,
        LoginPenyewa,
        Register
    };

    explicit LoginDialog(DialogType type, QWidget *parent = nullptr);
    ~LoginDialog();

    QString getUsername() const;
    QString getPassword() const;
    QString getNama() const;
    QString getKontak() const;

private slots:
    void onOkClicked();
    void onCancelClicked();

private:
    void setupUI();

    DialogType dialogType;
    
    QLabel *lblTitle;
    QLabel *lblNama;
    QLabel *lblKontak;
    QLabel *lblUsername;
    QLabel *lblPassword;
    
    QLineEdit *editNama;
    QLineEdit *editKontak;
    QLineEdit *editUsername;
    QLineEdit *editPassword;
    
    QPushButton *btnOk;
    QPushButton *btnCancel;
};

#endif // LOGINDIALOG_H
