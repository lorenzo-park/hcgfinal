#ifndef ADDLAYER_H
#define ADDLAYER_H

#include <QWidget>
#include <QListWidgetItem>
#include <list>
#include "glwidget.h"

namespace Ui {
class addlayer;
}

class addlayer : public QWidget
{
    Q_OBJECT

public:
    explicit addlayer(QWidget *parent = nullptr);
    ~addlayer();

    GLWidget* target;

    void addLayerItems(std::list<int> layers);
    void addLayerItem(int layerNum);
    std::list<int> getLayerItems();
    int getLayerItemsSize();
    void setCurrentLayerLabel();
    void updateListWidgetItems();

private slots:
    void on_chooseBtn_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::addlayer *ui;
};

#endif // ADDLAYER_H
