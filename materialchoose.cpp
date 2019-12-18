#include "materialchoose.h"
#include "ui_materialchoose.h"
#include <QListWidget>
#include <QListWidgetItem>

materialChoose::materialChoose(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::materialChoose)
{
    ui->setupUi(this);

}

materialChoose::~materialChoose()
{
    delete ui;
}

void materialChoose::on_chooseBtn_clicked()
{

}
