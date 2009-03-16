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

	RuleExpression loadRuleIf(FunctBlock& funcBlock, QString &ruleif,RuleConnectionMethod *and, RuleConnectionMethod *or );
private:
	void loadVarInput(QTextStream& in, FunctBlock& funcBlock);
	void loadVarOutput(QTextStream& in, FunctBlock& funcBlock);
	void loadDefuzzify(QTextStream& in, FunctBlock& funcBlock, QString varName);
	void loadFuzzify(QTextStream& in, FunctBlock& funcBlock, QString name);
	void loadRuleBlock(QTextStream& in, FunctBlock& funcBlock, QString name);
	void loadRule(FunctBlock& funcBlock, QString &rule, QString name,RuleConnectionMethod *and, RuleConnectionMethod *or );
	RuleAccumulationMethod* createAccumulationMethod(QString type);
};

#endif // FCLPARSER_H
