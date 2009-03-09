#include "MembershipFunctionDiscrete.h"

MembershipFunctionDiscrete::MembershipFunctionDiscrete(MembershipType type):MembershipFunction(type)
{
	this->discrete = true;
}

MembershipFunctionDiscrete::~MembershipFunctionDiscrete()
{

}
/** How many points are there in this defuzzifier */
int MembershipFunctionDiscrete::size()
{
	return 0;
}
double MembershipFunctionDiscrete::valueX(int index)
{
	return 0;
}