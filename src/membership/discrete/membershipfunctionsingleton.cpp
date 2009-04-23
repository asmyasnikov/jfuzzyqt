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
 * \file membershipfunctionsingleton.cpp
 * \class MembershipFunctionSingleton
 * \author Marco Estanqueiro <estanqueiro.marco@gmail.com>
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 0.2
 * \brief FIXME
 */
#include "membershipfunctionsingleton.h"
#include "../../membership/value.h"
#include <QDebug>

MembershipFunctionSingleton::MembershipFunctionSingleton(QObject* parent, const double& valueX)
:MembershipFunctionDiscrete(parent, FunctionSingleton)
{
    parameters = new Value*[2];
    parameters[0] = new Value(this, valueX);
    parameters[1] = new Value(this, 1.);
    if(universeMax) delete universeMax;
    if(universeMin) delete universeMin;
    universeMax = new double;
    universeMin = new double;
    *universeMax = valueX+1.e-10;
    *universeMin = valueX-1.e-10;
}

MembershipFunctionSingleton::~MembershipFunctionSingleton()
{
}

QString MembershipFunctionSingleton::getName() const
{
    return "Singleton";
}

void MembershipFunctionSingleton::debug(const QString& tbs)const
{
    QString nxtTbs = tbs;
    qDebug() << tbs << "\tDiscrete:" << discrete;
    qDebug() << tbs <<"\tParameters";
    parameters[0]->debug(nxtTbs);
}

int MembershipFunctionSingleton::size()const
{
    return 1;
}

double MembershipFunctionSingleton::membership(double index) const
{
    double toReturn = 0.;
    if( qAbs(index-parameters[0]->getValue()) < 1.e-10 )
    {
        toReturn = 1.;
    }
    return toReturn;
}

double MembershipFunctionSingleton::valueX(int index)const
{
    if( index == 0 )
    {
        return parameters[0]->getValue();
    }else{
        qCritical() << "[MembershipFunctionSingleton::valueX]:Array index out of range.";
        return 0.;
    }
}
bool MembershipFunctionSingleton::checkParamters(QString&errors)const
{
    bool toReturn = true;
    if( parameters[1]->getValue() < 0. || parameters[1]->getValue() > 1.)
    {
        toReturn = false;
        errors.append(QString("Parameter 'membership of singletone' should be between 0 and 1 : %1\n").arg(parameters[1]->getValue()));
    }
    return toReturn;
}
void MembershipFunctionSingleton::estimateUniverse()
{
    if(!universeMax) universeMax = new double;
    if(!universeMin) universeMin = new double;
    *universeMax = parameters[1]->getValue()+1.e10;
    *universeMin = parameters[1]->getValue()-1.e10;
}
