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
 * \author Aleksey Myasnikov
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 0.83
 * \brief Implementation Sigmoidal membership function
 */
#include "membershipfunctionsigm.h"
#include <math.h>
#include <QDebug>

jfuzzyqt::MembershipFunctionSigm::MembershipFunctionSigm(QObject* parent, double mx, double dx)
    : MembershipFunctionContinuous(parent, FunctionGaussian)
{
    parameters = new Value*[2];
    parameters[0] = new Value(this, mx);
    parameters[1] = new Value(this, dx);
    estimateUniverse();
}

jfuzzyqt::MembershipFunctionSigm::~MembershipFunctionSigm()
{

}

void jfuzzyqt::MembershipFunctionSigm::debug(const QString& tbs)const
{
    QString str = "{ sigm ( ";
    str.append ( QString::number( parameters[0]->getValue() ) );
    str.append(" , ");
    str.append ( QString::number( parameters[1]->getValue() ) );
    str.append(" ) ");
    str.append(" }");
    qDebug() << tbs << str;
}
QString jfuzzyqt::MembershipFunctionSigm::getName() const
{
    return "Sigm";
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
