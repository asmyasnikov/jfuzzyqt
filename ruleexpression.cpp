#include "ruleexpression.h"
#include "ruleconnectionmethod.h"
#include "ruleterm.h"
#include <QDebug>

RuleExpression::RuleExpression(QObject *parent)
	: QObject(parent)
{
	term1Type = UNDEF;
	term2Type = UNDEF;
	this->negated = false;
}

RuleExpression::~RuleExpression()
{
}

RuleExpression::term_t RuleExpression::getTerm1Type()const
{
	return this->term1Type;
}

RuleExpression::term_t RuleExpression::getTerm2Type()const
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
		qCritical() << "[RuleExpression::getTerm1Rule]:Null term returned";
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
		qCritical() << "[RuleExpression::getTerm2Rule]:Null term returned";
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
		qCritical() << "[RuleExpression::getTerm1Expression]:Null term returned";
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
		qCritical() << "[RuleExpression::getTerm2Expression]:Null term returned";
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

QString RuleExpression::toQString()const
{
	QString str = "(";
	switch (term1Type)
	{
		case RULETERM:
			str += term1.ruleTerm->toQString();
			break;
		case RULEEXPRESSION:
			str += term1.ruleExpression->toQString();
			break;
		case UNDEF:
			str += "UNDEFINED";
			break;
	}
	
	str += " (" ;
	if (this->ruleConnectionMethod != NULL )
	{
		str += this->ruleConnectionMethod->toQString();
	}
	else
	{
		str += "Invalid Rule Connection Method";
	}
	str += ") " ;
	
	switch (term2Type)
	{
		case RULETERM:
			str += term2.ruleTerm->toQString();
			break;
		case RULEEXPRESSION:
			str += term2.ruleExpression->toQString();
			break;
		case UNDEF:
			str += "UNDEFINED";
			break;
	}
	str += ")" ;
	return str;
}

void RuleExpression::reset()
{
	switch (term1Type)
	{
		case RULETERM:
			this->term1.ruleTerm->getVariable()->reset();
			break;
		case RULEEXPRESSION:
			this->term1.ruleExpression->reset();
			break;
		case UNDEF:
			qWarning() << "[RuleExpression::reset]:Error reseting term1";
			break;
	}
	
	switch (term2Type)
	{
		case RULETERM:
			this->term2.ruleTerm->getVariable()->reset();
			break;
		case RULEEXPRESSION:
			this->term2.ruleExpression->reset();
			break;
		case UNDEF:
			qWarning() << "[RuleExpression::reset]:Error reseting term2";
			break;
	}
}

double RuleExpression::evaluate()
{
	// Results for each term
	double resTerm1 = 0.0;
	double resTerm2 = 0.0;

	// Evaluate term1: if it's an expression => recursive
	if( this->term1Type == RULEEXPRESSION ) resTerm1 = this->term1.ruleExpression->evaluate();
	else if( this->term1Type == RULETERM ) 
	{
		resTerm1 = this->term1.ruleTerm->getMembership();
	}
	else
	{
		qCritical() << "[RuleExpression::evaluate]:term1 undefined";
	}

	// Evaluate term2: if it's an expression => recursive
	if( this->term2Type == RULEEXPRESSION ) resTerm2 = this->term2.ruleExpression->evaluate();
	else if( this->term2Type == RULETERM )
	{
		resTerm2 = this->term2.ruleTerm->getMembership();
	}
	else 
	{
		qCritical() << "[RuleExpression::evaluate]:term2 undefined";
	}

	double result;
	result = this->ruleConnectionMethod->connect(resTerm1, resTerm2);
	
	qDebug() << "[RuleExpression::evaluate]:" << resTerm1 << "x" << resTerm2;

	// Is this clause negated?
	if( this->negated )
	{
		result = 1 - result;
	}
	return result;
}
