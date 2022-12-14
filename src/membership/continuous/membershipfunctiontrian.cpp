/****************************************************************
Copyright (C) 2009 Aleksey Myasnikov
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser GPL as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser GPL for more details.
You should have received a copy of the GNU Lesser GPL
in file LICENSE along with this program.  If not, see
<http://www.gnu.org/licenses/>
****************************************************************/
/*!
 * \file membershipfunctiontrian.cpp
 * \class MembershipFunctionTrian
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 1.08
 * \brief Implementation Triangular membership function
 */
#include "membershipfunctiontrian.h"
#include <math.h>
#include <QDebug>

jfuzzyqt::MembershipFunctionTrian::MembershipFunctionTrian(QObject* parent, double left, double mid, double right)
    : MembershipFunctionContinuous(parent, FunctionTriangular)
{
    parameters.append(new Value(this, left,-HUGE_VAL,HUGE_VAL, true));
    parameters.append(new Value(this, mid,parameters.at(0),HUGE_VAL, true));
    parameters.append(new Value(this, right,parameters.at(1),HUGE_VAL, true));
}

jfuzzyqt::MembershipFunctionTrian::~MembershipFunctionTrian()
{
}

QString jfuzzyqt::MembershipFunctionTrian::toString()const
{
    return QString("TRIAN %1 %2 %3")
           .arg(parameters[0]->getValue())
           .arg(parameters[1]->getValue())
           .arg(parameters[2]->getValue());
}
QString jfuzzyqt::MembershipFunctionTrian::getName() const
{
    return "TRIAN";
}
double jfuzzyqt::MembershipFunctionTrian::membership(double index) const
{
    if((index <= parameters[0]->getValue()) || (index > parameters[2]->getValue()) ) return 0.;
    else if( qAbs(index-parameters[1]->getValue()) < 1.e-10 ) return 1.;
    else if( index <= parameters[1]->getValue() ) return ((index - parameters[0]->getValue()) / (parameters[1]->getValue() - parameters[0]->getValue()));
    else return 1.-((index-parameters[1]->getValue())/(parameters[2]->getValue()-parameters[1]->getValue()));
}
bool jfuzzyqt::MembershipFunctionTrian::checkParameters(QString&errors)const
{
    bool toReturn = true;
    if( parameters[0]->getValue() > parameters[1]->getValue() )
    {
        toReturn = false;
        errors.append(QString("Parameter mid is out of range : %1 > %2\n").arg(parameters[0]->getValue()).arg(parameters[1]->getValue()));
    }
    if( parameters[1]->getValue() > parameters[2]->getValue() )
    {
        toReturn = false;
        errors.append(QString("Parameter mid is out of range : %1 > %2\n").arg(parameters[1]->getValue()).arg(parameters[2]->getValue()));
    }
    return toReturn;
}
void jfuzzyqt::MembershipFunctionTrian::estimateUniverse()
{
    if(!universeMax) universeMax = new double;
    if(!universeMin) universeMin = new double;
    *universeMax = parameters[2]->getValue();
    *universeMin = parameters[0]->getValue();
}
