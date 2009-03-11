#ifndef RULE_H
#define RULE_H

#include <QObject>
#include <QString>
#include <QLinkedList>
#include "ruleexpression.h"
#include "ruleterm.h"

class Rule : public QObject
{
public:
	Rule();
	Rule(const Rule &rule);
	Rule(QObject *parent, QString name);
	~Rule();
	void addAntecedents(RuleExpression *antecedents);
	void addConsequent(RuleTerm rt);
	const QString Rule::getName()const;
	RuleExpression* getAntecedents()const;
	const QLinkedList<RuleTerm> getConsequents()const ;
private:
	QString name;
	RuleExpression* antecedents;
	QLinkedList<RuleTerm> consequents;
};

#endif // RULE_H
