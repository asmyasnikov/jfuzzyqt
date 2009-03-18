#ifndef FUNCTBLOCK_H
#define FUNCTBLOCK_H

#include <QString>
#include <QHash>
#include <QDebug>
#include <QObject>
#include "variable.h"
#include "ruleblock.h"
#include "defuzzifier.h"
#include "defuzzifiercenterofgravitysingletons.h"


class FunctBlock : public QObject
{
	Q_OBJECT

public:
	FunctBlock(QObject* parent=NULL);
	FunctBlock(QObject* parent, QString name);
	FunctBlock(const FunctBlock &fb);
	~FunctBlock();
	
	QString getName()const;
	void setName(QString name);
	//bool addVarBlock(Variable variable);
	Defuzzifier* createDefuzzifier(QString defuzzType);
	bool setValue(QString varName,double value);
	void evaluate();
	double getValue(QString varName);
	bool addVariable(QString varName,Variable variable);
	bool setVariable(QString varName,LinguisticTerm lt);
	Variable* getVariable(QString varName);
	bool setDefaultValue(const QString varName,const double value);
	bool setDefuzzifier(QString varName, Defuzzifier* d);
	bool addRuleBlock(RuleBlock rl);
	void debug(QString tbs) const;
	QHash<QString, RuleBlock> getRuleBlocks()const;
	QHash<QString, Variable> getVariables()const;

	FunctBlock operator=(const FunctBlock &fb);
private:
	QString name; ///<Function block name

	QHash<QString, RuleBlock> ruleBlocks; ///<Several RuleBlocks indexed by name

	QHash<QString, Variable> variables; ///<Every variable is here (key: VariableName)
};

#endif // FUNCTBLOCK_H
