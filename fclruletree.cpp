#include "fclruletree.h"
#include <QDebug>
#include <QRegExp>

FCLRuleTree::FCLRuleTree(QObject *parent)
	: QObject(parent)
{
	this->root = NULL;
}

FCLRuleTree::~FCLRuleTree()
{

}

void FCLRuleTree::insertNode(FCLRuleNode* node)
{
	node->setParent(this);
	
	if (root == NULL)
	{
		this->root = node;
		qDebug() << "[FCLRuleTree::insertNode1]:Insert root";
	}else
	{
		qDebug() << "[FCLRuleTree::insertNode1]:Insert leave";
		this->root = insertNode(this->root, node);
	}
}
FCLRuleNode* FCLRuleTree::insertNode(FCLRuleNode* root, FCLRuleNode* node)
{
	if(node->isPriorThen( root->getPriority()))
	{
		qDebug() << "[FCLRuleTree::insertNode2]:Insert right";
		insertRight(root, node);
		return root;
	}else
	{
		qDebug() << "[FCLRuleTree::insertNode2]:Insert root";
		//insere na raiz
		node->setLeft(root);
		return node;
	}
}
void FCLRuleTree::insertRight(FCLRuleNode* root, FCLRuleNode* node)
{
	if ( root->hasRightMember() )
	{
		qDebug() << "[FCLRuleTree::insertRight]:Insert right";
		insertRight(root->getRight(), node);
	}else
	{
		qDebug() << "[FCLRuleTree::insertRight]:Inserted";
		root->setRight(node);
	}
}

QString FCLRuleTree::print()
{
	return root->print();
}
void FCLRuleTree::insertLeaveValues(QList<QString> &values)
{
	return root->insertLeaveValues(values);
}
void FCLRuleTree::addExpression(QString exp)
{
	QList<QString> list;
	QRegExp rx("(and|or)");
	QRegExp rxMember("(\\w+)\\s+(is not|is)\\s+(\\w+)");
	int pos = 0;

	while ((pos = rx.indexIn(exp, pos)) != -1) {
		qDebug() << rx.cap(1);
		this->insertNode( new FCLRuleNode(this, rx.cap(1) ) );
		//list.append( rx.cap(1) );
		pos += rx.matchedLength();
	}

	pos = 0;
	while ((pos = rxMember.indexIn(exp, pos)) != -1) {
		//qDebug() << rx.cap(0);
		list.append( rxMember.cap(0) );
		pos += rxMember.matchedLength();
	}
	this->insertLeaveValues(list);
	//"\\s*(\\w+)\\s+(is|is not)\\s+(\\w+)\\s+(and|or)"
}