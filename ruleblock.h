#ifndef RULEBLOCK_H
#define RULEBLOCK_H

#include <QLinkedList>
#include <QString>
#include "ruleactivationmethod.h"
#include "ruleaccumulationmethod.h"
#include "rule.h"

class RuleBlock
{
public:
	RuleBlock();
	RuleBlock(QString name);
	~RuleBlock();
	void reset();
	void evaluate();
	QString getName();
	void debug(QString tbs) const;
private:
	QString name;
	
	/** Rule accumulation method: How results of the rules are combined to obtain an overall result (e.g. MAX: maximum, BSUM: bounded sum, etc.) */
	RuleAccumulationMethod* ruleAccumulationMethod;

	/** Rule activation (implication) method: How the 'if' activates the 'then' (e.g. MIN: minimum, PROD: product) */
	RuleActivationMethod* ruleActivationMethod;

	/** All the rules */
	QLinkedList<Rule> rules;
};

#endif // RULEBLOCK_H
