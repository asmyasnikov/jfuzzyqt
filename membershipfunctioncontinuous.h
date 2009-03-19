#ifndef MEMBERSHIPFUNCTIONCONTINUOUS_H
#define MEMBERSHIPFUNCTIONCONTINUOUS_H

#include "membershipfunction.h"

class MembershipFunctionContinuous : public MembershipFunction
{
public:
	MembershipFunctionContinuous(QObject* parent, MembershipType type);
	~MembershipFunctionContinuous();

private:
	
};

#endif // MEMBERSHIPFUNCTIONCONTINUOUS_H
