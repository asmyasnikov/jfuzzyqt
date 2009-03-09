#ifndef FUNCTBLOCK_H
#define FUNCTBLOCK_H

#include <QString>
#include <QHash>
#include <QDebug>
#include "Variable.h"
#include "ruleblock.h"
#include "Defuzzifier.h"
#include "DefuzzifierCenterOfGravitySingletons.h"


class FunctBlock
{
public:
	FunctBlock();
	FunctBlock(QString name);
	~FunctBlock();
	
	QString getName();
	void setName(QString name);
	//bool addVarBlock(Variable variable);
	Defuzzifier* createDefuzzifier(QString defuzzType);
	bool setValue(QString varName,double value);
	void evaluate();
	double getValue(QString varName);
	bool addVariable(QString varName,Variable variable);
	bool setVariable(QString varName,LinguisticTerm lt);
	bool setDefaultValue(const QString varName,const double value);
	bool setDefuzzifier(QString varName, Defuzzifier* d);
	bool addRuleBlock(RuleBlock rl);
	void debug(QString tbs) const;
private:
	/** Function block name */
	QString name;

	/** Several RuleBlocks indexed by name */
	QHash<QString, RuleBlock> ruleBlocks;

	/** Every variable is here (key: VariableName) */
	QHash<QString, Variable> variables;
};

#endif // FUNCTBLOCK_H
