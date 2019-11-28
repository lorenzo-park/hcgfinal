#include <QApplication>

#include "mainwindow.h"




int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow mainWindow;

    mainWindow.show();
    return app.exec();
}


//undo : Ctrl+z
//go foward : Ctrl+y
//comment processing : Ctrl+/
