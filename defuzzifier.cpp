#include "defuzzifier.h"
#include <QDebug>

Defuzzifier::Defuzzifier()
{

}

Defuzzifier::~Defuzzifier()
{

}
QString Defuzzifier::getName()
{
	QString toReturn;
	toReturn = "Defuzzifier";
	return toReturn;
}



void Defuzzifier::reset(){}

double* Defuzzifier::defuzzify()
{
	qDebug() << "double* Defuzzifier::defuzzify: UNINPLEMENTED";
	return NULL;
}

bool Defuzzifier::isDiscrete()
{
	return this->discrete;
}
void Defuzzifier::setDiscrete(const bool& value)
{
	this->discrete = value;
}
void Defuzzifier::debug(QString tbs) const
{
	qDebug()<< tbs <<"[Defuzzifier::debug]:Call to virtual method.";
}