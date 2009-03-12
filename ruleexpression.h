#ifndef RULEEXPRESSION_H
#define RULEEXPRESSION_H

#include <QObject>
class RuleConnectionMethod;
class RuleTerm;

class RuleExpression : public QObject
{
public:
	RuleExpression(QObject *parent);
	RuleExpression(const RuleExpression &re);
	~RuleExpression();
	int isTerm1Type()const;
	int isTerm2Type()const;
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

private:
	bool negated; ///<Is it negated?
	RuleConnectionMethod* ruleConnectionMethod; ///<How are term1 and term2 connected?
	union term1_t{///<Term can be a either a 'RuleTerm' or 'RuleExpression'
		RuleTerm *ruleTerm; 
		RuleExpression *ruleExpression;
	} term1,term2;
	static enum term_t{RULETERM , RULEEXPRESSION, UNDEF};
	term_t term1Type;
	term_t term2Type;
};

#endif // RULEEXPRESSION_H