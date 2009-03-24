#include "defuzzifiercenterofgravitysingletons.h"
#include <QDebug>

DefuzzifierCenterOfGravitySingletons::DefuzzifierCenterOfGravitySingletons()
{

}

DefuzzifierCenterOfGravitySingletons::~DefuzzifierCenterOfGravitySingletons()
{

}

QVariant DefuzzifierCenterOfGravitySingletons::defuzzify() 
{
	double x, y, sum = 0, sumWeight = 0;
	QList<double> list = this->values();

	foreach (double xD, list)
	{
		y = getDiscreteValue(xD);
		x = xD;
		sumWeight += x * y;
		sum += y;
	}

	QVariant toReturn;
	if( sum != 0 ){
		toReturn = (sumWeight / sum);
	}
	return toReturn;
}

void DefuzzifierCenterOfGravitySingletons::debug(QString tbs) const
{
	qDebug() << tbs << "defuzzifier method = cogs;";
}