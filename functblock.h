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
	FunctBlock(QObject* parent,const QString& name);
	FunctBlock(const FunctBlock &fb);
	~FunctBlock();
	
	QString getName()const;
	void setName(const QString& name);
	Defuzzifier* createDefuzzifier(const QString& defuzzType);
	bool setValue(const QString& varName, const double& value);
	void evaluate();
	double getValue(const QString& varName)const;
	bool addVariable(const QString& varName, Variable* variable);
	bool setVariable(const QString& varName, LinguisticTerm* lt);
	Variable* getVariable(const QString& varName);
	bool setDefaultValue(const QString& varName,const double value);
	bool setDefuzzifier(const QString& varName, Defuzzifier* d);
	bool addRuleBlock(RuleBlock* rl);
	void debug(QString tbs) const;
	QHash<QString, RuleBlock*> getRuleBlocks()const;
	QHash<QString, Variable*> getVariables()const;

	//FunctBlock operator=(const FunctBlock &fb);
private:
	QString name; ///<Function block name
	QHash<QString, RuleBlock*> ruleBlocks; ///<Several RuleBlocks indexed by name
	QHash<QString, Variable*> variables; ///<Every variable is here (key: VariableName)
};

#endif // FUNCTBLOCK_H
