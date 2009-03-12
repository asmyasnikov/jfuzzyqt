#ifndef RULECONNECTIONMETHODANDMIN_H
#define RULECONNECTIONMETHODANDMIN_H

#include "ruleconnectionmethod.h"
#include <QString>

class RuleConnectionMethodAndMin : public RuleConnectionMethod
{
public:
	RuleConnectionMethodAndMin();
	~RuleConnectionMethodAndMin();
	double connect(double antecedent1, double antecedent2);
	QString toQString() const;
private:
	
};

#endif // RULECONNECTIONMETHODANDMIN_H
