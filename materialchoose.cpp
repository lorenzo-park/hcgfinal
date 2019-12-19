#include "materialchoose.h"
#include "ui_materialchoose.h"
#include <QListWidget>
#include <QListWidgetItem>
#include <QMessageBox>

materialChoose::materialChoose(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::materialChoose)
{
    ui->setupUi(this);
    ui->listWidget->addItem("nwell");
    ui->listWidget->addItem("pwell");
    ui->listWidget->addItem("nselect");
    ui->listWidget->addItem("pselect");
    ui->listWidget->addItem("nactive");
    ui->listWidget->addItem("pactive");
    ui->listWidget->addItem("poly");
    ui->listWidget->addItem("contact");
    ui->listWidget->addItem("metal");

}

materialChoose::~materialChoose()
{
    delete ui;
}

void materialChoose::on_chooseBtn_clicked()
{
    QMessageBox::information(this, "title", ui->listWidget->currentItem()->text());
    material_text = ui->listWidget->currentItem()->text();
    this->close();
}
