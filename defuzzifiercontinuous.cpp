#include "defuzzifiercontinuous.h"
#include <QString>
#include <QDebug>

DefuzzifierContinuous::DefuzzifierContinuous():Defuzzifier()
{
	this->setDiscrete(false);
}

DefuzzifierContinuous::~DefuzzifierContinuous()
{

}
double DefuzzifierContinuous::getMin()
{
	return this->min;
}
double DefuzzifierContinuous::getStepSize()
{
	return this->stepSize;
}
int DefuzzifierContinuous::getLength()
{
	qDebug() << "[DefuzzifierContinuous::getLength]:Unimplmented.";
	//if( values != null ) return values.length;
	//return 0;
	return this->DEFAULT_NUMBER_OF_POINTS;
}
void DefuzzifierContinuous::setValue(double valueX, double valueY)
{
	values[getIndex(valueX)] = valueY;
}
/** Get 'values[]' index */
int DefuzzifierContinuous::getIndex(double d)
{
	if( (d < min) || (d > max) ){
		QString error = "Value out of range: ";
		error.append (QString::number(d));
		qCritical( error.toAscii());
	}
	return (int) ((d - min) / stepSize);
}
/** Get a value from 'values[]' using a double as index */
double DefuzzifierContinuous::getValue(double x)
{
	return values[getIndex(x)];
}