#ifndef RULEEXPRESSION_H
#define RULEEXPRESSION_H

#include "ruleterm.h"
#include "ruleexpression.h"

class RuleExpression
{
public:
	RuleExpression();
	~RuleExpression();

private:
	enum form_t {TRuleTerm, TRuleExpression}; 

	typedef union form1types_t {
		RuleTerm* ruleTerm;
		RuleExpression* ruleExpression;
	} form1;
	form_t form1type;

	/** Term2 can be a either a 'RuleTerm' or 'RuleExpression' */
	typedef union form2types_t {
		RuleTerm* ruleTerm;
		RuleExpression* ruleExpression;
	} form2;
	form_t form2type;
	/** Is it negated? */
	bool negated;
};

#endif // RULEEXPRESSION_H
