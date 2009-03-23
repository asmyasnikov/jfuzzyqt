#include "defuzzifierdiscrete.h"
#include <QDebug>

DefuzzifierDiscrete::DefuzzifierDiscrete()
{
	this->setDiscrete(true);
}

DefuzzifierDiscrete::~DefuzzifierDiscrete()
{

}

QList<double> DefuzzifierDiscrete::values()
{
	QList<double> toReturn;
	QList<QString> list;
	list = this->discreteValues.keys();
	foreach (QString str, list){
		toReturn.append(str.toDouble());
	}
	return toReturn;
}

/** Get a point's 'y' value */
double DefuzzifierDiscrete::getDiscreteValue(double x) 
{
	double toReturn = 0;
	if ( discreteValues.contains( QString::number(x) ) )
	{
		toReturn = discreteValues.value(QString::number(x));
	}
	return toReturn;
}

/** Set a point */
void DefuzzifierDiscrete::setPoint(double x, double y)
{
	discreteValues.insert(QString::number(x), y);
}

void DefuzzifierDiscrete::debug(QString tbs) const
{
	qDebug()<< tbs <<"[DefuzzifierDiscrete::debug]:Call to virtual method.";
}

void DefuzzifierDiscrete::reset()
{
	QHash<QString, double>::iterator i = this->discreteValues.begin();
	while (i != this->discreteValues.end())
	{
		this->discreteValues.insert(i.key(),0.0);
		++i;
	}
}