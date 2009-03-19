#include "ruleactivationmethod.h"
#include "variable.h"
#include "defuzzifier.h"
#include "membershipfunctiondiscrete.h"
#include "defuzzifierdiscrete.h"
#include "defuzzifiercontinuous.h"
#include <QDebug>

RuleActivationMethod::RuleActivationMethod(QObject *parent, QString name)
	: QObject(parent)
{
	this->name=name;
}
RuleActivationMethod::RuleActivationMethod(const RuleActivationMethod &ram)
{
	this->name = ram.getName();
}
RuleActivationMethod::~RuleActivationMethod()
{

}
/**
 * Implication sub method used for inference (see imply method) 
 * @param degreeOfSupport : degree of support for this point
 * @param membership : membership for this point
 * @return implication
 */
double RuleActivationMethod::imply(double degreeOfSupport, double membership)const
{
	return 0;
}
void RuleActivationMethod::setName(QString name)
{
	this->name = name;
}

/**
* Inference method
* Add membershipfunction to deffuzifier (using 'min' as inference)
*/
void RuleActivationMethod::imply(QLinkedList<RuleTerm>::iterator fuzzyRuleTerm, RuleAccumulationMethod ruleAccumulationMethod, double degreeOfSupport)
{
	qDebug() << "[RuleActivationMethod::imply]:Unimplemented";
	/*Variable* variable = fuzzyRuleTerm->getVariable();
	Defuzzifier* defuzzifier = variable->getDefuzzifier();
	const MembershipFunction* mf = fuzzyRuleTerm->getMembershipFunction();
	double membership, y, x, aggregated = 0;

	// Both are equal? (both discrete or both continuous?)
	if( mf->isDiscrete() != defuzzifier->isDiscrete() )
	{
		QString error = "MembershipFunction and Defuzzifier are neither both discrete nor both continuous\n\tTerm: ";
		error.append(fuzzyRuleTerm->getName());
		error.append("\n\tMembership function: ");
		error.append(mf->getName());
		error.append("\n\tDefuzzifier: ");
		error.append(defuzzifier->getName());
		error.append( "\n");
		
		qFatal( error.toAscii() );
	}

	if( mf->isDiscrete() ) {
		//---
		// Discrete case
		//---
		DefuzzifierDiscrete* defuzzifierDiscrete = (DefuzzifierDiscrete*) defuzzifier;
		MembershipFunctionDiscrete* mfd = (MembershipFunctionDiscrete*) mf;

		// Add membershipfunction to deffuzifier
		int i, size ;
		size = mfd->size();
		for( i = 0; i < size; i++ ) {
			// Get 'x' value
			x = mfd->valueX(i);

			// Is term negated?
			if( fuzzyRuleTerm->isNegated() ) membership = 1 - mf->membership(x);
			else membership = mf->membership(x);

			y = imply(degreeOfSupport, membership); // Call to abstract implication method described above

			// Aggregate value
			aggregated = ruleAccumulationMethod.aggregate(defuzzifierDiscrete->getDiscreteValue(x), y);
			defuzzifierDiscrete->setPoint(x, aggregated);
		}
	} else {
		//---
		// Continuous case
		//---
		DefuzzifierContinuous* defuzzifierContinuous = (DefuzzifierContinuous*) defuzzifier;
		x = defuzzifierContinuous->getMin();
		double step = defuzzifierContinuous->getStepSize();

		// Do some sanitychecks
		//if( Double.isNaN(x) || Double.isInfinite(x) ) throw new RuntimeException("Universe minimum not calculated for term '" + fuzzyRuleTerm.getTermName() + "' : " + x);
		//if( Double.isNaN(step) || Double.isInfinite(step) ) throw new RuntimeException("Step not calculated for term '" + fuzzyRuleTerm.getTermName() + "' : " + step);

		int i, length = defuzzifierContinuous->getLength();

		// Add membershipfunction to deffuzifier
		for( i = 0; i < length; i++, x += step ) {
			// Is term negated?
			if( fuzzyRuleTerm->isNegated() ) membership = 1 - mf->membership(x);
			else membership = mf->membership(x);

			y = imply(degreeOfSupport, membership); // Call to abstract implication method described above

			// Aggregate value
			aggregated = ruleAccumulationMethod.aggregate(defuzzifierContinuous->getValue(i), y);
			defuzzifierContinuous->setValue(i, aggregated);
		}
	}*/
}
QString RuleActivationMethod::getName()const
{
	return this->name;
}
QString RuleActivationMethod::toQString()const
{
	QString qstr = "ACT : ";
	qstr.append( this->name );
	return qstr;
}
