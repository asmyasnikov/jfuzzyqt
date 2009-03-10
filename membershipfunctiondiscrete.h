#ifndef MEMBERSHIPFUNCTIONDISCRETE_H
#define MEMBERSHIPFUNCTIONDISCRETE_H

#include "membershipfunction.h"

class MembershipFunctionDiscrete : public MembershipFunction
{
public:
	MembershipFunctionDiscrete(MembershipType type);
	~MembershipFunctionDiscrete();
	virtual int size();
	virtual double valueX(int index);
private:

};

#endif // MEMBERSHIPFUNCTIONDISCRETE_H
