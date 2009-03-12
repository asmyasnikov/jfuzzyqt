#include "ruleconnectionmethodormax.h"
#include <QtGlobal>

RuleConnectionMethodOrMax::RuleConnectionMethodOrMax() : RuleConnectionMethod("or")
{

}

RuleConnectionMethodOrMax::~RuleConnectionMethodOrMax()
{

}
double RuleConnectionMethodOrMax::connect(double antecedent1, double antecedent2)
{
	return qMax(antecedent1, antecedent2);
}

QString RuleConnectionMethodOrMax::toStringFcl()const
{
	return "OR: MAX";
}