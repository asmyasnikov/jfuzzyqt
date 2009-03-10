#include "ruleaccumulationmethod.h"

RuleAccumulationMethod::RuleAccumulationMethod()
{

}

RuleAccumulationMethod::~RuleAccumulationMethod()
{

}

/**
* Aggregate a 'valueToAggregate' to a 'defuzzifierValue'  
* @param defuzzifierValue : defuzzifier's current value
* @param valueToAggregate : value to aggregate
* @return new defuzzifier's value
*/
double RuleAccumulationMethod::aggregate(double defuzzifierValue, double valueToAggregate)
{
return 0;
}

QString RuleAccumulationMethod::getName()
{
		return this->name;
}
void RuleAccumulationMethod::setName(QString name)
{
	this->name = name;
}

QString RuleAccumulationMethod::toStringFcl()
{
	return getName();
}