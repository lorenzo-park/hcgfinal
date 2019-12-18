#include "layertoggle.h"
#include "ui_layertoggle.h"

layerToggle::layerToggle(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::layerToggle)
{
    ui->setupUi(this);
}

layerToggle::~layerToggle()
{
    delete ui;
}
