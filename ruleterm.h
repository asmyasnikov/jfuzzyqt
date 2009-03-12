#ifndef RULETERM_H
#define RULETERM_H

#include <QObject>
#include <QString>
#include "variable.h"
#include "membershipfunction.h"

class RuleTerm : public QObject
{
public:
	RuleTerm(QObject* parent=NULL);
	RuleTerm(const RuleTerm &rt);
	RuleTerm(QObject* parent, const RuleTerm &rt);
	RuleTerm(QObject* parent, Variable* variable, QString term, bool negated);
	~RuleTerm();
	Variable* getVariable()const;
	const MembershipFunction* getMembershipFunction();
	QString getName()const;
	const bool isNegated() const;
private:
	/** Is it negated? */
	bool negated;
	/** RuleTerm's name */
	QString termName;
	/** Variable */
	Variable* variable;
};

#endif // RULETERM_H
