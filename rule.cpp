#include "rule.h"

Rule::Rule(QString name)
{
	this->name = name;
}

Rule::~Rule()
{

}
void Rule::addAntecedents(RuleExpression antecedents)
{
	this->antecedents = antecedents;
}
void Rule::addConsequent(RuleTerm rt)
{
	this->consequents.append(rt);
}