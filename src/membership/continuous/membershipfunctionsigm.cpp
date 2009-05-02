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
 * \file membershipfunctionsigm.cpp
 * \class MembershipFunctionSigm
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 0.95
 * \brief Implementation Sigmoidal membership function
 */
#include "membershipfunctionsigm.h"
#include <math.h>
#include <QDebug>

jfuzzyqt::MembershipFunctionSigm::MembershipFunctionSigm(QObject* parent, double mx, double dx)
    : MembershipFunctionContinuous(parent, FunctionGaussian)
{
    parameters.append(new Value(this, mx,-HUGE_VAL,HUGE_VAL));
    parameters.append(new Value(this, dx,0.,HUGE_VAL));
}

jfuzzyqt::MembershipFunctionSigm::~MembershipFunctionSigm()
{
}
QString jfuzzyqt::MembershipFunctionSigm::toString()const
{
    return QString("SIGM %1 %2")
           .arg(parameters[0]->getValue())
           .arg(parameters[1]->getValue());
}
QString jfuzzyqt::MembershipFunctionSigm::getName() const
{
    return "SIGM";
}

double jfuzzyqt::MembershipFunctionSigm::membership(double index) const
{
    return 1./(1.+exp(-parameters[0]->getValue()*(index-parameters[1]->getValue())));
}
bool jfuzzyqt::MembershipFunctionSigm::checkParamters(QString&errors)const
{
    return true;
}
void jfuzzyqt::MembershipFunctionSigm::estimateUniverse()
{
    if(!universeMax) universeMax = new double;
    if(!universeMin) universeMin = new double;
    *universeMax = parameters[1]->getValue()+9./qAbs(parameters[0]->getValue());
    *universeMin = parameters[1]->getValue()-9./qAbs(parameters[0]->getValue());
}
