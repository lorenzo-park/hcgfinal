#ifndef LAYERTOGGLE_H
#define LAYERTOGGLE_H

#include <QWidget>

namespace Ui {
class layerToggle;
}

class layerToggle : public QWidget
{
    Q_OBJECT

public:
    explicit layerToggle(QWidget *parent = nullptr);
    ~layerToggle();

private:
    Ui::layerToggle *ui;
};

#endif // LAYERTOGGLE_H
