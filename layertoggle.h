#ifndef LAYERTOGGLE_H
#define LAYERTOGGLE_H

#include <QWidget>
#include <QCheckBox>
#include "glwidget.h"

namespace Ui {
class layerToggle;
}

class layerToggle : public QWidget
{
    Q_OBJECT

public:
    explicit layerToggle(QWidget *parent = nullptr);
    ~layerToggle();

    GLWidget* target;
    std::list<QCheckBox*> cbxs;

    void updateWithFilter(std::list<int> filtered);
    void initialize(GLWidget* target);

private slots:
    void on_pushButton_clicked();

private:
    Ui::layerToggle *ui;
};

#endif // LAYERTOGGLE_H
