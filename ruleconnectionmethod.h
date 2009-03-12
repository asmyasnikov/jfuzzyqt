/*!
* \file RuleConnectionMethod.h
* \class RuleConnectionMethod
* \author Marco Estanqueiro
* \date 2009/03
* \version 0.1
* \brief  Base for methods used to connect rule's antecedents
*
* From FCL's specs:
* 
* "To fulfill de Morgan's Law, the algorithms for operators AND and OR shall be used pair-wise e.g. 
* MAX shall be used for OR if MIN is used for AND."
*  
* 			Operator OR 		Operator AND 
* 			MAX					MIN 
* 			ASUM				PROD 
* 			BSUM				BDIF
*
* original author pcingola@users.sourceforge.net
*/
#ifndef RULECONNECTIONMETHOD_H
#define RULECONNECTIONMETHOD_H

#include <QString>

class RuleConnectionMethod 
{
public:
	RuleConnectionMethod(QString name="Undefined");
	~RuleConnectionMethod();
	QString getName() const;
	void setName(const QString name);
	virtual double connect(double antecedent1, double antecedent2);
	virtual QString toQString() const;
private:
	QString name;
};

#endif // RULECONNECTIONMETHOD_H
