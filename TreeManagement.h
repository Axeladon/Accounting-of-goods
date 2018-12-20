#ifndef TREE_MANAGEMENT
#define TREE_MANAGEMENT

//#include "Database_of_Goods.h"
#include <QApplication>
#include <QTreeWidgetItem>
#include <QComboBox>

#define TYPE 0
#define SUBTYPE 1
#define UNDERSUBTYPE 2

class TreeManagement
{
public:
	struct Node
	{
        QString name;
        QTreeWidgetItem * m_hRoot;
		short type;
		struct Node * previous;
		struct Node * subhierarchy;
		struct Node * next;
        //DatabaseOfGoods database;
	};
private:
	Node * first;
    Node * last;
public:
	TreeManagement();
	~TreeManagement();
    Node * AddRoot(QString str, QTreeWidgetItem * hRoot);
    Node * AddSubRoot(QString str, QTreeWidgetItem * hSubRoot, Node * parent_root);
    Node * AddUnderSubRoot(QString str, QTreeWidgetItem * hSubRoot, Node * subRoot);
    QString GetStringFromRoot(int index) const;
    QString GetStringFromSubRoot(Node * parent_root, int index) const;
    QTreeWidgetItem * GetRoot(int num) const;
    QTreeWidgetItem * GetSubRoot(Node * parent_root, int index) const;
    //void ChangeName(DWORD_PTR dword_ptr, QString str);
	void SetFirstNode(Node * frst = nullptr ); //set into pointers zero value
	void SetLastNode(Node * last = nullptr);
    int GetCountOfRoots() const;
    int GetCountOfSubRoot(Node * parent_root) const;
    Node * GetRootNode(int index) const;
    Node * GetSubRootNode(Node * parent_root, int index) const;
};

inline TreeManagement::TreeManagement()
{
    first = last = nullptr;
}

Q_DECLARE_METATYPE(TreeManagement::Node *)
#endif
