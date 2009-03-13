#ifndef RULEACCUMULATIONMETHODMAX_H
#define RULEACCUMULATIONMETHODMAX_H

#include "ruleaccumulationmethod.h"
#include <QObject>

class RuleAccumulationMethodMax : public RuleAccumulationMethod
{
	Q_OBJECT

public:
	RuleAccumulationMethodMax(QObject *parent=NULL);
	~RuleAccumulationMethodMax();
	double aggregate(double defuzzifierValue, double valueToAggregate) const;
	QString toQString()const;
private:
	
};

#endif // RULEACCUMULATIONMETHODMAX_H
