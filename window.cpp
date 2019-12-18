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

#include "glwidget.h"
#include "window.h"
#include "mainwindow.h"
#include "materialchoose.h"
#include "layertoggle.h"
#include "addlayer.h"
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QPushButton>
#include <QDesktopWidget>
#include <QApplication>
#include <QMessageBox>

QString buildPath = "../hcgfinal/images/";

Window::Window(MainWindow *mw)
    : mainWindow(mw)
{
    // For design screen
    glWidget2D = new GLWidget;
    glWidget2D->setScale(10);
    glWidget2D->enableTranslation(false);

    // For viewer screen
    glWidget3D = new GLWidget(this->glWidget2D);
    glWidget3D->enableViewerMode(true);

    glWidget2D->setReferenceWidget(glWidget3D);

    glWidget3D->setXRotation(115*16);
    glWidget3D->setScale(2);
    glWidget3D->enableTranslation(true);


    selectBtn = new QPushButton;
    selectBtn->setStyleSheet("QPushButton { background-color: rgb(0,0,255,50) } QPushButton:hover { background-color: rgb(0,0,255,30) } QPushButton:pressed{ background-color: rgb(0,0,255,70); }");
    selectBtn->setIcon(QIcon(buildPath+"selectingBtnIcon2.png"));
    selectBtn->setIconSize(QSize(50,50));
    selectBtn->setFixedSize(QSize(60,60));
    connect(selectBtn, &QPushButton::clicked, this, &Window::select);

    subBlockColorBtn = new QPushButton;
    subBlockColorBtn->setStyleSheet("QPushButton { background-color: rgb(0,0,255,50) } QPushButton:hover { background-color: rgb(0,0,255,30) } QPushButton:pressed{ background-color: rgb(0,0,255,70); }");
    subBlockColorBtn->setIcon(QIcon(buildPath+"subblockcolorBtnicon.png"));
    subBlockColorBtn->setIconSize(QSize(80,80));
    subBlockColorBtn->setFixedSize(QSize(60,60));
    connect(subBlockColorBtn, &QPushButton::clicked, this, &Window::subBlockColor);

    addBlockBtn = new QPushButton;
    addBlockBtn->setStyleSheet("QPushButton { background-color:  rgb(0,0,255,50) } QPushButton:hover { background-color: rgb(0,0,255,30) } QPushButton:pressed{ background-color: rgb(0,0,255,70); }");
    addBlockBtn->setIcon(QIcon(buildPath+"addblockBtnicon.png"));
    addBlockBtn->setIconSize(QSize(100,100));
    addBlockBtn->setFixedSize(QSize(60,60));
    connect(addBlockBtn, &QPushButton::clicked, this, &Window::addBlock);

    deleteBlockBtn = new QPushButton;
    deleteBlockBtn->setStyleSheet("QPushButton { background-color:  rgb(0,0,255,50) } QPushButton:hover { background-color: rgb(0,0,255,30) } QPushButton:pressed{ background-color: rgb(0,0,255,70); }");
    deleteBlockBtn->setIcon(QIcon(buildPath+"deleteblockBtnicon.png"));
    deleteBlockBtn->setIconSize(QSize(80,80));
    deleteBlockBtn->setFixedSize(QSize(60,60));
    connect(deleteBlockBtn, &QPushButton::clicked, this, &Window::deleteBlock);

    addLayerBtn =  new QPushButton;
    addLayerBtn->setStyleSheet("QPushButton { background-color:  rgb(0,0,255,50) } QPushButton:hover { background-color: rgb(0,0,255,30) } QPushButton:pressed{ background-color: rgb(0,0,255,70); }");
    addLayerBtn->setIcon(QIcon(buildPath+"addlayerBtnicon.png"));
    addLayerBtn->setIconSize(QSize(50,50));
    addLayerBtn->setFixedSize(QSize(60,60));
    connect(addLayerBtn, &QPushButton::clicked, this, &Window::addLayer);

    layerToggleBtn = new QPushButton;
    layerToggleBtn->setStyleSheet("QPushButton { background-color:  rgb(0,0,255,50) } QPushButton:hover { background-color: rgb(0,0,255,30) } QPushButton:pressed{ background-color: rgb(0,0,255,70); }");
    layerToggleBtn->setIcon(QIcon(buildPath+"layertoggleBtnicon.png"));
    layerToggleBtn->setIconSize(QSize(50,50));
    layerToggleBtn->setFixedSize(QSize(60,60));
    connect(layerToggleBtn, &QPushButton::clicked, this, &Window::LayerToggle);

    addSubblockBtn = new QPushButton;
    addSubblockBtn->setStyleSheet("QPushButton { background-color:  rgb(0,0,255,50) } QPushButton:hover { background-color: rgb(0,0,255,30) } QPushButton:pressed{ background-color: rgb(0,0,255,70); }");
    addSubblockBtn->setIcon(QIcon(buildPath+"addsubblockBtn.png"));
    addSubblockBtn->setIconSize(QSize(50,50));
    addSubblockBtn->setFixedSize(QSize(60,60));
    connect(addSubblockBtn, &QPushButton::clicked, this, &Window::addSubblock);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    QVBoxLayout *buttonLayout = new QVBoxLayout;
    QHBoxLayout *glLayout = new QHBoxLayout;

    buttonLayout->addWidget(selectBtn);
    buttonLayout->addWidget(subBlockColorBtn);
    buttonLayout->addWidget(addBlockBtn);
    buttonLayout->addWidget(deleteBlockBtn);
    buttonLayout->addWidget(addLayerBtn);
    buttonLayout->addWidget(layerToggleBtn);
    buttonLayout->addWidget(addSubblockBtn);

    glLayout->addWidget(glWidget2D);
    glLayout->addWidget(glWidget3D);

    mainLayout->addLayout(buttonLayout);
    mainLayout->addLayout(glLayout);
    setLayout(mainLayout);

    QPalette pal = this->palette();
    // set white background
    pal.setColor(QPalette::Background, QColor(255,255,255));
    this->setAutoFillBackground(true);
    this->setPalette(pal);


}

QSlider *Window::createSlider()
{
    QSlider *slider = new QSlider(Qt::Vertical);
    slider->setRange(0, 360 * 16);
    slider->setSingleStep(16);
    slider->setPageStep(15 * 16);
    slider->setTickInterval(15 * 16);
    slider->setTickPosition(QSlider::TicksRight);
    return slider;
}

void Window::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
        close();
    else
        QWidget::keyPressEvent(e);
}

void Window::SaveFile(QString Filename) {

    glWidget2D->SaveFile( Filename );

}

void Window::LoadFile(QString Filename) {

    ResetMaterial();

    glWidget2D->LoadFile( Filename );
    glWidget3D->LoadFile( Filename );

}



void Window::select(){

}

void Window::subBlockColor(){

}

void Window::addBlock(){
    materialChoose* materialchoose = new materialChoose();
    materialchoose->show();

    if (glWidget2D->getEditMode() == ADD_MODE)
        glWidget2D->setEditMode(DEFAULT_MODE);
    else
        glWidget2D->setEditMode(ADD_MODE);
}

void Window::deleteBlock(){
    if (glWidget2D->getEditMode() == DELETE_MODE)
        glWidget2D->setEditMode(DEFAULT_MODE);
    else
        glWidget2D->setEditMode(DELETE_MODE);
}

void Window::addLayer(){
    addlayer* al = new addlayer();
    al->target = glWidget2D;
    al->updateListWidgetItems();
    al->show();
}

void Window::LayerToggle(){
    layerToggle* layertoggle = new layerToggle();
    layertoggle->initialize(glWidget2D);

    layertoggle->show();
}

void Window::addSubblock(){

}
void Window::ResetMaterial() {
    glWidget2D->Reset();
    glWidget3D->Reset();

}
