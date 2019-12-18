#include "materialchoose.h"
#include "ui_materialchoose.h"
#include <QListWidget>
#include <QListWidgetItem>

materialChoose::materialChoose(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::materialChoose)
{
    ui->setupUi(this);
    ui->listWidget->addItem("poly");
    ui->listWidget->addItem("metal");
    ui->listWidget->addItem("n-diffuse");
}

materialChoose::~materialChoose()
{
    delete ui;
}

void materialChoose::on_chooseBtn_clicked()
{

}
