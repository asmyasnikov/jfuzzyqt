#include "RuleBlock.h"

#include <QDebug>
#include "ruleconnectionmethod.h"
#include "ruleconnectionmethodandmin.h"
#include "ruleconnectionmethodormax.h"

RuleBlock::RuleBlock()
{
	this->name = "Unknown";
	//RuleConnectionMethod and = new RuleConnectionMethodAndMin(), or = new RuleConnectionMethodOrMax();
	//String ruleAccumulationMethodType = "SUM";
}

RuleBlock::RuleBlock(QString name)
{
	this->name = name;
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
QString RuleBlock::getName()
{
	return this->name;
}
void RuleBlock::loadFrom(QString str)
{
	RuleConnectionMethod *and = new RuleConnectionMethodAndMin(), *or = new RuleConnectionMethodOrMax();
	QString ruleAccumulationMethodType = "SUM";

}
void RuleBlock::debug(QString tbs) const
{
	qDebug() << tbs << "[RuleBlock::debug]:Uninplemented.";
}