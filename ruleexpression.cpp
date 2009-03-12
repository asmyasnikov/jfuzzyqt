#include "ruleexpression.h"
#include "RuleConnectionMethod.h"
#include "RuleTerm.h"
#include <QDebug>

RuleExpression::RuleExpression(QObject *parent)
	: QObject(parent)
{
	term1Type = UNDEF;
	term2Type = UNDEF;
}
RuleExpression::RuleExpression(const RuleExpression &re)
{
	this->negated = re.isNegated();
	switch ( re.isTerm1Type() )
	{ 
	case 0:///<RULETERM
		this->term1Type = RULETERM;	
		this->term1.ruleTerm = new RuleTerm(re.getTerm1Rule());
		this->term1.ruleTerm->setParent(this);
		break;
	case 1:///<RULEEXPRESSION
		this->term1Type = RULEEXPRESSION;	
		this->term1.ruleExpression = new RuleExpression( re.getTerm1Expression() );
		this->term1.ruleExpression->setParent(this);
		break;
	case 2:///<UNDEF
		this->term1Type = UNDEF;
		break;
	}

	switch ( re.isTerm2Type() )
	{ 
	case 0:///<RULETERM
		this->term2Type = RULETERM;	
		this->term2.ruleTerm = new RuleTerm(re.getTerm2Rule());
		this->term2.ruleTerm->setParent(this);
		break;
	case 1:///<RULEEXPRESSION
		this->term2Type = RULEEXPRESSION;	
		this->term2.ruleExpression = new RuleExpression( re.getTerm2Expression() );
		this->term2.ruleExpression->setParent(this);
		break;
	case 2:///<UNDEF
		this->term2Type = UNDEF;
		break;
	}
}
RuleExpression::~RuleExpression()
{
}
int RuleExpression::isTerm1Type()const
{
	return this->term1Type;
}
int RuleExpression::isTerm2Type()const
{	
	return this->term2Type;
}
RuleConnectionMethod* RuleExpression::getRuleConnectionMethod()const
{
	return this->ruleConnectionMethod;
}
bool RuleExpression::isNegated()const
{
	return this->negated;
}
RuleTerm* RuleExpression::getTerm1Rule()const
{
	if ( this->term1Type==RULETERM )
	{
		return this->term1.ruleTerm;
	}
	else
	{
		return NULL;
	}
}
RuleTerm* RuleExpression::getTerm2Rule()const
{
	if ( this->term2Type==RULETERM )
	{
		return this->term2.ruleTerm;
	}
	else
	{
		return NULL;
	}
}
RuleExpression* RuleExpression::getTerm1Expression()const
{
	if ( this->term1Type==RULEEXPRESSION )
	{
		return this->term1.ruleExpression;
	}
	else
	{
		return NULL;
	}
}
RuleExpression* RuleExpression::getTerm2Expression()const
{	
	if ( this->term2Type==RULEEXPRESSION )
	{
		return this->term2.ruleExpression;
	}
	else
	{
		return NULL;
	}
}
void RuleExpression::addTerm1Rule(RuleTerm *ruleTerm)
{
	this->term1Type = RULETERM;	
	this->term1.ruleTerm = ruleTerm;
	this->term1.ruleTerm->setParent(this);
}
void RuleExpression::addTerm2Rule(RuleTerm *ruleTerm)
{
	this->term2Type = RULETERM;	
	this->term2.ruleTerm = ruleTerm;
	this->term2.ruleTerm->setParent(this);
}
void RuleExpression::addTerm1Expression(RuleExpression *ruleExpression)
{
	this->term1Type = RULEEXPRESSION;	
	this->term1.ruleExpression = ruleExpression;
	this->term1.ruleExpression->setParent(this);
}
void RuleExpression::addTerm2Expression(RuleExpression *ruleExpression)
{
	this->term2Type = RULEEXPRESSION;	
	this->term2.ruleExpression = ruleExpression;
	this->term2.ruleExpression->setParent(this);
}
void RuleExpression::setRuleConnectionMethod(RuleConnectionMethod* ruleConnectionMethod)
{
	this->ruleConnectionMethod = ruleConnectionMethod;
}