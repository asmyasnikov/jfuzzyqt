#ifndef VARIABLE_H
#define VARIABLE_H

#include <QObject>
#include <QString>
#include <QHash>
#include "LinguisticTerm.h"
#include "MembershipFunction.h"

class Defuzzifier;
class LinguisticTerm;
class MembershipFunction;

class Variable
{
public:
	Variable();
	Variable(QString name);
	~Variable();
	
	QString getName();
	void setName(QString name);
	void addLinguisticTerm(LinguisticTerm lt);
	const MembershipFunction* getMembershipFunction(QString termName);
	Defuzzifier* getDefuzzifier();
	void setValue(double value);
	double getValue();
	bool isOutputVariable() const;
	void defuzzify();
	LinguisticTerm getLinguisticTerm(QString termName);
	void setDefaultValue(double value);
	void setDefuzzifier(Defuzzifier* deffuzifier);
	void debug(QString tbs) const;
private:
	QString name;
	double value;
	double* defaultValue;
	Defuzzifier* deffuzifier;
	QHash<QString, LinguisticTerm> linguisticTerms;///<Terms for this variable
};

#endif // VARIABLE_H
