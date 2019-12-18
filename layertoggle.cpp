#include "layertoggle.h"
#include "ui_layertoggle.h"
#include <QCheckBox>

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

void layerToggle::initialize(GLWidget* target)
{
    this->target = target;
    QVBoxLayout* box = new QVBoxLayout();
    for (auto layer : target->layers) {
        QCheckBox* checkbox = new QCheckBox();
        checkbox->setText(QString::number(layer));

        if (std::find(target->filteredLayers.begin(), target->filteredLayers.end(), layer) == target->filteredLayers.end()) {
            checkbox->setChecked(true);
        }

        cbxs.push_back(checkbox);

        box->addWidget(checkbox);
    }

    ui->verticalLayout->addLayout(box);
}

void layerToggle::on_pushButton_clicked()
{
    for (QCheckBox* checkbox : cbxs) {
        if (!checkbox->checkState()) {
            target->filteredLayers.push_back(checkbox->text().toInt());
        } else {
            if (std::find(target->filteredLayers.begin(), target->filteredLayers.end(), checkbox->text().toInt())
                    != target->filteredLayers.end()) {
                target->filteredLayers.remove(checkbox->text().toInt());
            }
        }
    }

    target->setReferenceWidgetData();
    target->update();
    cbxs.clear();
    this->close();
}
