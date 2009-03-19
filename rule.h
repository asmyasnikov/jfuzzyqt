#ifndef RULE_H
#define RULE_H

#include "ruleexpression.h"
#include "ruleterm.h"
#include "ruleaccumulationmethod.h"
#include "ruleactivationmethod.h"
#include <QObject>
#include <QString>
#include <QLinkedList>

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
	QString toQString() const;
	void setDegreeOfSupport(const double& degreeOfSupport);
	void reset();
	void evaluate (RuleActivationMethod& act,RuleAccumulationMethod& accu);

private:
	QString name;
	RuleExpression* antecedents;
	QLinkedList<RuleTerm> consequents;
	double degreeOfSupport;
};

#endif // RULE_H
