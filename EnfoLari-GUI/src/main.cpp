#include "mainwindow.h"
#include <QApplication>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    // Create data directory if it doesn't exist
    QDir dir;
    if (!dir.exists("data"))
    {
        dir.mkpath("data");
    }
    
    MainWindow mainWindow;
    mainWindow.show();
    
    return app.exec();
}
