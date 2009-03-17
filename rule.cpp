#include "rule.h"

Rule::Rule() 
: QObject()
{
	this->name = "undefined";
}

Rule::Rule(QObject *parent, QString name) 
: QObject(parent)
{
	this->name = name;
}
Rule::Rule(const Rule &rule)
{
	this->name = rule.getName();
	this->addAntecedents( new RuleExpression(*rule.getAntecedents()) );
	this->consequents = rule.getConsequents();
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
		str += this->antecedents->toQString();
		str += "\n";
	}

	QLinkedList<RuleTerm>::const_iterator i = this->consequents.begin();
	while (i != this->consequents.end()) {
		str += i->toQString();
		str += "\n";
		i++;
	}

	str += "}";
	return str;
}
