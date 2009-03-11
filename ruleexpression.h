#ifndef RULEEXPRESSION_H
#define RULEEXPRESSION_H

#include <QObject>

class RuleExpression : public QObject
{
public:
	RuleExpression(QObject *parent);
	RuleExpression(const RuleExpression &re);
	~RuleExpression();

private:
	
};

#endif // RULEEXPRESSION_H
