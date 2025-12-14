QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/logindialog.cpp \
    src/adminwindow.cpp \
    src/penyewawindow.cpp \
    src/sepatudialog.cpp \
    src/rentaldialog.cpp \
    src/core/admin.cpp \
    src/core/penyewa.cpp \
    src/core/sepatu.cpp \
    src/core/penyewaan.cpp

HEADERS += \
    src/mainwindow.h \
    src/logindialog.h \
    src/adminwindow.h \
    src/penyewawindow.h \
    src/sepatudialog.h \
    src/rentaldialog.h \
    src/core/admin.h \
    src/core/penyewa.h \
    src/core/sepatu.h \
    src/core/penyewaan.h



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target