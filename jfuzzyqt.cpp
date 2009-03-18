#include "jfuzzyqt.h"
#include "ruleconnectionmethod.h"
#include "ruleconnectionmethodandmin.h"
#include "ruleconnectionmethodormax.h"
#include "fclruletree.h"
#include <QDebug>
#include <QRegExp>
#include <QFile>
#include <QTextStream>

JFuzzyQt::JFuzzyQt(QObject *parent) : QObject(parent)
{
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

	QRegExp rxFunctionBlock("function_block\\s+(\\w+)");

	QTextStream in(&file);
	FCLParser fclParser;
	QString line = fclParser.readLine(in);

	while (!line.isNull()) { ///<File Cycle (only works for one function block
		if (rxFunctionBlock.indexIn(line) > -1) //If Function Block
		{
			FunctBlock* functionBlock = new FunctBlock(this,rxFunctionBlock.cap(1));
			fclParser.loadFunctBlock(in,*functionBlock);
			this->addFunctionBlock(functionBlock);
		}///<END If Function Block
		line = fclParser.readLine(in);
	} ///<END File Cycle
	qDebug() << "FIM FICHEIRO \n\n";
	
	return toReturn;
}
bool JFuzzyQt::addFunctionBlock(FunctBlock* functionBlock)
{
	qWarning("[JFuzzyQt::addFunctionBlock]:Only one function block is supported");

	bool toReturn = false;
	functionBlock->setParent(this);

	if ( !this->functionBlocks.contains( functionBlock->getName() ))
	{
		this->functionBlocks.insert(functionBlock->getName(),functionBlock);
		toReturn = true;
	}
	if ( this->defaultBlockName == "" )
	{
		this->defaultBlockName = functionBlock->getName();
	}
	return toReturn;
}

/*! \brief Sets var from default functions block inserted
*
*/
void JFuzzyQt::setVariable(const QString& varName, const double& value)
{
	if( functionBlocks.size() > 0 )
	{
		qWarning("[JFuzzyQt::setVariable]:Only one function block is supported");
		QHash<QString, FunctBlock*>::iterator i = this->functionBlocks.find(this->defaultBlockName);
		if ( i!=this->functionBlocks.end() )
		{
			i.value()->setValue(varName.toLower(),value);
		}
	}
	else
	{
		qWarning("[JFuzzyQt::setVariable]:There are no FunctionBlocks");
	}
}
void JFuzzyQt::evaluate()
{
	if( functionBlocks.size() > 0 )
	{
		qWarning("[JFuzzyQt::evaluate]:Only one function block is supported");
		QHash<QString, FunctBlock*>::iterator i = this->functionBlocks.find(this->defaultBlockName);
		if ( i!=this->functionBlocks.end() )
		{
			i.value()->evaluate();
		}
	}
	else
	{
			qWarning("[JFuzzyQt::evaluate]:There are no FunctionBlocks");
	}
}
double JFuzzyQt::getValue(const QString& varName)const
{
	
	if( functionBlocks.size() > 0 )
	{
		qWarning("[JFuzzyQt::getValue]:Only one function block is supported");
		QHash<QString, FunctBlock*>::const_iterator i = this->functionBlocks.find(this->defaultBlockName);
		if ( i!=this->functionBlocks.end() )
		{
			return i.value()->getValue( varName.toLower() );
		}
	}
	else
	{
		qWarning("[JFuzzyQt::getValue]:There are no FunctionBlocks");
	}
	return 0;

}

void JFuzzyQt::debug() const
{
	this->functionBlocks.value(this->defaultBlockName)->debug("");
}
