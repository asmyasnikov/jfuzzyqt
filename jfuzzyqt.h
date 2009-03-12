#ifndef JFUZZYQT_H
#define JFUZZYQT_H

#include "jfuzzyqt_global.h"
#include "ruleexpression.h"
#include "functblock.h"
#include "fclparser.h"
#include <QString>
#include <QObject>
#include <QHash>

///<This class is called FIS@jFuzzyLogic

class JFuzzyQt : public QObject
{
public:
	JFuzzyQt();
	JFuzzyQt(QObject *parent);
	JFuzzyQt(const JFuzzyQt& fuzzy);
	~JFuzzyQt();
	bool load(QString fileUri);
	void setVariable(QString varName, double value);
	void evaluate();
	double getValue(QString varName);
	void debug() const;
	QHash<QString, FunctBlock> getFunctionBlocks()const;
	QString getDefaultBlockName()const;
	FCLParser* getFCLParser()const;

private:
	QHash<QString, FunctBlock> functionBlocks;
	QString defaultBlockName;
	FCLParser fclParser;

	bool addFunctionBlock(FunctBlock functionBlock);
};

#endif // JFUZZYQT_H