#ifndef RULEACTIVATIONMETHOD_H
#define RULEACTIVATIONMETHOD_H

#include "ruleterm.h"
#include "ruleaccumulationmethod.h"
#include <QObject>
#include <QString>
#include <QLinkedList>

class RuleActivationMethod : public QObject
{
	Q_OBJECT

public:
	RuleActivationMethod(QObject *parent,QString name="");
	RuleActivationMethod(const RuleActivationMethod &ram);
	~RuleActivationMethod();
	void setName(QString name);
	QString getName()const;
	virtual double imply(double degreeOfSupport, double membership)const;
	void imply(QLinkedList<RuleTerm>::iterator fuzzyRuleTerm, RuleAccumulationMethod ruleAccumulationMethod, double degreeOfSupport);
	QString toQString()const;

private:
	QString name;

};

#endif // RULEACTIVATIONMETHOD_H
