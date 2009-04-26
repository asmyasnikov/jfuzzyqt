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
 * \author Aleksey Myasnikov
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 0.78
 * \brief Implementation Triangular membership function
 */
#include "membershipfunctiontrap.h"
#include <math.h>
#include <QDebug>

MembershipFunctionTrap::MembershipFunctionTrap(QObject* parent, double left, double lmid, double rmid, double right)
    : MembershipFunctionContinuous(parent, FunctionTriangular)
{
    parameters = new Value*[4];
    parameters[0] = new Value(this, left);
    parameters[1] = new Value(this, lmid);
    parameters[2] = new Value(this, rmid);
    parameters[3] = new Value(this, right);
    estimateUniverse();
}

MembershipFunctionTrap::~MembershipFunctionTrap()
{

}

void MembershipFunctionTrap::debug(const QString& tbs)const
{
    QString str = "{ trap ( ";
    str.append ( QString::number( parameters[0]->getValue() ) );
    str.append(" , ");
    str.append ( QString::number( parameters[1]->getValue() ) );
    str.append(" , ");
    str.append ( QString::number( parameters[2]->getValue() ) );
    str.append(" , ");
    str.append ( QString::number( parameters[3]->getValue() ) );
    str.append(" ) ");
    str.append(" }");
    qDebug() << tbs << str;
}
QString MembershipFunctionTrap::getName() const
{
    return "Trapetziodal";
}

double MembershipFunctionTrap::membership(double index) const
{
    if((index <= parameters[0]->getValue()) || (index > parameters[2]->getValue()) ) return 0.;
    else if( index >= index-parameters[1]->getValue() && index <= index-parameters[1]->getValue() ) return 1.;
    else if( index <= parameters[1]->getValue() ) return ((index - parameters[0]->getValue()) / (parameters[1]->getValue() - parameters[0]->getValue()));
    else return 1.-((index-parameters[1]->getValue())/(parameters[2]->getValue()-parameters[1]->getValue()));
}
bool MembershipFunctionTrap::checkParamters(QString&errors)const
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
void MembershipFunctionTrap::estimateUniverse()
{
    if(!universeMax) universeMax = new double;
    if(!universeMin) universeMin = new double;
    *universeMax = parameters[2]->getValue();
    *universeMin = parameters[0]->getValue();
}
