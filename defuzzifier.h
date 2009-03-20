#ifndef DEFUZZIFIER_H
#define DEFUZZIFIER_H

#include <QObject>

class Defuzzifier : public QObject
{
public:
	Defuzzifier();
	//Defuzzifier(Variable variable);
	~Defuzzifier();
	QString getName();
	virtual double* defuzzify();
	virtual void reset();
	bool isDiscrete();
	void setDiscrete(const bool& value);
	virtual void debug(QString tbs) const;
private:
	bool discrete;
};

#endif // DEFUZZIFIER_H
