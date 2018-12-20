#include "dialogaddgoods.h"
#include "ui_dialogaddgoods.h"
#include <QDebug>
#include <QMessageBox>
#include "TreeManagement.h"
#include <QTreeWidgetItem>

DialogAddGoods::DialogAddGoods(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddGoods)
{
    ui->setupUi(this);
}

DialogAddGoods::~DialogAddGoods()
{
    delete ui;
}

void DialogAddGoods::on_buttonCancel_clicked()
{
    this->close();
}

void DialogAddGoods::on_buttonAdd_clicked()
{
    if (ui->lineEdit->text().isEmpty() == false)  //edit control is empty?
    {
        int ans = ui->comboBox_Type->currentIndex(); //get value from ComboBox

        if (ans == TYPE)
        {
            QTreeWidgetItem * parent = new QTreeWidgetItem();
            parent->setText(0, ui->lineEdit->text());
            treeWidget->addTopLevelItem(parent);

            TreeManagement::Node * temp_node = treeManagement->AddRoot(ui->lineEdit->text(), parent); //add it to my database

            QVariant var; //add to database of treeWidget
            var.setValue(temp_node);
            parent->setData(0, Qt::UserRole, var);

            this->close(); //close the dialog window
        }
        else if (ans == SUBTYPE)
        {
            int index = ui->comboBox_SubType->currentIndex(); //get value from ComboBox

            if (treeWidget->topLevelItemCount()) //created top lvl?
            {
                QTreeWidgetItem * child = new QTreeWidgetItem();
                child->setText(0, ui->lineEdit->text());

                QTreeWidgetItem * parent = treeManagement->GetRoot(index); //get pointer to the parent (first layer of hierarchy)
                TreeManagement::Node * temp_node = treeManagement->AddSubRoot(ui->lineEdit->text(), child, treeManagement->GetRootNode(index));
                parent->addChild(child); //set the child to the parent

                //todо: найти и добавить способ записывать информацию (узлы) в объекты дерева
                this->close(); //close the dialog window
            }
            else
            {
                QMessageBox msgBox(QMessageBox::Critical, "Error!", "No rows are selected in the \"Type\" line", QMessageBox::Close, this);
                msgBox.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
                msgBox.exec();
            }
        }
        else if (ans == UNDERSUBTYPE)
        {
            int parent_index = ui->comboBox_SubType->currentIndex(); //get value from ComboBox
            int child_index = ui->comboBox_UnderSubType->currentIndex();

            if (child_index >= 0) //if something is selected
            {
                QTreeWidgetItem * child = new QTreeWidgetItem();
                child->setText(0, ui->lineEdit->text());

                QTreeWidgetItem * parent = treeManagement->GetSubRoot(treeManagement->GetRootNode(parent_index), child_index); //get pointer to the parent (second layer of hierarchy)

                TreeManagement::Node * parentRoot = treeManagement->GetRootNode(parent_index);
                TreeManagement::Node * subRoot = treeManagement->GetSubRootNode(parentRoot, child_index);
                TreeManagement::Node * temp_node = treeManagement->AddUnderSubRoot(ui->lineEdit->text(), child, subRoot);
                parent->addChild(child); //set the child to the parent

                //todо: найти и добавить способ записывать информацию (узлы) в объекты дерева
                this->close(); //close the dialog window
            }
            else
            {
                QMessageBox msgBox(QMessageBox::Critical, "Error!", "No rows are selected in the \"Type\" line", QMessageBox::Close, this);
                msgBox.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
                msgBox.exec();
            }
        }
    }
    else
    {
        QMessageBox msgBox(QMessageBox::Critical, "Data entry error", "Input field cannot be empty", QMessageBox::Close, this);
        msgBox.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
        msgBox.exec();
    }
}

void DialogAddGoods::on_comboBox_Type_activated(int index) // this func sets, what will be done if use comboBox_Type
{
    ui->comboBox_SubType->clear();
    ui->comboBox_UnderSubType->clear();

    if (index == 0)
    {
        ui->comboBox_SubType->setDisabled(true);
        ui->comboBox_UnderSubType->setDisabled(true);
    }
    else if (index == 1)
    {
        ui->comboBox_SubType->setDisabled(false);
        ui->comboBox_UnderSubType->setDisabled(true);

        QString temp;
        for (int i = 0; i < treeManagement->GetCountOfRoots(); i++) //write all first lvl into comboBox
        {
            temp = treeManagement->GetStringFromRoot(i);
            ui->comboBox_SubType->addItem(temp);
        }
    }
    else if (index == 2)
    {
        ui->comboBox_SubType->setDisabled(false);
        ui->comboBox_UnderSubType->setDisabled(false);

        QString temp;
        for (int i = 0; i < treeManagement->GetCountOfRoots(); i++) //write all first lvl into comboBox
        {
            temp = treeManagement->GetStringFromRoot(i);
            ui->comboBox_SubType->addItem(temp);
        }

        TreeManagement::Node * parent_node = treeManagement->GetRootNode(ui->comboBox_SubType->currentIndex());
        for (int i = 0; i < treeManagement->GetCountOfSubRoot(parent_node); i++) //write all second lvl into comboBox
        {
            temp = treeManagement->GetStringFromSubRoot(parent_node, i);
            ui->comboBox_UnderSubType->addItem(temp);
        }
    }
}

void DialogAddGoods::on_comboBox_SubType_activated(int index)
{
    ui->comboBox_UnderSubType->clear();

    if (ui->comboBox_Type->currentIndex() == UNDERSUBTYPE)
    {
        int index_of_parent = ui->comboBox_SubType->currentIndex();
        QTreeWidgetItem * parent = treeManagement->GetRoot(index_of_parent); //get pointer to the parent

        QString temp;
        for (int i = 0; i < parent->childCount(); i++) //write all second lvl into comboBox
        {
            temp = treeManagement->GetStringFromSubRoot(treeManagement->GetRootNode(index_of_parent), i);
            ui->comboBox_UnderSubType->addItem(temp);
        }
    }
}

//на чем я остановился...
//нужно сделать запись в базу ЭУ (элем. упр) среднего и нижнего слоев.
//проверить на работоспособность
//начать делать редактирование и удаление (п.с. попробуй использовать функции Qt для нахождения кол-ва детей, радителей и т.д.)
