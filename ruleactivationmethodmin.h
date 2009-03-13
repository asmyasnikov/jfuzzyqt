#ifndef RULEACTIVATIONMETHODMIN_H
#define RULEACTIVATIONMETHODMIN_H

#include "ruleactivationmethod.h"
#include <QObject>

class RuleActivationMethodMin : public RuleActivationMethod
{
public:
	RuleActivationMethodMin(QObject *parent);
	~RuleActivationMethodMin();
	double imply(double degreeOfSupport, double membership)const;
private:
	
};

#endif // RULEACTIVATIONMETHODMIN_H
