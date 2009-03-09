#ifndef DEFUZZIFIERDISCRETE_H
#define DEFUZZIFIERDISCRETE_H

#include <QHash>
#include <QList>
#include <QString>
#include "defuzzifier.h"

class DefuzzifierDiscrete : public Defuzzifier
{
public:
	DefuzzifierDiscrete();
	~DefuzzifierDiscrete();
	QList<double> values();
	double getDiscreteValue(double x);
	void setPoint(double x, double y);
	virtual void debug(QString tbs) const;
private:
	QHash<QString, double> discreteValues;
};

#endif // DEFUZZIFIERDISCRETE_H
