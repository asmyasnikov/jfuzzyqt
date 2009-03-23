#include "ruleexpression.h"
#include "ruleconnectionmethod.h"
#include "ruleterm.h"
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
	switch ( re.getTerm1Type() )
	{ 
	case RULETERM:
		this->term1Type = RULETERM;	
		//this->term1.ruleTerm = new RuleTerm(re.getTerm1Rule());
		this->term1.ruleTerm = re.getTerm1Rule();
		this->term1.ruleTerm->setParent(this);
		break;
	case RULEEXPRESSION:
		this->term1Type = RULEEXPRESSION;	
		//this->term1.ruleExpression = new RuleExpression( re.getTerm1Expression() );
		this->term1.ruleExpression = re.getTerm1Expression();
		this->term1.ruleExpression->setParent(this);
		break;
	case UNDEF:
		qWarning() << "[RuleExpression::RuleExpression]: unddefined term1type";
		this->term1Type = UNDEF;
		break;
	}

	switch ( re.getTerm2Type() )
	{ 
	case RULETERM:
		this->term2Type = RULETERM;	
		this->term2.ruleTerm = new RuleTerm(re.getTerm2Rule());
		this->term2.ruleTerm->setParent(this);
		break;
	case RULEEXPRESSION:
		this->term2Type = RULEEXPRESSION;	
		this->term2.ruleExpression = new RuleExpression( re.getTerm2Expression() );
		this->term2.ruleExpression->setParent(this);
		break;
	case UNDEF:
		qWarning() << "[RuleExpression::RuleExpression]: unddefined term2type";
		this->term2Type = UNDEF;
		break;
	}
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
QVariant RuleExpression::evaluate()
{
	qDebug() << "[RuleExpression::evaluate]:beta";
	// Results for each term
	QVariant resTerm1 = 0;
	QVariant resTerm2 = 0;

	// Evaluate term1: if it's an expression => recurse
	if( this->term1Type == RULEEXPRESSION ) resTerm1 = this->term1.ruleExpression->evaluate();
	else if( this->term1Type == RULETERM ) resTerm1 = this->term1.ruleTerm->getMembership();
	else if( term1Type == UNDEF ) resTerm1.clear();

	// Evaluate term2: if it's an expression => recurse
	if( this->term2Type == RULEEXPRESSION ) resTerm2 = this->term2.ruleExpression->evaluate();
	else if( this->term2Type == RULETERM ) resTerm2 = this->term2.ruleTerm->getMembership();
	else if( term2Type == UNDEF ) resTerm2.clear();

	QVariant result;
	// No values? => return NaN
	if( (term1Type == UNDEF) && (term2Type == UNDEF) ) return result;
	// if we only have 1 term => just return that result
	if( term1Type == UNDEF ) result = resTerm2;
	else if( term2Type == UNDEF ) result = resTerm1;
	// Ok, we've got 2 values => connect these 2 values 
	else result = this->ruleConnectionMethod->connect(resTerm1.toDouble(), resTerm2.toDouble());

	// Is this clause negated?
	if( this->negated ) result = 1 - result.toDouble();
	return result;
}