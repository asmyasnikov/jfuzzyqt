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
 * \file membershipfunctiontrian.cpp
 * \class MembershipFunctionTrian
 * \author Aleksey Myasnikov
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 0.2
 * \brief Implementation Triangular membership function
 */
#include "membershipfunctiontrian.h"
#include <math.h>
#include <QDebug>

MembershipFunctionTrian::MembershipFunctionTrian(QObject* parent, double left, double mid, double right)
    : MembershipFunctionContinuous(parent, FunctionTriangular)
{
    parameters = new Value*[3];
    parameters[0] = new Value(this, left);
    parameters[1] = new Value(this, mid);
    parameters[2] = new Value(this, right);
    estimateUniverse();
}

MembershipFunctionTrian::~MembershipFunctionTrian()
{

}

void MembershipFunctionTrian::debug(const QString& tbs)const
{
    QString str = "{ trian ( ";
    str.append ( QString::number( parameters[0]->getValue() ) );
    str.append(" , ");
    str.append ( QString::number( parameters[1]->getValue() ) );
    str.append(" ) ");
    str.append(" }");
    qDebug() << tbs << str;
}
QString MembershipFunctionTrian::getName() const
{
    return "Trian";
}

double MembershipFunctionTrian::membership(double index) const
{
    if((index < parameters[0]->getValue()) || (index > parameters[2]->getValue()) ) return 0.;
    else if( qAbs(index-parameters[1]->getValue()) < 1.e-10 ) return 1.;
    else if( index < parameters[1]->getValue() ) return ((index - parameters[0]->getValue()) / (parameters[1]->getValue() - parameters[0]->getValue()));
    else return 1.-((index-parameters[1]->getValue())/(parameters[2]->getValue()-parameters[1]->getValue()));
}
bool MembershipFunctionTrian::checkParamters(QString&errors)const
{
    bool toReturn = true;
    if( parameters[0]->getValue() > parameters[1]->getValue() )
    {
        toReturn = false;
        errors.append(QString("Parameter mid is out of range (should stisfy: min <= mid): %1 > %2\n").arg(parameters[0]->getValue()).arg(parameters[1]->getValue()));
    }
    if( parameters[1]->getValue() > parameters[2]->getValue() )
    {
        toReturn = false;
        errors.append(QString("Parameter mid is out of range (should stisfy: min <= mid): %1 > %2\n").arg(parameters[1]->getValue()).arg(parameters[2]->getValue()));
    }
    return toReturn;
}
void MembershipFunctionTrian::estimateUniverse()
{
    if(!universeMax) universeMax = new double;
    if(!universeMin) universeMin = new double;
    *universeMax = parameters[2]->getValue();
    *universeMin = parameters[0]->getValue();
}