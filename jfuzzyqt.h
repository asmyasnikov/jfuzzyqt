#ifndef JFUZZYQT_H
#define JFUZZYQT_H

#include "jfuzzyqt_global.h"
#include <QString>
#include <QHash>
#include "functblock.h"
#include "ruleexpression.h"

///<This class is called FIS in JFuzzy

class JFuzzyQt
{
public:
	JFuzzyQt();
	~JFuzzyQt();
	bool load(QString fileUri);
	void setVariable(QString varName, double value);
	void evaluate();
	double getValue(QString varName);
	void debug() const;
private:
	QHash<QString, FunctBlock> functionBlocks;
	QString defaultBlockName;

	void loadVarInput(QTextStream& in, FunctBlock& funcBlock);
	void loadFuzzify(QTextStream& in, FunctBlock& funcBlock, QString name);
	void loadDefuzzify(QTextStream& in, FunctBlock& funcBlock, QString name);
	void loadRuleBlock(QTextStream& in, FunctBlock& funcBlock, QString name);
	void loadVarOutput(QTextStream& in, FunctBlock& funcBlock);
	bool addFunctionBlock(FunctBlock functionBlock);
	void loadRule(FunctBlock& funcBlock, QString &rule, QString name);
	RuleExpression loadRuleIf(FunctBlock& funcBlock, QString &ruleif);
};

#endif // JFUZZYQT_H