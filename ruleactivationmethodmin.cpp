#include "ruleactivationmethodmin.h"
#include <QtGlobal>

RuleActivationMethodMin::RuleActivationMethodMin(QObject *parent)
	: RuleActivationMethod(parent,"min")
{

}

RuleActivationMethodMin::~RuleActivationMethodMin()
{

}
double RuleActivationMethodMin::imply(double degreeOfSupport, double membership)const
{
	return qMin(degreeOfSupport, membership);
}