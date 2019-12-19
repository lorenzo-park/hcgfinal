#ifndef MATERIALCHOOSE_H
#define MATERIALCHOOSE_H

#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <string>

namespace Ui {
class materialChoose;
}

class materialChoose : public QWidget
{
    Q_OBJECT

public:
    explicit materialChoose(QWidget *parent = nullptr);
    ~materialChoose();
    QString material_text="-1";

private slots:
    void on_chooseBtn_clicked();

private:
    Ui::materialChoose *ui;
};

#endif // MATERIALCHOOSE_H
