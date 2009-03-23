#include "functblock.h"

FunctBlock::FunctBlock(QObject* parent) : QObject (parent)
{
}
FunctBlock::FunctBlock(QObject* parent,const QString& name) : QObject (parent)
{
	this->name = name;
}
FunctBlock::FunctBlock(const FunctBlock &fb)
{
	this->name = fb.getName();
	this->ruleBlocks = fb.getRuleBlocks();
	this->variables = fb.getVariables();
}
FunctBlock::~FunctBlock()
{

}
QString FunctBlock::getName()const
{
	return this->name;
}
void FunctBlock::setName(const QString& name)
{
	this->name = name;
}

bool FunctBlock::addVariable(const QString& varName, Variable* variable)
{

	bool toReturn = false;
	if ( !this->variables.contains(varName) )
	{
		this->variables.insert(varName, variable);
		variable->setParent(this);
		toReturn = true;
		qDebug() << "[FunctBlock::addVariable]: added Variable '" << varName << "'.";
	}
	else
	{
		qDebug() << "[FunctBlock::addVariable: Variable '" << varName << "' duplicated";
	}
	return toReturn;
}

bool FunctBlock::setVariable(const QString& varName, LinguisticTerm* lt)
{
	
	QHash<QString, Variable*>::iterator i = this->variables.find(varName);
	if ( i != this->variables.end() )
	{
		i.value()->addLinguisticTerm(lt);
		return true;
	}else
	{
		qWarning() << "[FunctBlock::setVariable]: Variable '" << varName << "' does not exist";
	}
	return false;
}
Variable* FunctBlock::getVariable(const QString& varName)
{
	QHash<QString, Variable*>::iterator i = this->variables.find(varName);

	if ( i!= this->variables.end() )
	{
		return i.value();
	}
	else
	{
		qWarning() << "[FunctBlock::getVariable]:Unknwon variable";
		return NULL;
	}
}
bool FunctBlock::setDefaultValue(const QString& varName,const double value)
{
	QHash<QString, Variable*>::iterator i = this->variables.find(varName);
	if ( i != this->variables.end() )
	{
		i.value()->setDefaultValue(value);
		return true;
	}else
	{
		qWarning() << "[FunctBlock::setVariable]: Variable '" << varName << "' does not exist";
	}
	return false;
}
bool FunctBlock::setDefuzzifier(const QString& varName, Defuzzifier* d)
{
	
	QHash<QString, Variable*>::iterator i = this->variables.find(varName);
	if ( i != this->variables.end() )
	{
		i.value()->setDefuzzifier(d);
		return true;
	}else
	{
		qWarning() << "[FunctBlock::setVariable]: Variable '" << varName << "' does not exist";
	}
	return false;
}
Defuzzifier* FunctBlock::createDefuzzifier(const QString& defuzzType)
{
	Defuzzifier* defuzzifier = NULL;
	if( defuzzType == "cog" )
	{
		//defuzzifier = new DefuzzifierCenterOfGravity(variable);
		QString error = "Unknown/Unimplemented Rule defuzzification method '";
		error.append( defuzzType );
		error.append( "'" );
		qCritical(error.toAscii());
	}
	else if( defuzzType == "cogs" )
	{	
		defuzzifier = new DefuzzifierCenterOfGravitySingletons();

	}
	else if( defuzzType == "cogf" )
	{
		//defuzzifier = new DefuzzifierCenterOfGravityFunctions(variable);
		QString error = "Unknown/Unimplemented Rule defuzzification method '";
		error.append( defuzzType );
		error.append( "'" );
		qCritical(error.toAscii());
	}
	else if( defuzzType == "coa" )
	{
		//defuzzifier = new DefuzzifierCenterOfArea(variable);
		QString error = "Unknown/Unimplemented Rule defuzzification method '";
		error.append( defuzzType );
		error.append( "'" );
		qCritical(error.toAscii());
	}
	else if( defuzzType =="lm" )
	{
		//defuzzifier = new DefuzzifierLeftMostMax(variable);
		QString error = "Unknown/Unimplemented Rule defuzzification method '";
		error.append( defuzzType );
		error.append( "'" );
		qCritical(error.toAscii());
	}
	else if( defuzzType == "rm" )
	{
		//defuzzifier = new DefuzzifierRightMostMax(variable);
		QString error = "Unknown/Unimplemented Rule defuzzification method '";
		error.append( defuzzType );
		error.append( "'" );
		qCritical(error.toAscii());
	}
	else if( defuzzType == "mm" )
	{
		//defuzzifier = new DefuzzifierMeanMax(variable);
		QString error = "Unknown/Unimplemented Rule defuzzification method '";
		error.append( defuzzType );
		error.append( "'" );
		qCritical(error.toAscii());
	}
	else {
		QString error = "Unknown/Unimplemented Rule defuzzification method ";
		error.append( defuzzType );
		error.append( "'" );
		qCritical(error.toAscii());
	}
	return defuzzifier;
}

bool FunctBlock::setValue(const QString& varName, const double& value)
{
	bool toReturn = false;
	if ( this->variables.contains( varName ) )
	{
		Variable *v = new Variable(this,varName);
		v->setValue( value );
		this->variables.insert( varName , v );
		toReturn = true;
	}
	return toReturn;
}
/*! \brief Evaluate fuzzy rules in this function block  
*/
void FunctBlock::evaluate()
{
	qDebug() << "[FunctBlock::evaluate]: beta.";
	///<First: Reset defuzzifiers, variables, etc.
	QHashIterator<QString, RuleBlock*> i(this->ruleBlocks);
	while (i.hasNext()) {
		i.next();
		i.value()->reset();
	}

	///<Second: Evaluate each RuleBlock
	QHashIterator<QString, RuleBlock*> j(this->ruleBlocks);
	while (j.hasNext()) {
		j.next();
		j.value()->evaluate();
	}

	///<Third: Defuzzify each consequent variable
	QHashIterator<QString, Variable*> var(this->variables);
	while ( var.hasNext() ) {
		var.next();
		if( var.value()->isOutputVariable() )
		{ 
			var.value()->defuzzify();
		}
	}
}

double FunctBlock::getValue(const QString& varName)const
{
	double toReturn = NULL;
	if ( this->variables.contains( varName ) )
	{
		toReturn = this->variables.value(varName)->getValue();
	}
	return toReturn;
}

bool FunctBlock::addRuleBlock(RuleBlock* rl)
{
	bool toReturn = false;
	if ( !this->ruleBlocks.contains(rl->getName()) )
	{
		this->ruleBlocks.insert( rl->getName(), rl );
		rl->setParent(this);
		toReturn = true;
	}
	else
	{
		qWarning() << "[FunctBlock::addRuleBlock]:Duplicated RuleBlock wasn't added"<< rl->getName();
	}
	return toReturn;
}

void FunctBlock::debug(QString tbs)const
{
	QString nxTbs = tbs;
	nxTbs.append("\t");

	qDebug() << tbs << "Debuging" << this->name;
	
	qDebug() << tbs << "VARIABLES{";
	QHashIterator<QString, Variable*> var(this->variables);
	while ( var.hasNext() ) {
		var.next();
		var.value()->debug(nxTbs);
	}
	qDebug() << tbs << "}";
	
	qDebug() << tbs << "RULE BLOCK{";
	QHashIterator<QString, RuleBlock*> j(this->ruleBlocks);
	while (j.hasNext()) {
		j.next();
		j.value()->debug(nxTbs);
	}
	qDebug() << tbs << "}";
}

/*FunctBlock FunctBlock::operator=(const FunctBlock &fb)
{
	FunctBlock tmp(fb);
	return tmp;
}*/
QHash<QString, RuleBlock*> FunctBlock::getRuleBlocks()const
{
	return this->ruleBlocks;
}
QHash<QString, Variable*> FunctBlock::getVariables()const
{
	return this->variables;
}