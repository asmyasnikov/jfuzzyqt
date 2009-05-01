/****************************************************************
Copyright (C) 2009 Aleksey Myasnikov, Marco Estanqueiro
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
 * \file membershipfunctiongauss.cpp
 * \class MembershipFunctionGauss
 * \author Marco Estanqueiro <estanqueiro.marco@gmail.com>
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 0.84
 * \brief Implementation Gaussian membership function
 */

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

#include "membershipfunctiongauss.h"
#include <math.h>
#include <QDebug>

jfuzzyqt::MembershipFunctionGauss::MembershipFunctionGauss(QObject* parent, double mx, double dx)
    : MembershipFunctionContinuous(parent, FunctionGaussian)
{
    parameters.append(new Value(this, mx));
    parameters.append(new Value(this, dx));
}
jfuzzyqt::MembershipFunctionGauss::~MembershipFunctionGauss()
{
}
QString jfuzzyqt::MembershipFunctionGauss::toQString()const
{
    return QString("GAUSS %1 %2")
           .arg(parameters[0]->getValue())
           .arg(parameters[1]->getValue());
}
QString jfuzzyqt::MembershipFunctionGauss::getName() const
{
    return "GAUSS";
}

double jfuzzyqt::MembershipFunctionGauss::membership(double index) const
{
    return (1. / parameters[1]->getValue() / sqrt(2. * M_PI) *
            exp(-(index - parameters[0]->getValue()) *
                 (index - parameters[0]->getValue()) /
                 (2 * parameters[1]->getValue() * parameters[1]->getValue())));
}
bool jfuzzyqt::MembershipFunctionGauss::checkParamters(QString&errors)const
{
    bool toReturn = true;
    if( parameters[1]->getValue() < 0 )
    {
        toReturn = false;
        errors.append(QString("Parameter 'stdev' should be greater than zero : %1\n").arg(parameters[1]->getValue()));
    }
    return toReturn;
}
void jfuzzyqt::MembershipFunctionGauss::estimateUniverse()
{
    if(!universeMax) universeMax = new double;
    if(!universeMin) universeMin = new double;
    *universeMax = parameters[0]->getValue()+3.*parameters[1]->getValue();
    *universeMin = parameters[0]->getValue()-3.*parameters[1]->getValue();
}
