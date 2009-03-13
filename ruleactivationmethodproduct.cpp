#include "ruleactivationmethodproduct.h"

RuleActivationMethodProduct::RuleActivationMethodProduct(QObject *parent)
: RuleActivationMethod(parent,"product")
{

}

RuleActivationMethodProduct::~RuleActivationMethodProduct()
{

}
double RuleActivationMethodProduct::imply(double degreeOfSupport, double membership)const
{
	return degreeOfSupport * membership;
}