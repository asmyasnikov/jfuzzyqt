#ifndef RULECONNECTIONMETHODORMAX_H
#define RULECONNECTIONMETHODORMAX_H

#include "ruleconnectionmethod.h"

class RuleConnectionMethodOrMax : public RuleConnectionMethod
{
public:
	RuleConnectionMethodOrMax();
	~RuleConnectionMethodOrMax();
	double connect(double antecedent1, double antecedent2);
	QString toStringFcl()const;
private:
	
};

#endif // RULECONNECTIONMETHODORMAX_H
