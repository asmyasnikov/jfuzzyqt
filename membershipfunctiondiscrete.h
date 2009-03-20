#ifndef MEMBERSHIPFUNCTIONDISCRETE_H
#define MEMBERSHIPFUNCTIONDISCRETE_H

#include "membershipfunction.h"

class MembershipFunctionDiscrete : public MembershipFunction
{
public:
	MembershipFunctionDiscrete(QObject* parent, MembershipType type);
	~MembershipFunctionDiscrete();
	virtual int size()const;
	virtual double valueX(int index);
private:

};

#endif // MEMBERSHIPFUNCTIONDISCRETE_H
