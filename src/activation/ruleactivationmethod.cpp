/****************************************************************
Copyright (C) 2009 Marco Estanqueiro, Aleksey Myasnikov
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
in file LICENSE along with this program.  If not, see
<http://www.gnu.org/licenses/>
****************************************************************/
/*!
 * \file ruleactivationmethod.cpp
 * \class RuleActivationMethod
 * \author Marco Estanqueiro
 * \author Aleksey Myasnikov
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 0.2
 * \brief FIXME
 */
#include "ruleactivationmethod.h"
#include "../rule/variable.h"
#include "../defuzzifier/defuzzifier.h"
#include "../membership/discrete/membershipfunctiondiscrete.h"
#include "../defuzzifier/defuzzifierdiscrete.h"
#include "../defuzzifier/defuzzifiercontinuous.h"
#include <QDebug>

RuleActivationMethod::RuleActivationMethod(QObject *parent, const QString& name)
    : QObject(parent)
{
    this->name=name;
}
RuleActivationMethod::RuleActivationMethod(const RuleActivationMethod &ram)
    : QObject(ram.parent())
{
    name = ram.getName();
}
RuleActivationMethod::~RuleActivationMethod()
{
}
void RuleActivationMethod::setName(const QString& name)
{
    this->name = name;
}

/*!
* \brief Inference method
* Add membershipfunction to deffuzifier (using 'min' as inference)
*/
void RuleActivationMethod::imply(RuleTerm* fuzzyRuleTerm, RuleAccumulationMethod* ruleAccumulationMethod, double degreeOfSupport)
{
    Variable* variable = fuzzyRuleTerm->getVariable();
    Defuzzifier* defuzzifier = variable->getDefuzzifier();
    const MembershipFunction* mf = fuzzyRuleTerm->getMembershipFunction();
    double membership, y, x, aggregated = 0;

    // Both are equal? (both discrete or both continuous?)
    if( mf->isDiscrete() && !defuzzifier->isDiscrete() )
    {
        QString error = "MembershipFunction and Defuzzifier are neither both discrete nor both continuous\n\tTerm: ";
        error.append(fuzzyRuleTerm->getName());
        error.append("\n\tMembership function: ");
        error.append(mf->getName());
        error.append("\n\tDefuzzifier: ");
        error.append(defuzzifier->getName());
        error.append( "\n" );
        qFatal("%s", error.toLocal8Bit().data() );
    }
    DefuzzifierDiscrete* defuzzifierDiscrete = dynamic_cast<DefuzzifierDiscrete*>(defuzzifier);
    const MembershipFunctionDiscrete* mfd = dynamic_cast<const MembershipFunctionDiscrete*>(mf);
    DefuzzifierContinuous* defuzzifierContinuous = dynamic_cast<DefuzzifierContinuous*>(defuzzifier);
    Q_ASSERT((defuzzifierDiscrete && !defuzzifierContinuous)||
             (!defuzzifierDiscrete && defuzzifierContinuous));
    Q_ASSERT(!(mfd && defuzzifierContinuous));
    if( mfd ) {
        ///< Discrete case
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
            aggregated = ruleAccumulationMethod->aggregate(defuzzifierDiscrete->getDiscreteValue(x), y);
            defuzzifierDiscrete->setPoint(x, aggregated);
        }
    }else{
        ///< Continuous case
        if(defuzzifierContinuous)
        {
            x = defuzzifier->getMin();
            double step = defuzzifierContinuous->getStepSize();
            int i, length = defuzzifierContinuous->getLength();
            // Add membershipfunction to deffuzifier
            for( i = 0; i < length; i++, x += step ) {
                // Is term negated?
                if( fuzzyRuleTerm->isNegated() ) membership = 1 - mf->membership(x);
                else membership = mf->membership(x);
                y = imply(degreeOfSupport, membership); // Call to abstract implication method described above
                // Aggregate value
                aggregated = ruleAccumulationMethod->aggregate(defuzzifierContinuous->getValue(x), y);
                defuzzifierContinuous->setValue(x, aggregated);
            }
        }else{
            // Continuous memberfunction and discrete defuzzification - algorithm Tsukamoto
            int i, size ;
            size = 1000;
            x = defuzzifier->getMin();
            double step = (defuzzifier->getMax()-x)/double(1000);
            bool muchDegreeOfSupport = true;
            for( i = 0; i < size; i++, x += step )
            {
                // Is term negated?
                if( fuzzyRuleTerm->isNegated() ) membership = 1 - mf->membership(x);
                else membership = mf->membership(x);
                if(i>0)
                {
                    // If mf intersect degreeOfSupport than add this point
                    if(muchDegreeOfSupport != (membership > degreeOfSupport))
                    {
                        defuzzifierDiscrete->setPoint(x, membership);
                    }
                }
                muchDegreeOfSupport = (membership > degreeOfSupport);
            }
        }
    }
}
const QString& RuleActivationMethod::getName()const
{
    return name;
}
QString RuleActivationMethod::toQString()const
{
    return QString("act : %1").arg(name);
}
