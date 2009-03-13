#ifndef RULEACTIVATIONMETHODPRODUCT_H
#define RULEACTIVATIONMETHODPRODUCT_H

#include "ruleactivationmethod.h"
#include <QObject>

class RuleActivationMethodProduct : public RuleActivationMethod
{
public:
	RuleActivationMethodProduct(QObject *parent);
	~RuleActivationMethodProduct();
	double imply(double degreeOfSupport, double membership)const;
private:
	
};

#endif // RULEACTIVATIONMETHODPRODUCT_H
