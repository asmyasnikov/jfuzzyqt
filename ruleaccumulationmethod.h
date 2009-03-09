/*!
* \file ClassNamePlaceholder.h
* \class ClassNamePlaceholder
* \author Marco Estanqueiro
* \date 2009/02
* \version 0.1
* \brief Rule accumulation base method
* 
* From FCL's definition:
* "The results of the rules are combined to obtain an overall result. The maximum algorithm is usually 
* used for accumulation. 
* Depending on the combination of operators in the individual steps, different inference strategies are 
* obtained. The best-known are the so-called MaxMin Inference and MaxProd Inference, which use the 
* maximum for accumulation and the minimum or the algebraic product for activation. In the case of the 
* MaxMin Inference, the membership functions of the Fuzzy Sets of the conclusions are limited to the 
* degree of accomplishment of the condition and then, in turn, combined to create a Fuzzy Set by 
* forming a maximum. In MaxProd Inference, in contrast, the membership functions of the Fuzzy Sets 
* of the conclusions are weighted, i.e. multiplied, with the degree of accomplishment of the condition 
* and then combined."
* 
* previous author author pcingola@users.sourceforge.net
*/


#ifndef RULEACCUMULATIONMETHOD_H
#define RULEACCUMULATIONMETHOD_H

#include <QString>

class RuleAccumulationMethod
{
public:
	RuleAccumulationMethod();
	~RuleAccumulationMethod();
	virtual double aggregate(double defuzzifierValue, double valueToAggregate);
	QString getName();
	void setName(QString name);
	QString toStringFcl();
private:
	QString name;
	
};

#endif // RULEACCUMULATIONMETHOD_H
