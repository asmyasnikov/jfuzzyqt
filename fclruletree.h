#ifndef FCLRULETREE_H
#define FCLRULETREE_H

#include <QObject>
#include <QObject>
#include <QString>
#include <QList>
#include "fclrulenode.h"
#include "ruleexpression.h"

class FCLRuleTree : public QObject
{
public:
	FCLRuleTree(QObject *parent);
	~FCLRuleTree();
	void addExpression(QString exp);
	QString print()const;
	RuleExpression getRuleExpression(RuleConnectionMethod *and, RuleConnectionMethod *or)const;
private:
	FCLRuleNode* root;
	FCLRuleNode* insertNode(FCLRuleNode* root, FCLRuleNode* node);
	void insertNode(FCLRuleNode* node);
	void insertRight(FCLRuleNode* root, FCLRuleNode* node);
	void insertLeaveValues(QList<QString> &values);
};

#endif // FCLRULETREE_H
