#ifndef MATERIALCHOOSE_H
#define MATERIALCHOOSE_H

#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>

namespace Ui {
class materialChoose;
}

class materialChoose : public QWidget
{
    Q_OBJECT

public:
    explicit materialChoose(QWidget *parent = nullptr);
    ~materialChoose();

private slots:
    void on_chooseBtn_clicked();

private:
    Ui::materialChoose *ui;
};

#endif // MATERIALCHOOSE_H
