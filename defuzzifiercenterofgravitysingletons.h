#ifndef DEFUZZIFIERCENTEROFGRAVITYSINGLETONS_H
#define DEFUZZIFIERCENTEROFGRAVITYSINGLETONS_H

#include "defuzzifierdiscrete.h"
#include "variable.h"
#include <QString>
#include <QList>
#include <QVariant>

class DefuzzifierCenterOfGravitySingletons : public DefuzzifierDiscrete
{
public:
	DefuzzifierCenterOfGravitySingletons();
	~DefuzzifierCenterOfGravitySingletons();
	QVariant defuzzify();
	void debug(QString tbs) const;
private:
	
};

#endif // DEFUZZIFIERCENTEROFGRAVITYSINGLETONS_H
