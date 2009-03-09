#include "MembershipFunctionSingleton.h"
#include "Value.h"
#include <QDebug>

MembershipFunctionSingleton::MembershipFunctionSingleton(Value valueX):MembershipFunctionDiscrete(FunctionSingleton)
{
	parameters = new Value[2];
	parameters[0] = valueX;
	parameters[1] = Value(1);
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
	parameters[0].debug(nxtTbs);
	//parameters[1].debug(nxtTbs);
	//qDebug() << tbs << "universeMax:" << this->universeMax;
	//qDebug() << tbs << "universeMin:" << this->universeMin;
		
}