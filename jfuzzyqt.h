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

	Q_OBJECT

public:
	JFuzzyQt(QObject *parent=NULL);
	~JFuzzyQt();
	bool load(QString fileUri);
	void setVariable(QString varName, double value);
	void evaluate();
	double getValue(QString varName);
	void debug() const;
	
private:
	QHash<QString, FunctBlock*> functionBlocks;
	QString defaultBlockName;
	
	bool addFunctionBlock(FunctBlock* functionBlock);
};

#endif // JFUZZYQT_H