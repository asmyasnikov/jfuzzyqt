#include "functblock.h"

FunctBlock::FunctBlock(QObject* parent) : QObject (parent)
{
}
FunctBlock::FunctBlock(QObject* parent, QString name) : QObject (parent)
{
	this->name = name;
}
FunctBlock::FunctBlock(const FunctBlock &fb)
{
}
FunctBlock::~FunctBlock()
{

}
QString FunctBlock::getName()
{
	return this->name;
}
void FunctBlock::setName(QString name)
{
	this->name = name;
}

bool FunctBlock::addVariable(QString varName,Variable variable)
{

	bool toReturn = false;
	if ( !this->variables.contains(varName) )
	{
		this->variables.insert(variable.getName(),variable);
		toReturn = true;
		qDebug() << "[FunctBlock::addVariable]: added Variable '" << variable.getName() << "'.";
	}else{
		qDebug() << "[FunctBlock::addVariable: Variable '" << variable.getName() << "' duplicated";
	}

	return toReturn;
}

bool FunctBlock::setVariable(QString varName,LinguisticTerm lt)
{
	
	QHash<QString, Variable>::iterator i = this->variables.find(varName);
	if ( i != this->variables.end() )
	{
		i.value().addLinguisticTerm(lt);
		return true;
	}else
	{
		qWarning() << "[FunctBlock::setVariable]: Variable '" << varName << "' does not exist";
	}
	return false;
}
Variable* FunctBlock::getVariable(QString varName)
{
 QHash<QString, Variable>::iterator i = this->variables.find(varName);
 
 if ( i!= this->variables.end() )
{
	return &i.value();
}else
{
	return NULL;
}
 /*while (i != hash.end() && i.key() == "HDR") {
     cout << i.value() << endl;
 /*    ++i;
 /*}


	if ( this->variables.contains(varName) )
	{
		return &this->variables[varName];
	}else
	{
		return NULL;
	}*/
}
bool FunctBlock::setDefaultValue(const QString varName,const double value)
{
	
	QHash<QString, Variable>::iterator i = this->variables.find(varName);
	if ( i != this->variables.end() )
	{
		i.value().setDefaultValue(value);
		return true;
	}else
	{
		qWarning() << "[FunctBlock::setVariable]: Variable '" << varName << "' does not exist";
	}
	return false;
}
bool FunctBlock::setDefuzzifier(QString varName, Defuzzifier* d)
{
	
	QHash<QString, Variable>::iterator i = this->variables.find(varName);
	if ( i != this->variables.end() )
	{
		i.value().setDefuzzifier(d);
		return true;
	}else
	{
		qWarning() << "[FunctBlock::setVariable]: Variable '" << varName << "' does not exist";
	}
	return false;
}
Defuzzifier* FunctBlock::createDefuzzifier(QString defuzzType)
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

bool FunctBlock::setValue(QString varName,double value)
{
	bool toReturn = false;
	if ( this->variables.contains( varName ) )
	{
		Variable v;
		v.setName( varName );
		v.setValue( value );
		this->variables.insert( varName , v );
		toReturn = true;
	}
	return toReturn;
}
/*! \brief Evaluate fuzzy rules in this function block  
*/
void FunctBlock::evaluate()
{
	///<First: Reset defuzzifiers, variables, etc.
	QHashIterator<QString, RuleBlock> i(this->ruleBlocks);
	while (i.hasNext()) {
		i.next();
		this->ruleBlocks[i.key()].reset();
	}

	///<Second: Evaluate each RuleBlock
	QHashIterator<QString, RuleBlock> j(this->ruleBlocks);
	while (j.hasNext()) {
		j.next();
		this->ruleBlocks[j.key()].evaluate();
	}

	///<Third: Defuzzify each consequent variable
	QHashIterator<QString, Variable> var(this->variables);
	while ( var.hasNext() ) {
		var.next();
		if( var.value().isOutputVariable() ){ 
			this->variables[var.key()].defuzzify();
		}
	}
}

double FunctBlock::getValue(QString varName)
{
	double toReturn = NULL;
	if ( this->variables.contains( varName ) )
	{
		toReturn = this->variables[varName].getValue();
	}
	return toReturn;
}

bool FunctBlock::addRuleBlock(RuleBlock rl)
{
	bool toReturn = false;
	if ( !this->ruleBlocks.contains(rl.getName()) )
	{
		this->ruleBlocks.insert( rl.getName(), rl );
		toReturn = true;
	}
	return toReturn;
}

void FunctBlock::debug(QString tbs)const
{
	QString nxTbs = tbs;
	nxTbs.append("\t");

	qDebug() << tbs << "Debuging" << this->name;
	
	qDebug() << tbs << "VARIABLES{";
	QHashIterator<QString, Variable> var(this->variables);
	while ( var.hasNext() ) {
		var.next();
		var.value().debug(nxTbs);
	}
	qDebug() << tbs << "}";
	
	qDebug() << tbs << "RULE BLOCK{";
	QHashIterator<QString, RuleBlock> j(this->ruleBlocks);
	while (j.hasNext()) {
		j.next();
		j.value().debug(nxTbs);
	}
	qDebug() << tbs << "}";
}

FunctBlock FunctBlock::operator=(const FunctBlock &fb)
{
	FunctBlock tmp(fb);
	return tmp;
}