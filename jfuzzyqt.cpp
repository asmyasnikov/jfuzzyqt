#include "jfuzzyqt.h"
#include "ruleconnectionmethod.h"
#include "ruleconnectionmethodandmin.h"
#include "ruleconnectionmethodormax.h"
#include "fclruletree.h"
#include <QDebug>
#include <QRegExp>
#include <QFile>
#include <QTextStream>

JFuzzyQt::JFuzzyQt() : QObject()
{
}
JFuzzyQt::JFuzzyQt(QObject *parent) : QObject(parent)
{
}

JFuzzyQt::JFuzzyQt(const JFuzzyQt& fuzzy)
{
	this->functionBlocks = fuzzy.getFunctionBlocks();
	this->defaultBlockName = fuzzy.getDefaultBlockName();
}
JFuzzyQt::~JFuzzyQt()
{

}
bool JFuzzyQt::load(QString fileUri)
{
	bool toReturn = false;

	QFile file(fileUri);
	if (!file.open(QIODevice::ReadOnly))
	{
		QString str = "Unable to open the file (";
		str.append( fileUri );
		str.append( ")" ); 
		qFatal(str.toAscii());
		return false;
	}

	QRegExp rxFunctionBlock("FUNCTION_BLOCK\\s+(\\w+)");


	QTextStream in(&file);
	QString line = fclParser.readLine(in);

	FunctBlock functionBlock;

	while (!line.isNull()) { ///<File Cycle (only works for one function block
		
		if (rxFunctionBlock.indexIn(line) > -1) //If Function Block
		{
			functionBlock.setName(rxFunctionBlock.cap(1));
			fclParser.loadFunctBlock(in,functionBlock);
			this->addFunctionBlock(functionBlock);
		}//END If Function Block
		line = fclParser.readLine(in);
	} //END File Cycle
	qDebug() << "FIM FICHEIRO \n\n";
	
	return toReturn;
}
bool JFuzzyQt::addFunctionBlock(FunctBlock functionBlock)
{
	bool toReturn = false;
	if ( !this->functionBlocks.contains( functionBlock.getName() ))
	{
		this->functionBlocks.insert(functionBlock.getName(),functionBlock);
		toReturn = true;
	}
	if ( this->defaultBlockName == "" )
	{
		this->defaultBlockName = functionBlock.getName();
	}
	return toReturn;
}

/*! \brief Sets var from default functions block inserted
*
*/
void JFuzzyQt::setVariable(QString varName, double value)
{
	if( functionBlocks.size() > 0 )
	{
		qWarning("Only one function block is supported");
		this->functionBlocks[ this->defaultBlockName ].setValue(varName,value);
	}
	else
	{
			qWarning("There are no FunctionBlocks");
	}
}
void JFuzzyQt::evaluate()
{
	if( functionBlocks.size() > 0 )
	{
		qWarning("Only one function block is supported");
		this->functionBlocks[ this->defaultBlockName ].evaluate();
	}
	else
	{
			qWarning("There are no FunctionBlocks");
	}
}
double JFuzzyQt::getValue(QString varName)
{
	if( functionBlocks.size() > 0 )
	{
		qWarning("Only one function block is supported");
		return this->functionBlocks[ this->defaultBlockName ].getValue(varName);
	}
	else
	{
		qWarning("There are no FunctionBlocks");
	}
	return 0;

}

void JFuzzyQt::debug() const
{
	this->functionBlocks.value(this->defaultBlockName).debug("");
}
QString JFuzzyQt::getDefaultBlockName()const
{
	return this->defaultBlockName;
}
QHash<QString, FunctBlock> JFuzzyQt::getFunctionBlocks()const
{
	return this->functionBlocks;
}