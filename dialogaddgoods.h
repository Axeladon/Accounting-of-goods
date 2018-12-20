#ifndef DIALOGADDGOODS_H
#define DIALOGADDGOODS_H

#include <QDialog>
#include <QTreeWidget>
#include "TreeManagement.h"

namespace Ui {
class DialogAddGoods;
}

class DialogAddGoods : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddGoods(QWidget *parent = nullptr);
    ~DialogAddGoods();

    void SetPointerToTreeWidget(QTreeWidget * treeWidget) { this->treeWidget = treeWidget; }
    void SetPointerToDatabase(TreeManagement * treeManagement) {this->treeManagement = treeManagement; }

private slots:
    void on_buttonCancel_clicked();
    void on_buttonAdd_clicked();

    void on_comboBox_Type_activated(int index);
    void on_comboBox_SubType_activated(int index);

private:
    Ui::DialogAddGoods *ui;
    QTreeWidget * treeWidget;

    TreeManagement * treeManagement;
};

#endif // DIALOGADDGOODS_H
