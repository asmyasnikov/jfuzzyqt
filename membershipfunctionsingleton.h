#ifndef MEMBERSHIPFUNCTIONSINGLETON_H
#define MEMBERSHIPFUNCTIONSINGLETON_H

#include "membershipfunctiondiscrete.h"

class MembershipFunctionSingleton : public MembershipFunctionDiscrete
{
public:
	MembershipFunctionSingleton(QObject* parent, Value valueX);
	~MembershipFunctionSingleton();
	void debug(QString tbs)const;
	int size()const;
	double membership(double index) const;

private:
	
};

#endif // MEMBERSHIPFUNCTIONSINGLETON_H
