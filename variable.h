#ifndef VARIABLE_H
#define VARIABLE_H

#include "linguisticterm.h"
#include "membershipfunction.h"
#include <QObject>
#include <QString>
#include <QHash>
#include <QVariant>

class Defuzzifier;
class LinguisticTerm;
class MembershipFunction;

class Variable : public QObject
{
	Q_OBJECT

public:
	Variable(QObject* parent=NULL);
	Variable(QObject* parent,QString name);
	~Variable();
	
	QString getName()const;
	void setName(const QString& name);
	void addLinguisticTerm(LinguisticTerm* lt);
	MembershipFunction* getMembershipFunction(const QString& termName);
	Defuzzifier* getDefuzzifier()const;
	void setValue(const double& value);
	double getValue()const;
	bool isOutputVariable() const;
	QVariant defuzzify();
	LinguisticTerm* getLinguisticTerm(const QString& termName);
	void setDefaultValue(const double& value);
	void setDefuzzifier(Defuzzifier* deffuzifier);
	void debug(QString tbs) const;
	void reset();
	double getMembership(const QString& termName);

private:
	QString name;
	double value;
	QVariant defaultValue;
	Defuzzifier* deffuzifier;
	QHash<QString, LinguisticTerm*> linguisticTerms;///<Terms for this variable
	QVariant latestDefuzzifiedValue;///<Latest defuzzified value

};

#endif // VARIABLE_H
