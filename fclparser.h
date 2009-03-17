#ifndef FCLPARSER_H
#define FCLPARSER_H

#include "functblock.h"
#include "ruleexpression.h"
#include <QString>
#include <QTextStream>
#include <QObject>

class FCLParser : public QObject
{
public:
	FCLParser();
	FCLParser(QObject *parent);
	FCLParser(const FCLParser &parser);
	~FCLParser();
	QString readLine(QTextStream &in);
	void loadFunctBlock(QTextStream &in,FunctBlock& funcBlock);

private:
	void loadVarInput(QTextStream& in, FunctBlock& funcBlock);
	void loadVarOutput(QTextStream& in, FunctBlock& funcBlock);
	void loadDefuzzify(QTextStream& in, FunctBlock& funcBlock, QString varName);
	void loadFuzzify(QTextStream& in, FunctBlock& funcBlock, QString name);
	RuleBlock* loadRuleBlock(QTextStream& in, FunctBlock& funcBlock, QString name);
	Rule* loadRule(FunctBlock& funcBlock, QString &rule, QString name,RuleConnectionMethod *and, RuleConnectionMethod *or );
	RuleAccumulationMethod* createAccumulationMethod(QString type);
	RuleExpression* loadRuleIf(FunctBlock& funcBlock, QString &ruleif,RuleConnectionMethod *and, RuleConnectionMethod *or );

};

#endif // FCLPARSER_H
