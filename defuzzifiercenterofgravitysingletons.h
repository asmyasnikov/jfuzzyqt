#ifndef DEFUZZIFIERCENTEROFGRAVITYSINGLETONS_H
#define DEFUZZIFIERCENTEROFGRAVITYSINGLETONS_H

#include <QString>
#include <QList>
#include "defuzzifierdiscrete.h"
#include "variable.h"

class DefuzzifierCenterOfGravitySingletons : public DefuzzifierDiscrete
{
public:
	DefuzzifierCenterOfGravitySingletons();
	~DefuzzifierCenterOfGravitySingletons();
	double* defuzzify();
	void debug(QString tbs) const;
private:
	
};

#endif // DEFUZZIFIERCENTEROFGRAVITYSINGLETONS_H
