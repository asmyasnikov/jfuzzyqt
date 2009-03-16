#include "ruleterm.h"

RuleTerm::RuleTerm(QObject* parent) : QObject(parent)
{

}
RuleTerm::RuleTerm(QObject* parent, const RuleTerm &rt) : QObject(parent)
{
	this->variable = rt.getVariable();
	this->termName = rt.getName();
	this->negated = rt.isNegated();
}
RuleTerm::RuleTerm(QObject* parent, Variable* variable, QString term, bool negated) : QObject(parent)
{
	this->variable = variable;
	this->termName = term;
	this->negated = negated;
}
RuleTerm::RuleTerm(const RuleTerm &rt): QObject()
{
	this->variable = rt.getVariable();
	this->termName = rt.getName();
	this->negated = rt.isNegated();
}
RuleTerm::~RuleTerm()
{
}
const MembershipFunction* RuleTerm::getMembershipFunction()
{
	return this->variable->getMembershipFunction(this->termName);
}
QString RuleTerm::getName()const
{
	return this->termName;
}
void RuleTerm::setName(const QString &name)
{
	this->termName = name;
}
const bool RuleTerm::isNegated() const
{
	return this->negated;
}
Variable* RuleTerm::getVariable()const
{
	return this->variable;
}