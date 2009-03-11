#include "variable.h"
#include "defuzzifier.h"
#include <QDebug>

Variable::Variable()
{
	this->deffuzifier=NULL;
	linguisticTerms.clear();
	this->value=0;
	this->defaultValue=NULL;
}

Variable::Variable(QString name)
{
	this->name=name;
	this->deffuzifier=NULL;
	linguisticTerms.clear();
	this->defaultValue=NULL;
	this->value=0;
}
Variable::~Variable()
{
	if (this->deffuzifier!=NULL)
	{
		delete(this->deffuzifier);
	}
	if (this->defaultValue!=NULL)
	{
		delete this->defaultValue;
	}

}
QString Variable::getName()
{
	return this->name;
}
void Variable::setName(QString name)
{
	this->name=name;
}
void Variable::addLinguisticTerm(LinguisticTerm lt)
{
	linguisticTerms.insert(lt.getTermName(), lt);
}
const MembershipFunction* Variable::getMembershipFunction(QString termName)
{
	return this->getLinguisticTerm(termName).getMembershipFunction();
}
Defuzzifier* Variable::getDefuzzifier()
{
	return this->deffuzifier;
}
void Variable::setValue(double value)
{
	this->value=value;
}
double Variable::getValue()
{
	return this->value;
}
/** Return 'true' if this is an output variable */
bool Variable::isOutputVariable() const
{
	return (deffuzifier != NULL);///<Only output variables have defuzzyfiers
}
void Variable::defuzzify()
{
	qDebug()<<"Variable::isOutputVarable->Uninplemented";
}

/*! \brief Get 'termName' linguistic term
*/
LinguisticTerm Variable::getLinguisticTerm(QString termName)
{
	//LinguisticTerm lt = linguisticTerms.get(termName);
	//if( lt == null ) throw new RuntimeException("No such linguistic term: '" + termName + "'");
	if( !this->linguisticTerms.contains(termName))
	{
		qCritical("Variable::getLinguisticTerm:No such linguistic term: '" + termName.toAscii() + "'");
	}
	return this->linguisticTerms.value(termName);
}
void Variable::setDefaultValue(double value)
{
	if (this->defaultValue!=NULL)
	{
		delete this->defaultValue;
	}
	this->defaultValue = new double(value);
}

void Variable::setDefuzzifier(Defuzzifier* deffuzifier)
{
	if (this->deffuzifier!=NULL)
	{
		delete this->deffuzifier;
	}
	this->deffuzifier = deffuzifier;
}
void Variable::debug(QString tbs) const
{
	QString nxTbs = tbs;
	nxTbs.append("\t");
	qDebug() << tbs << "Variable" << this->name << "{";
	(this->deffuzifier!=NULL) ? this->deffuzifier->debug(nxTbs) : qDebug() << tbs << "No deffuzifier";
	qDebug() << tbs<< "Value(" << this->value << ")";
	QHashIterator<QString, LinguisticTerm> var(this->linguisticTerms);
	while ( var.hasNext() ) {
		var.next();
		var.value().debug(tbs);
	}
	qDebug() << tbs<< "}";
}
