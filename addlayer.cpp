#include "addlayer.h"
#include "ui_addlayer.h"
#include <QCoreApplication>

addlayer::addlayer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addlayer)
{
    ui->setupUi(this);
}

addlayer::~addlayer()
{
    delete ui;
}

int addlayer::getLayerItemsSize()
{
    return target->layers.size();
}

void addlayer::on_chooseBtn_clicked()
{
    if (target->layers.size() == 0) {
        target->layers.push_back(1);
    } else {
        target->layers.push_back(target->layers.back() + 1);
    }
    updateListWidgetItems();
}

void addlayer::setCurrentLayerLabel()
{
    ui->label->setText("Layer " + QString::number(target->currentLayer));
}

void addlayer::updateListWidgetItems()
{
    ui -> listWidget->clear();
    for (auto layer : target->layers) {
        ui->listWidget->addItem(QString::number(layer));
    }

    setCurrentLayerLabel();
}

void addlayer::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    target->currentLayer = item->text().toInt();
    this->close();
}
