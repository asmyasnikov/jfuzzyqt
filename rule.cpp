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
void Rule::addConsequent(RuleTerm rt)
{
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
const QLinkedList<RuleTerm> Rule::getConsequents()const
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
	QLinkedList<RuleTerm>::const_iterator i = this->consequents.begin();
	while (i != this->consequents.end()) {
		str += i->toQString();
		str += "\n";
		i++;
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
	QLinkedList<RuleTerm>::iterator i = this->consequents.begin();
	while (i != this->consequents.end()) {
		i->getVariable()->reset();
		i++;
	}
	this->antecedents->reset();
}
void Rule::evaluate (RuleActivationMethod& act,RuleAccumulationMethod& accu)
{
	qDebug() << "[Rule::evaluate]:Unimplemented.";
	this->degreeOfSupport = this->antecedents->evaluate(); ///< Evaluate antecedents
	///< Apply weight
	this->degreeOfSupport *= this->weight;

	///< Imply rule consequents: Apply degreeOfSupport to consequent linguisticTerms
	QLinkedList<RuleTerm>::iterator i;
	for (i = this->consequents.begin(); i != this->consequents.end(); ++i)
	{
		act.imply(i,accu,this->degreeOfSupport);
	}
}
double Rule::getWeight()const
{
	return this->weight;
}
