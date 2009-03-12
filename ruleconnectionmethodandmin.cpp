#include "ruleconnectionmethodandmin.h"
#include <QtGlobal>

RuleConnectionMethodAndMin::RuleConnectionMethodAndMin() : RuleConnectionMethod("and")
{

}

RuleConnectionMethodAndMin::~RuleConnectionMethodAndMin()
{

}
double RuleConnectionMethodAndMin::connect(double antecedent1, double antecedent2)
{
	return qMin(antecedent1, antecedent2);
}
QString RuleConnectionMethodAndMin::toQString() const
{
	return "AND : MIN";
}