#include "ruleaccumulationmethod.h"

RuleAccumulationMethod::RuleAccumulationMethod(QObject* parent)
: QObject(parent)
{
	this->name = "Undefined";
}
RuleAccumulationMethod::RuleAccumulationMethod(QObject* parent, QString name)
: QObject(parent)
{
	this->name = name;
}
RuleAccumulationMethod::RuleAccumulationMethod(const RuleAccumulationMethod &ram)
: QObject()
{
	this->name=ram.getName();
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
double RuleAccumulationMethod::aggregate(double defuzzifierValue, double valueToAggregate)const
{
return 0;
}

QString RuleAccumulationMethod::getName()const
{
		return this->name;
}
void RuleAccumulationMethod::setName(const QString &name)
{
	this->name = name;
}

QString RuleAccumulationMethod::toQString()const
{
	return getName();
}