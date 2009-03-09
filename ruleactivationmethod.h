#ifndef RULEACTIVATIONMETHOD_H
#define RULEACTIVATIONMETHOD_H

#include <QString>
#include "RuleTerm.h"
#include "RuleAccumulationMethod.h"

class RuleActivationMethod
{
public:
	RuleActivationMethod();
	~RuleActivationMethod();
	virtual double RuleActivationMethod::imply(double degreeOfSupport, double membership);
	void setName(QString name);
	void RuleActivationMethod::imply(RuleTerm fuzzyRuleTerm, RuleAccumulationMethod ruleAccumulationMethod, double degreeOfSupport);
private:
	QString name;
};

#endif // RULEACTIVATIONMETHOD_H
