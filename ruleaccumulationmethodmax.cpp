#include "ruleaccumulationmethodmax.h"
#include <QtGlobal>

RuleAccumulationMethodMax::RuleAccumulationMethodMax(QObject *parent)
	: RuleAccumulationMethod(parent,"max")
{

}

RuleAccumulationMethodMax::~RuleAccumulationMethodMax()
{

}

double RuleAccumulationMethodMax::aggregate(double defuzzifierValue, double valueToAggregate) const
{
	return qMax(defuzzifierValue,valueToAggregate);
}

QString RuleAccumulationMethodMax::toQString()const
{
	return "ACCU : MAX;";
}