#include "ruleblock.h"
#include "ruleconnectionmethod.h"
#include "ruleconnectionmethodandmin.h"
#include "ruleconnectionmethodormax.h"
#include <QDebug>

RuleBlock::RuleBlock(QObject *parent) : QObject (parent)
{
	this->name = "Unknown";
	this->ruleActivationMethod=NULL;
	this->ruleAccumulationMethod = NULL;
	this->and=NULL;
	this->or=NULL;
}

RuleBlock::RuleBlock(QString name) : QObject ()
{
	this->name = name;
	this->ruleActivationMethod=NULL;
	this->ruleAccumulationMethod = NULL;
	this->and=NULL;
	this->or=NULL;
}
RuleBlock::RuleBlock(const RuleBlock &rb) : QObject ()
{
	this->name = rb.getName();
	this->ruleActivationMethod = NULL;
	this->ruleAccumulationMethod = NULL;
	this->addRuleActivationMethod ( rb.getRuleActivationMethod() );
	this->addRuleAccumulationMethod ( rb.getRuleAccumulationMethod() );
	
	this->and=NULL;
	this->or=NULL;
	this->setRuleConnectionMethodAnd( rb.getRuleConnectionMethodAnd() );
	this->setRuleConnectionMethodOr( rb.getRuleConnectionMethodOr() );
}
RuleBlock::~RuleBlock()
{
	qDebug()<< "[RuleBlock::~RuleBlock]:Uninplemented.";
}
void RuleBlock::reset()
{
	qDebug()<< "[void RuleBlock::reset]:Uninplemented.";
}
void RuleBlock::evaluate()
{
	qDebug()<< "[void RuleBlock::evaluate]:Uninplemented.";
}
QString RuleBlock::getName()const
{
	return this->name;
}
void RuleBlock::debug(QString tbs) const
{
	qDebug() << tbs << this->toQString();
}
void RuleBlock::addRuleActivationMethod(RuleActivationMethod* ruleActivationMethod)
{
	if (this->ruleActivationMethod!=NULL)
	{
		delete this->ruleActivationMethod;
	}
	this->ruleActivationMethod = ruleActivationMethod;
	this->ruleActivationMethod->setParent(this);
}
void RuleBlock::addRuleAccumulationMethod(RuleAccumulationMethod* ruleAccumulationMethod)
{
	if (this->ruleAccumulationMethod!=NULL)
	{
		delete this->ruleAccumulationMethod;
	}
	this->ruleAccumulationMethod = ruleAccumulationMethod;
	this->ruleAccumulationMethod->setParent(this);

}
RuleActivationMethod* RuleBlock::getRuleActivationMethod()const
{
	return this->ruleActivationMethod;
}
RuleAccumulationMethod* RuleBlock::getRuleAccumulationMethod()const
{
	return this->ruleAccumulationMethod;
}
void RuleBlock::addRule(const Rule &fuzzyRule)
{
	qDebug() << "[RuleBlock::addRule]:Added rule block" << fuzzyRule.getName();
	rules.append(fuzzyRule);
}
QString RuleBlock::toQString()const
{
	QString tmp;
	tmp += "RuleBlock(";
	tmp += this->name;
	tmp += ")\n{\n";
	tmp += "ruleAccumulationMethod: ";
	if ( this->ruleAccumulationMethod != NULL )
	{
		tmp += this->ruleAccumulationMethod->toQString();
		tmp += "\n";
	}
	else
	{
		tmp += "NULL\n";
	}

	tmp += "ruleActivationMethod: ";
	if ( this->ruleActivationMethod != NULL )
	{
		tmp += this->ruleActivationMethod->toQString();
		tmp += "\n";
	}
	else
	{
		tmp += " NULL\n";
	}

	QLinkedList<Rule>::const_iterator i = rules.begin();
	while (i != rules.end()) {
		tmp += i->toQString();
		tmp += "\n";
		i++;
	}

	tmp += "}";
	return tmp;
}

void RuleBlock::setRuleConnectionMethodAnd(RuleConnectionMethod *and)
{
	if( this->and != NULL)
	{
		delete (this->and);
	}
	this->and = and;
	this->and->setParent(this);
}
void RuleBlock::setRuleConnectionMethodOr(RuleConnectionMethod *or)
{
	if( this->or != NULL)
	{
		delete (this->or);
	}
	this->or = or;
	this->or->setParent(this);
}
RuleConnectionMethod* RuleBlock::getRuleConnectionMethodAnd()const
{
	return this->and;
}
RuleConnectionMethod* RuleBlock::getRuleConnectionMethodOr()const
{
	return this->or;
}