#include "TreeManagement.h"

TreeManagement::Node * TreeManagement::AddRoot(QString str, QTreeWidgetItem * hRoot)
{
	Node * created = new Node;
	created->name = str;
	created->m_hRoot = hRoot;
	created->type = TYPE;
	created->previous = nullptr;
	created->subhierarchy = nullptr;
	created->next = nullptr;

	if (first == nullptr)
		first = created;
	else
	{
		last->next = created;
		Node * temp = last->next;
		temp->previous = last;
	}
	last = created;
	return created;
}

QString TreeManagement::GetStringFromRoot(int index) const
{
	Node * temp = first;
    for (int i = 0; i < index; i++)
		temp = temp->next;
    return temp->name;
}

QString TreeManagement::GetStringFromSubRoot(Node * parent_root, int index) const
{
    Node * temp = parent_root->subhierarchy;

    for (int i = 0; i < index; i++)
        temp = temp->next;
    return temp->name;
}

QTreeWidgetItem * TreeManagement::GetRoot(int num) const
{
	Node * temp = first;
	for (int i = 0; i < num; i++)
		temp = temp->next;
    QTreeWidgetItem * htreeitem = temp->m_hRoot;
    return htreeitem;
}

QTreeWidgetItem * TreeManagement::GetSubRoot(Node * parent_root, int index) const
{
    Node * temp = parent_root->subhierarchy;

    for (int j = 0; j < index; j++)
        temp = temp->next;
    //QTreeWidgetItem * htreeitem = temp->m_hRoot;
    return temp->m_hRoot;;
}

TreeManagement::Node * TreeManagement::AddSubRoot(QString str, QTreeWidgetItem * hSubRoot, Node * parent_root)
{
	Node * created = new Node;
	created->name = str;
	created->m_hRoot = hSubRoot;
	created->type = SUBTYPE;
	created->previous = nullptr;
	created->subhierarchy = nullptr;
	created->next = nullptr;
	
    Node * pointer = parent_root;

    if (pointer->subhierarchy == nullptr)
	{
		pointer->subhierarchy = created;

		Node * temp = pointer->subhierarchy;
		temp->previous = pointer;
	}
	else
	{
		pointer = pointer->subhierarchy; 
        while (true) //looking for a last child
		{
			if (pointer->next != nullptr)
				pointer = pointer->next;
			else
			{
				pointer->next = created;

				Node * temp = pointer->next;
				temp->previous = pointer;
				break;
			}
		}
	}
	return created;
}

TreeManagement::Node * TreeManagement::AddUnderSubRoot(QString str, QTreeWidgetItem * hSubRoot, Node * subRoot)
{
	Node * created = new Node;
	created->name = str;
	created->m_hRoot = hSubRoot;
	created->type = UNDERSUBTYPE;
	created->previous = nullptr;
	created->subhierarchy = nullptr;
	created->next = nullptr;

    Node * pointer = subRoot;

	if (pointer->subhierarchy == nullptr)
	{
		pointer->subhierarchy = created;

        Node * temp = pointer->subhierarchy; //to add this address to previous block
		temp->previous = pointer;
	}
	else
	{
		pointer = pointer->subhierarchy;
		while (pointer->next != nullptr)
		{
			pointer = pointer->next;
		}
		pointer->next = created;

        Node * temp = pointer->next; //to add this address to next block
		temp->previous = pointer;
	}
	return created;
}

/*void TreeManagement::ChangeName(DWORD_PTR dword_ptr, CString str)
{
	Node * node_ptr = reinterpret_cast<Node *>(dword_ptr);
	node_ptr->name = str;
}*/

void TreeManagement::SetFirstNode(Node * frist)
{
    first = frist;
}

void TreeManagement::SetLastNode(Node * last)
{
	this->last = last;
}

int TreeManagement::GetCountOfRoots() const
{
    if (first == nullptr)
        return 0;
    else
    {
        int count = 1; //at least one already exists
        Node * temp = first;
        while (temp->next != nullptr)
        {
            temp = temp->next;
            count++;
        }
        return count;
    }
}

int TreeManagement::GetCountOfSubRoot(Node * parent_root) const
{
    if (parent_root == nullptr)
        return 0;
    if (parent_root->subhierarchy == nullptr)
        return 0;
    else
    {
        int count = 1; //at least one already exists
        Node * temp = parent_root->subhierarchy;
        while (temp->next != nullptr)
        {
            temp = temp->next;
            count++;
        }
        return count;
    }
}

TreeManagement::Node * TreeManagement::GetRootNode(int index) const
{
    Node * temp = first;
    for (int i = 0; i < index; i++)
       temp = temp->next;
    return temp;
}

TreeManagement::Node * TreeManagement::GetSubRootNode(Node * parent_root, int index) const
{
    Node * temp = parent_root->subhierarchy;
    for (int i = 0; i < index; i++)
       temp = temp->next;
    return temp;
}
