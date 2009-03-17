#ifndef RULEBLOCK_H
#define RULEBLOCK_H

#include "ruleactivationmethod.h"
#include "ruleaccumulationmethod.h"
#include "rule.h"
#include <QString>
#include <QLinkedList>
#include <QObject>

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
	void addRule(const Rule &fuzzyRule);
	RuleBlock operator=(const RuleBlock &rb);
	QString toQString()const;

private:
	QString name;
	
	///< Rule accumulation method: How results of the rules are combined to obtain an overall result (e.g. MAX: maximum, BSUM: bounded sum, etc.)
	RuleAccumulationMethod* ruleAccumulationMethod;

	///< Rule activation (implication) method: How the 'if' activates the 'then' (e.g. MIN: minimum, PROD: product)
	RuleActivationMethod* ruleActivationMethod;

	///< All the rules
	QLinkedList<Rule> rules;
};

#endif // RULEBLOCK_H
