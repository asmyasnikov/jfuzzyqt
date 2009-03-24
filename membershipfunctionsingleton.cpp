#include "membershipfunctionsingleton.h"
#include "value.h"
#include <QDebug>

MembershipFunctionSingleton::MembershipFunctionSingleton(QObject* parent, const double& valueX)
:MembershipFunctionDiscrete(parent, FunctionSingleton)
{
	parameters = new Value*[2];
	parameters[0] = new Value(this, valueX);
	parameters[1] = new Value(this, 1);
	qDebug() << "[MembershipFunctionSingleton::MembershipFunctionSingleton]:" << valueX;
}

MembershipFunctionSingleton::~MembershipFunctionSingleton()
{
}

void MembershipFunctionSingleton::debug(QString tbs)const
{
	QString nxtTbs = tbs;
	tbs.append("\t");
	qDebug() << tbs << "Discrete:" << this->discrete;
	qDebug() << tbs <<"Parameters";
	parameters[0]->debug(nxtTbs);
}

int MembershipFunctionSingleton::size()const
{
	return 1;
}

double MembershipFunctionSingleton::membership(double index) const
{
	double toReturn=0;
	if( index == parameters[0]->getValue() )
	{
		toReturn= parameters[1]->getValue();
	}
	return toReturn;
}

double MembershipFunctionSingleton::valueX(int index)
{
	if( index == 0 )
	{
		return parameters[0]->getValue();
	}
	else
	{
		qCritical() << "[MembershipFunctionSingleton::valueX]:Array index out of range.";
		return NULL;
	}
}