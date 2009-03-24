#ifndef MEMBERSHIPFUNCTIONSINGLETON_H
#define MEMBERSHIPFUNCTIONSINGLETON_H

#include "membershipfunctiondiscrete.h"

class MembershipFunctionSingleton : public MembershipFunctionDiscrete
{
public:
	MembershipFunctionSingleton(QObject* parent, const double& valueX);
	~MembershipFunctionSingleton();
	void debug(QString tbs)const;
	int size()const;
	double membership(double index) const;
	double valueX(int index);
private:
	
};

#endif // MEMBERSHIPFUNCTIONSINGLETON_H
