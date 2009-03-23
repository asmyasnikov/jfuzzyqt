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
	if ( discreteValues.contains( QString::number(x) ) )
	{
		return discreteValues.value(QString::number(x));
	}else
	{
		return 0;
	}
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
	/*if( discreteValues != NULL ) { // Set all values to 0
		
		for( Double key : this )
			discreteValues.put(key, 0.0);
	}*/
}