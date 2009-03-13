#ifndef RULEACTIVATIONMETHOD_H
#define RULEACTIVATIONMETHOD_H

#include "ruleterm.h"
#include "ruleaccumulationmethod.h"
#include <QObject>
#include <QString>

class RuleActivationMethod : public QObject
{
public:
	RuleActivationMethod(QObject *parent,QString name="");
	RuleActivationMethod(const RuleActivationMethod &ram);
	~RuleActivationMethod();
	virtual double imply(double degreeOfSupport, double membership)const;
	void setName(QString name);
	QString getName()const;
	void RuleActivationMethod::imply(RuleTerm fuzzyRuleTerm, RuleAccumulationMethod ruleAccumulationMethod, double degreeOfSupport);
	QString toQString()const;
private:
	QString name;
};

#endif // RULEACTIVATIONMETHOD_H
