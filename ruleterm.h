#ifndef RULETERM_H
#define RULETERM_H

#include "variable.h"
#include "membershipfunction.h"
#include <QObject>
#include <QString>

class RuleTerm : public QObject
{
public:
	RuleTerm(QObject* parent=NULL);
	RuleTerm(const RuleTerm &rt);
	RuleTerm(QObject* parent, const RuleTerm &rt);
	RuleTerm(QObject* parent, Variable* variable, QString term, bool negated);
	~RuleTerm();
	Variable* getVariable()const;
	void setVariable(Variable* variable);
	const MembershipFunction* getMembershipFunction();
	QString getName()const;
	void setName(const QString &name);
	const bool isNegated() const;
	void setNegated(const bool& value);

private:
	/** Is it negated? */
	bool negated;
	/** RuleTerm's name */
	QString termName;
	/** Variable */
	Variable* variable;

};

#endif // RULETERM_H
