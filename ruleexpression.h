/*!
* \file ruleexpression.h
* \class RuleExpression
* \author Marco Estanqueiro
* \date 2009/03
* \version 0.1
* \brief General rule expression term
*
* E.g.: "(temp IS hot AND pressure IS high) OR pressure IS low" 
* Original author  pcingola@users.sourceforge.net (jFuzzyLogic)
*/
#ifndef RULEEXPRESSION_H
#define RULEEXPRESSION_H

#include <QObject>
#include <QVariant>
class RuleConnectionMethod;
class RuleTerm;

class RuleExpression : public QObject
{
public:
	static enum term_t{RULETERM , RULEEXPRESSION, UNDEF};

	RuleExpression(QObject *parent=NULL);
	~RuleExpression();
	RuleConnectionMethod* getRuleConnectionMethod()const;
	bool isNegated()const;
	RuleTerm* getTerm1Rule()const;
	RuleTerm* getTerm2Rule()const;
	RuleExpression* getTerm1Expression()const;
	RuleExpression* getTerm2Expression()const;
	void addTerm1Rule(RuleTerm *ruleTerm);
	void addTerm2Rule(RuleTerm *ruleTerm);
	void addTerm1Expression(RuleExpression *ruleExpression);
	void addTerm2Expression(RuleExpression *ruleExpression);
	void setRuleConnectionMethod(RuleConnectionMethod* ruleConnectionMethod);
	QString toQString()const;
	RuleExpression::term_t getTerm1Type()const;
	RuleExpression::term_t getTerm2Type()const;
	void reset();
	QVariant evaluate();

private:
	bool negated; ///<Is it negated?
	RuleConnectionMethod* ruleConnectionMethod; ///<How are term1 and term2 connected?
	union term1_t{///<Term can be a either a 'RuleTerm' or 'RuleExpression'
		RuleTerm *ruleTerm; 
		RuleExpression *ruleExpression;
	} term1,term2;
	term_t term1Type;
	term_t term2Type;

};

#endif // RULEEXPRESSION_H
