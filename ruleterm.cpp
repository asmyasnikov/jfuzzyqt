#include "ruleterm.h"

RuleTerm::RuleTerm()
{

}

RuleTerm::~RuleTerm()
{

}

Variable* RuleTerm::getVariable()const
{
	return this->variable;
}
RuleTerm::RuleTerm(const RuleTerm &rt)
{
	this->variable = rt.getVariable();
	this->termName = rt.getName();
	this->negated = rt.isNegated();
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
QString RuleTerm::getName()const
{
	return this->termName;
}
const bool RuleTerm::isNegated() const
{
	return this->negated;
}