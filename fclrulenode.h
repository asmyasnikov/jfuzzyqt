#ifndef FCLRULENODE_H
#define FCLRULENODE_H

#include <QString>
#include <QObject>
#include "ruleexpression.h"
#include "ruleterm.h"
#include "ruleconnectionmethod.h"
#include "ruleconnectionmethodandmin.h"
#include "ruleconnectionmethodormax.h"

class FCLRuleNode : public QObject
{
public:
	FCLRuleNode(QObject *parent, QString oper);
	~FCLRuleNode();
	bool isPriorThen(int priority);
	int getPriority();
	void setLeft(FCLRuleNode* node);
	bool hasRightMember();
	FCLRuleNode* getRight();
	void setRight(FCLRuleNode* node);
	QString print()const;
	void insertLeaveValues(QList<QString> &values);
	const QString getOperator()const;
	RuleExpression toRuleExpression(RuleConnectionMethod *and, RuleConnectionMethod *or)const;
	RuleTerm toRuleTerm()const;

private:
	int priority;
	QString value1;
	QString value2;
	QString oper;
	FCLRuleNode* left;
	FCLRuleNode* right;
};

#endif // FCLRULENODE_H
