#include "rule.h"
#include <QDebug>

Rule::Rule(QObject *parent) 
: QObject(parent)
{
	this->name = "undefined";
	this->weight=1;
}

Rule::Rule(QObject *parent, QString name) 
: QObject(parent)
{
	this->name = name;
	this->weight=1;
}
Rule::Rule(const Rule &rule)
{
	this->name = rule.getName();
	this->addAntecedents(rule.getAntecedents());
	this->consequents = rule.getConsequents();
	this->weight= rule.getWeight();
}
Rule::~Rule()
{

}
void Rule::addAntecedents(RuleExpression *antecedents)
{
	antecedents->setParent(this);
	this->antecedents = antecedents;
}
void Rule::addConsequent(RuleTerm* rt)
{
	rt->setParent(this);
	this->consequents.append(rt);
}
const QString Rule::getName()const
{
	return this->name;
}
RuleExpression* Rule::getAntecedents()const
{
	return antecedents;
}
const QList<RuleTerm*> Rule::getConsequents()const
{
	return this->consequents;
}
QString Rule::toQString() const
{
	QString str;
	str += "Rule (";
	str += this->getName();
	str += ")\n{\n";
	str += "antecedents: ";
	if ( this->antecedents == NULL )
	{
		str += "NULL\n";
	}
	else
	{
		str += this->antecedents->toQString(); ///< antecedents problem!!
		str += "\n";
	}
	str += "consequents: ";
	
	for (int i = 0; i < this->consequents.size(); ++i) {
		 str += this->consequents.at(i)->toQString();
		 str += "\n";
	}

	str += "}";
	return str;
}
void Rule::setDegreeOfSupport(const double& degreeOfSupport)
{
	this->degreeOfSupport = degreeOfSupport;
}
void Rule::reset()
{
	for (int i = 0; i < this->consequents.size(); ++i) {
		this->consequents.at(i)->getVariable()->reset();
	}
	this->antecedents->reset();
}
void  Rule::evaluate(RuleActivationMethod* act,RuleAccumulationMethod* accu)
{
	QVariant tmp = this->antecedents->evaluate(); ///< Evaluate antecedents
	if ( !tmp.isValid() )
	{
		qCritical() << "[Rule::evaluate]:no antecedentes evaluation.";
		tmp = 0;
	}
	this->degreeOfSupport = tmp.toDouble();
	///< Apply weight
	this->degreeOfSupport *= this->weight;

	///< Imply rule consequents: Apply degreeOfSupport to consequent linguisticTerms
	for (int i = 0; i < this->consequents.size(); ++i) {
		act->imply(this->consequents.at(i),accu,this->degreeOfSupport);
	}
}
double Rule::getWeight()const
{
	return this->weight;
}
