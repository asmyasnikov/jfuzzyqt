/****************************************************************
Copyright (C) 2009 Aleksey Myasnikov
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
 * \file membershipfunctiontrap.cpp
 * \class MembershipFunctionTrap
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 0.95
 * \brief Implementation Trapetziodal membership function
 */
#include "membershipfunctiontrap.h"
#include <math.h>
#include <QDebug>

jfuzzyqt::MembershipFunctionTrap::MembershipFunctionTrap(QObject* parent, double left, double lmid, double rmid, double right)
    : MembershipFunctionContinuous(parent, FunctionTriangular)
{
    parameters.append(new Value(this, left,-HUGE_VAL,HUGE_VAL, true));
    parameters.append(new Value(this, lmid,parameters.at(0),HUGE_VAL, true));
    parameters.append(new Value(this, rmid,parameters.at(1),HUGE_VAL, true));
    parameters.append(new Value(this, right,parameters.at(2),HUGE_VAL, true));
}

jfuzzyqt::MembershipFunctionTrap::~MembershipFunctionTrap()
{
}

QString jfuzzyqt::MembershipFunctionTrap::toString()const
{
    return QString("TRAPE %1 %2 %3 %4")
           .arg(parameters[0]->getValue())
           .arg(parameters[1]->getValue())
           .arg(parameters[2]->getValue())
           .arg(parameters[3]->getValue());
}
QString jfuzzyqt::MembershipFunctionTrap::getName() const
{
    return "TRAPE";
}
double jfuzzyqt::MembershipFunctionTrap::membership(double index) const
{
    if((index <= parameters[0]->getValue()) || (index > parameters[2]->getValue()) ) return 0.;
    else if( index >= index-parameters[1]->getValue() && index <= index-parameters[1]->getValue() ) return 1.;
    else if( index <= parameters[1]->getValue() ) return ((index - parameters[0]->getValue()) / (parameters[1]->getValue() - parameters[0]->getValue()));
    else return 1.-((index-parameters[1]->getValue())/(parameters[2]->getValue()-parameters[1]->getValue()));
}
bool jfuzzyqt::MembershipFunctionTrap::checkParameters(QString&errors)const
{
    bool toReturn = true;
    if( parameters[0]->getValue() > parameters[1]->getValue() )
    {
        toReturn = false;
        errors.append(QString("Parameter left is out of range : %1 > %2\n").arg(parameters[0]->getValue()).arg(parameters[1]->getValue()));
    }
    if( parameters[1]->getValue() > parameters[2]->getValue() )
    {
        toReturn = false;
        errors.append(QString("Parameter left mid is out of range : %1 > %2\n").arg(parameters[1]->getValue()).arg(parameters[2]->getValue()));
    }
    if( parameters[2]->getValue() > parameters[3]->getValue() )
    {
        toReturn = false;
        errors.append(QString("Parameter right mid is out of range : %1 > %2\n").arg(parameters[2]->getValue()).arg(parameters[3]->getValue()));
    }
    return toReturn;
}
void jfuzzyqt::MembershipFunctionTrap::estimateUniverse()
{
    if(!universeMax) universeMax = new double;
    if(!universeMin) universeMin = new double;
    *universeMax = parameters[2]->getValue();
    *universeMin = parameters[0]->getValue();
}
