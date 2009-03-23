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
void Defuzzifier::reset()
{
	qWarning() << "[Defuzzifier::reset]: Virtual method called.";
}
QVariant Defuzzifier::defuzzify()
{
	qWarning() << "[Defuzzifier::defuzzify]: Virtual method called.";
	QVariant res;
	return res;
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