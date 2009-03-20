#ifndef DEFUZZIFIER_H
#define DEFUZZIFIER_H

#include <QObject>
#include <QVariant>

class Defuzzifier : public QObject
{
public:
	Defuzzifier();
	~Defuzzifier();
	QString getName();
	virtual QVariant defuzzify();
	virtual void reset();
	bool isDiscrete();
	void setDiscrete(const bool& value);
	virtual void debug(QString tbs) const;
private:
	bool discrete;
};

#endif // DEFUZZIFIER_H
