#include "ruleterm.h"

RuleTerm::RuleTerm()
{

}

RuleTerm::~RuleTerm()
{

}

Variable* RuleTerm::getVariable()
{
	return this->variable;
}
RuleTerm::RuleTerm(Variable* variable, QString term, bool negated)
{
	this->variable = variable;
	this->termName = term;
	this->negated = negated;
}
const MembershipFunction* RuleTerm::getMembershipFunction()
{
	return this->variable->getMembershipFunction(this->termName);
}
QString RuleTerm::getName()
{
	return this->termName;
}
const bool RuleTerm::isNegated() const
{
	return this->negated;
}