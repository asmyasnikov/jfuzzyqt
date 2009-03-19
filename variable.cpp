#include "variable.h"
#include "defuzzifier.h"
#include <QDebug>

Variable::Variable(QObject* parent)
: QObject (parent)
{
	this->deffuzifier=NULL;
	linguisticTerms.clear();
	this->value=0;
	this->defaultValue.clear();
}

Variable::Variable(QObject* parent,QString name)
: QObject (parent)
{
	this->name=name;
	this->deffuzifier=NULL;
	linguisticTerms.clear();
	this->defaultValue.clear();
	this->value=0;
}
Variable::~Variable()
{
	if (this->deffuzifier!=NULL)
	{
		delete(this->deffuzifier);
	}
}
QString Variable::getName()const
{
	return this->name;
}
void Variable::setName(const QString& name)
{
	this->name=name;
}
void Variable::addLinguisticTerm(LinguisticTerm* lt)
{
	lt->setParent(this);
	linguisticTerms.insert(lt->getTermName(), lt);
	qDebug() << "[Variable::addLinguisticTerm]:";
	lt->debug("");
}
const MembershipFunction* Variable::getMembershipFunction(const QString& termName)
{
	return this->getLinguisticTerm(termName)->getMembershipFunction();
}
Defuzzifier* Variable::getDefuzzifier()const
{
	return this->deffuzifier;
}
void Variable::setValue(const double& value)
{
	this->value=value;
}
double Variable::getValue()const
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
	qDebug()<<"[Variable::defuzzify]:Uninplemented";
}

/*! \brief Get 'termName' linguistic term
*/
LinguisticTerm* Variable::getLinguisticTerm(const QString& termName)
{	
	this->debug("");
	if( !this->linguisticTerms.contains(termName))
	{
		qCritical("[Variable::getLinguisticTerm]:No such linguistic term: '" + termName.toAscii() + "'");
		return NULL;
	}
	return this->linguisticTerms.value(termName);
}
void Variable::setDefaultValue(const double& value)
{
}

void Variable::setDefuzzifier(Defuzzifier* deffuzifier)
{
	if (this->deffuzifier!=NULL)
	{
		delete this->deffuzifier;
	}
	this->deffuzifier = deffuzifier;
	this->deffuzifier->setParent(this);
}
void Variable::debug(QString tbs) const
{
	QString nxTbs = tbs;
	nxTbs.append("\t");
	qDebug() << tbs << "Variable" << this->name << "{";
	(this->deffuzifier!=NULL) ? this->deffuzifier->debug(nxTbs) : qDebug() << tbs << "No deffuzifier";
	qDebug() << tbs<< "Value(" << this->value << ")";
	QHashIterator<QString, LinguisticTerm*> var(this->linguisticTerms);
	while ( var.hasNext() ) {
		var.next();
		var.value()->debug(tbs);
	}
	if(this->linguisticTerms.count()<1)
	{
		qDebug() << tbs<< "No Linguitic Terms";
	}
	qDebug() << tbs<< "}";
}
void Variable::reset()
{
	if (this->deffuzifier != NULL)
	{
		this->deffuzifier->reset();
		///<Set default value for output variables (if any default value was defined)
		if( defaultValue.isValid() )
		{
			this->value = defaultValue.toDouble() ;
		}
	}
	latestDefuzzifiedValue = defaultValue;
}
