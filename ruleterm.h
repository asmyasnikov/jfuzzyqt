#ifndef RULETERM_H
#define RULETERM_H

#include <QString>
#include "Variable.h"
#include "MembershipFunction.h"

class RuleTerm
{
public:
	RuleTerm();
	RuleTerm(Variable variable, QString term, bool negated);
	~RuleTerm();
	Variable getVariable();
	const MembershipFunction* getMembershipFunction();
	QString getName();
	const bool isNegated() const;
private:
	/** Is it negated? */
	bool negated;
	/** RuleTerm's name */
	QString termName;
	/** Variable */
	Variable variable;
};

#endif // RULETERM_H
