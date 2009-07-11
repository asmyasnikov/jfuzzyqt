/****************************************************************
Copyright (C) 2009 Marco Estanqueiro, Aleksey Myasnikov
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
 * \file membershipfunctionsingleton.cpp
 * \class MembershipFunctionSingleton
 * \author Marco Estanqueiro <estanqueiro.marco@gmail.com>
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 1.08
 * \brief FIXME
 */
#include "membershipfunctionsingleton.h"
#include <QDebug>
#include <math.h>

jfuzzyqt::MembershipFunctionSingleton::MembershipFunctionSingleton(QObject* parent, const double& valueX)
:MembershipFunctionDiscrete(parent, FunctionSingleton)
{
    parameters.append(new Value(this, valueX, valueX-1.e-10, valueX+1.e-10, true));
}

jfuzzyqt::MembershipFunctionSingleton::~MembershipFunctionSingleton()
{
}
QString jfuzzyqt::MembershipFunctionSingleton::toString()const
{
    return QString::number(parameters[0]->getValue());
}
QString jfuzzyqt::MembershipFunctionSingleton::getName() const
{
    return "Singleton";
}
int jfuzzyqt::MembershipFunctionSingleton::size()const
{
    return 1;
}
double jfuzzyqt::MembershipFunctionSingleton::membership(double index) const
{
    double toReturn = 0.;
    if( qAbs(index-parameters[0]->getValue()) < 1.e-5 )
    {
        toReturn = 1.;
    }
    return toReturn;
}

double jfuzzyqt::MembershipFunctionSingleton::valueX(int index)const
{
    if( index == 0 )
    {
        return parameters[0]->getValue();
    }else{
        qCritical() << "[jfuzzyqt::MembershipFunctionSingleton::valueX]:Array index out of range.";
        return 0.;
    }
}
bool jfuzzyqt::MembershipFunctionSingleton::checkParameters(QString&errors)const
{
   return true;
}
void jfuzzyqt::MembershipFunctionSingleton::estimateUniverse()
{
    if(!universeMax) universeMax = new double;
    if(!universeMin) universeMin = new double;
    *universeMax = parameters[0]->getValue()+1.e-5;
    *universeMin = parameters[0]->getValue()-1.e-5;
}
