#ifndef RULE_H
#define RULE_H

#include <QString>
#include <QLinkedList>
#include "ruleexpression.h"
#include "ruleterm.h"

class Rule
{
public:
	Rule(QString name);
	~Rule();
	void addAntecedents(RuleExpression antecedents);
	void addConsequent(RuleTerm rt);
private:
	QString name;
	RuleExpression antecedents;
	QLinkedList<RuleTerm> consequents;
};

#endif // RULE_H
