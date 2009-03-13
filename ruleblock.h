#ifndef RULEBLOCK_H
#define RULEBLOCK_H

#include <QObject>
#include <QLinkedList>
#include <QString>
#include "ruleactivationmethod.h"
#include "ruleaccumulationmethod.h"
#include "rule.h"

class RuleBlock : public QObject
{
public:
	RuleBlock(QObject *parent=NULL);
	RuleBlock(QString name);
	RuleBlock(const RuleBlock &rb);
	~RuleBlock();
	void reset();
	void evaluate();
	QString getName()const;
	void debug(QString tbs) const;
	void addRuleActivationMethod(RuleActivationMethod* ruleActivationMethod);
	void addRuleAccumulationMethod(RuleAccumulationMethod* ruleAccumulationMethod);
	RuleActivationMethod* getRuleActivationMethod()const;
	RuleAccumulationMethod* getRuleAccumulationMethod()const;
	RuleBlock operator=(const RuleBlock &rb);
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
