#include "ruleblock.h"
#include "ruleconnectionmethod.h"
#include "ruleconnectionmethodandmin.h"
#include "ruleconnectionmethodormax.h"
#include <QDebug>

RuleBlock::RuleBlock(QObject *parent) : QObject (parent)
{
	this->name = "Unknown";
	//RuleConnectionMethod and = new RuleConnectionMethodAndMin(), or = new RuleConnectionMethodOrMax();
	//String ruleAccumulationMethodType = "SUM";
	this->ruleActivationMethod=NULL;
	this->ruleAccumulationMethod = NULL;
}

RuleBlock::RuleBlock(QString name) : QObject ()
{
	this->name = name;
	this->ruleActivationMethod=NULL;
	this->ruleAccumulationMethod = NULL;
}
RuleBlock::RuleBlock(const RuleBlock &rb) : QObject ()
{
	this->name = rb.getName();
	this->ruleActivationMethod = NULL;
	this->ruleAccumulationMethod = NULL;
	this->addRuleActivationMethod (new RuleActivationMethod(*rb.getRuleActivationMethod()));
	this->addRuleAccumulationMethod (new RuleAccumulationMethod(*rb.getRuleAccumulationMethod()));
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
	qDebug() << tbs << "[RuleBlock::debug]:Uninplemented.";
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

}
RuleActivationMethod* RuleBlock::getRuleActivationMethod()const
{
	return this->ruleActivationMethod;
}
RuleAccumulationMethod* RuleBlock::getRuleAccumulationMethod()const
{
	return this->ruleAccumulationMethod;
}
RuleBlock RuleBlock::operator=(const RuleBlock &rb)
{
	RuleBlock tmp(rb);
	return tmp;
}
void RuleBlock::addRule(const Rule &fuzzyRule)
{
	qDebug() << "[RuleBlock::addRule]:Added rule block" << fuzzyRule.getName();
	rules.append(fuzzyRule);
}
QString RuleBlock::toQString()
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

	QLinkedList<Rule>::iterator i = rules.begin();
	while (i != rules.end()) {
		tmp += i->toQString();
		tmp += "\n";
		i++;
	}


	tmp += "}";
	return tmp;
}