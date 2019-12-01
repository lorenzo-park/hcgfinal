/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "mainwindow.h"
#include "window.h"
#include <QMenuBar>
#include <QMenu>
#include <QMessageBox>
#include <QtWidgets>
#include <fstream>
#include <QString>
#include "glwidget.h"

MainWindow::MainWindow(){

    QMenuBar *menuBar = new QMenuBar;
    QMenu *menuWindow = menuBar->addMenu(tr("&File"));  //keyboard shortcut "Alt+F"
    setMenuBar(menuBar);
//    QAction *addNew = new QAction(menuWindow);
//    addNew->setText(tr("Add new"));
//    menuWindow->addAction(addNew);
//    connect(addNew, &QAction::triggered, this, &MainWindow::onAddNew);
//    onAddNew();
    QAction *newFile = new QAction(menuWindow);
    newFile->setText(tr("New File"));
    menuWindow->addAction(newFile);
    connect(newFile, &QAction::triggered, this, &MainWindow::onNewFile);
    onNewFile();
    QAction *saveFile = new QAction(menuWindow);
    saveFile->setText(tr("Save File"));
    menuWindow->addAction(saveFile);
    connect(saveFile, &QAction::triggered, this, &MainWindow::onSaveFile);
    onSaveFile();
    QAction *OpenFile = new QAction(menuWindow);
    OpenFile->setText(tr("Open File"));
    menuWindow->addAction(OpenFile);
    connect(OpenFile, &QAction::triggered, this, &MainWindow::onOpenFile);
   // onOpenFile();

    QString Filename; // this filename

}

void MainWindow::onAddNew(){
    if (!centralWidget()){
        display=new Window(this);
        setCentralWidget(display);
    }
    else
        QMessageBox::information(0, tr("Cannot add new window"), tr("Already occupied. Undock first."));
}
void MainWindow::onNewFile(){
    if (!centralWidget()){
        display=new Window(this);
        setCentralWidget(display);
    }


    qDebug("New Project handle");

    QString filters("Text file (*.txt)");
    QString dir = QFileDialog::getSaveFileName(this, "New Project File", QDir::currentPath(),filters);

    if(dir == ""){
        QMessageBox msg;
        msg.setText("Failed to create new file");
        msg.exec();
        return;
    }

    this->Filename = dir;
}

void MainWindow::onSaveFile(){
    // save file
    display->SaveFile(this->Filename);
}

void MainWindow::onOpenFile(){
    qDebug("Open Project handle");

    QString filters("Text file (*.txt);; OFF file (*.off)");

    QString dir = QFileDialog::getOpenFileName(this, "Open Directory", QDir::currentPath(),filters);

    if(dir == ""){
        QMessageBox msg;
        msg.setText("Failed to Open file");
        msg.exec();
        return;
    }

    display->LoadFile( dir );
    this->Filename = dir;
}
