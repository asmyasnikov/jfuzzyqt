#include "membershipfunctiondiscrete.h"
#include <QDebug>

MembershipFunctionDiscrete::MembershipFunctionDiscrete(QObject* parent, MembershipType type)
:MembershipFunction(parent, type)
{
	this->discrete = true;
}

MembershipFunctionDiscrete::~MembershipFunctionDiscrete()
{

}
/** How many points are there in this defuzzifier */
int MembershipFunctionDiscrete::size()const
{
	qDebug()<<"[MembershipFunctionDiscrete::size]:Virtual Method Called";
	return 0;
}
double MembershipFunctionDiscrete::valueX(int index)
{
	return 0;
}