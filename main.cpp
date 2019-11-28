#include <QApplication>

#include "mainwindow.h"




int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow mainWindow;

    mainWindow.show();
    return app.exec();
}

//lol
//undo : Ctrl+z
//go foward : Ctrl+y
//comment processing : Ctrl+/
