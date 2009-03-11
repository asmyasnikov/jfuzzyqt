#ifndef FCLRULETREE_H
#define FCLRULETREE_H

#include <QObject>
#include <QObject>
#include <QString>
#include <QList>
#include "fclrulenode.h"

class FCLRuleTree : public QObject
{
public:
	FCLRuleTree(QObject *parent);
	~FCLRuleTree();
	void addExpression(QString exp);
	QString print();
private:
	FCLRuleNode* root;
	FCLRuleNode* insertNode(FCLRuleNode* root, FCLRuleNode* node);
	void insertNode(FCLRuleNode* node);
	void insertRight(FCLRuleNode* root, FCLRuleNode* node);
	void insertLeaveValues(QList<QString> &values);
};

#endif // FCLRULETREE_H
