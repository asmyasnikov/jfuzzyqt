#include "defuzzifiercenterofgravitysingletons.h"
#include <QDebug>

DefuzzifierCenterOfGravitySingletons::DefuzzifierCenterOfGravitySingletons()
{

}

DefuzzifierCenterOfGravitySingletons::~DefuzzifierCenterOfGravitySingletons()
{

}

double* DefuzzifierCenterOfGravitySingletons::defuzzify() 
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

	/*for( double xD : this ) {
		y = getDiscreteValue(xD);
		x = xD;
		sumWeight += x * y;
		sum += y;
	}*/


	if( sum != 0 ) return new double (sumWeight / sum);
	return NULL;
}

void DefuzzifierCenterOfGravitySingletons::debug(QString tbs) const
{
	qDebug() << tbs << "[DefuzzifierCenterOfGravitySingletons]: METHOD = COGS;";
}