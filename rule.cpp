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

Rule::Rule(const Rule &rule){}

Rule Rule::operator=(const Rule &rule)
{
	Rule tmp(NULL,"");
	return (tmp);
}