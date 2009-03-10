#ifndef MEMBERSHIPFUNCTIONSINGLETON_H
#define MEMBERSHIPFUNCTIONSINGLETON_H

#include "membershipfunctiondiscrete.h"

class MembershipFunctionSingleton : public MembershipFunctionDiscrete
{
public:
	MembershipFunctionSingleton(Value valueX);
	~MembershipFunctionSingleton();
	void debug(QString tbs)const;
private:
	
};

#endif // MEMBERSHIPFUNCTIONSINGLETON_H
