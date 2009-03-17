#include "ruleconnectionmethod.h"
#include <QDebug>

RuleConnectionMethod::RuleConnectionMethod(QString name)
:QObject()
{
	this->name = name;
}

RuleConnectionMethod::~RuleConnectionMethod()
{

}
QString RuleConnectionMethod::getName() const
{
	return this->name;
}
void RuleConnectionMethod::setName(const QString name)
{
	this->name = name;
}
double RuleConnectionMethod::connect(double antecedent1, double antecedent2)
{
	qWarning()<< "[RuleConnectionMethod::connect]:Virtual method called";
	return 0;
}
QString RuleConnectionMethod::toQString() const
{
	qWarning() << "[RuleConnectionMethod::toQString]:Virtual method called";
	return "";
}