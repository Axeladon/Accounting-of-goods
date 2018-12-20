#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    treeManagement = new TreeManagement();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonAdd_clicked()
{
  DialogAddGoods dlg_AddGoods;
  dlg_AddGoods.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::MSWindowsFixedSizeDialogHint);
  dlg_AddGoods.SetPointerToTreeWidget(ui->treeWidget);
  dlg_AddGoods.SetPointerToDatabase(this->treeManagement);
  //dlg.setParent(this, Qt::Window | Qt::WindowSystemMenuHint | Qt::MSWindowsFixedSizeDialogHint);
  dlg_AddGoods.exec();
}

void MainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    QVariant var = item->data(column, Qt::UserRole); //to get the data from element of treewidget
    TreeManagement::Node * result = var.value<TreeManagement::Node *>(); //convert the data from QVariant to Node
}
