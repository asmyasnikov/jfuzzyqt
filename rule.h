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
	Rule(QObject *parent=NULL);
	Rule(const Rule &rule);
	Rule(QObject *parent, QString name);
	~Rule();
	void addAntecedents(RuleExpression *antecedents);
	void addConsequent(RuleTerm* rt);
	const QString Rule::getName()const;
	RuleExpression* getAntecedents()const;
	const QList<RuleTerm*> getConsequents()const ;
	QString toQString() const;
	void setDegreeOfSupport(const double& degreeOfSupport);
	void reset();
	void evaluate (RuleActivationMethod* act,RuleAccumulationMethod* accu);
	double getWeight()const;

private:
	QString name;
	RuleExpression* antecedents;
	QList<RuleTerm*> consequents;
	double degreeOfSupport;
	double weight;
};

#endif // RULE_H
