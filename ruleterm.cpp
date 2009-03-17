#include "ruleterm.h"

RuleTerm::RuleTerm(QObject* parent) : QObject(parent)
{
	this->variable = NULL;
	this->termName = "Undefined";
	this->negated = false;
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
void RuleTerm::setNegated(const bool& value)
{
	this->negated = value;
}

Variable* RuleTerm::getVariable()const
{
	return this->variable;
}
void RuleTerm::setVariable(Variable* variable)
{
	this->variable = variable;
}

QString RuleTerm::toQString()const
{
	QString str = "";
	if ( variable != NULL )
	{
		str += this->variable->getName();
	}
	else
	{
		str += "Null variable";
	}
	if ( this->negated )
	{
		str += " IS NOT ";
	}
	else
	{
		str += " IS ";
	}

	str += this->getName();
	return str;
}
RuleTerm RuleTerm::operator=(const RuleTerm &rt)
{
	RuleTerm tmp(rt);
	return tmp;
}