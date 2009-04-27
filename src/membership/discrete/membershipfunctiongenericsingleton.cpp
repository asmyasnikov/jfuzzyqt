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
 * \file membershipfunctiongenericsingleton.cpp
 * \class MembershipFunctionGenericSingleton
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 0.83
 * \brief Implementation of generic singletone
 */
#include "membershipfunctiongenericsingleton.h"
#include "../../membership/value.h"
#include <QDebug>

jfuzzyqt::MembershipFunctionGenericSingleton::MembershipFunctionGenericSingleton(QObject* parent,
                                                                       const QList<double>& x,
                                                                       const QList<double>& y)
    :MembershipFunctionDiscrete(parent, FunctionSingleton)
{
    if(!universeMax) universeMax = new double(-1.e304);
    if(!universeMin) universeMin = new double( 1.e304);
    for(int i = 0; i < x.size(); i++)
    {
        this->x.append(new Value(this, x.at(i)));
        this->y.append(new Value(this, y.at(i)));
        *universeMax = qMax(*universeMax, x.at(i));
        *universeMin = qMin(*universeMin, x.at(i));
    }
}

jfuzzyqt::MembershipFunctionGenericSingleton::~MembershipFunctionGenericSingleton()
{
}

QString jfuzzyqt::MembershipFunctionGenericSingleton::getName() const
{
    return "Singletons";
}

void jfuzzyqt::MembershipFunctionGenericSingleton::debug(const QString& tbs)const
{
    QString nxtTbs = tbs;
    qDebug() << tbs << "\tDiscrete:" << discrete;
    qDebug() << tbs <<"\tParameters";
    for(int i = 0; i < x.size(); i++)
    {
        x.at(i)->debug(nxtTbs);
        y.at(i)->debug(nxtTbs);
    }
}

int jfuzzyqt::MembershipFunctionGenericSingleton::size()const
{
    return x.size();
}

double jfuzzyqt::MembershipFunctionGenericSingleton::membership(double index) const
{
    double toReturn = 0.;
    for(int i = 0; i < x.size(); i++)
    {
        if( qAbs(index-x.at(i)->getValue()) < 1.e-10 )
        {
            toReturn = y.at(i)->getValue();
            break;
        }
    }
    return toReturn;
}
bool jfuzzyqt::MembershipFunctionGenericSingleton::checkParamters(QString&errors)const
{
    bool toReturn = true;
    for(int i = 0; i < x.size(); i++)
    {
        if( (i < (x.size()-1)) && (x.at(i)->getValue() > x.at(i+1)->getValue()))
        {
            toReturn = false;
            errors.append(QString("Array not sorted\n"));
        }
        if((y.at(i)->getValue() > 1.) || (y.at(i)->getValue() < 0.))
        {
            toReturn = false;
            errors.append(QString("Membership is out of range: %1\n").arg(y.at(i)->getValue()));
        }
    }
    return toReturn;
}
void jfuzzyqt::MembershipFunctionGenericSingleton::estimateUniverse()
{
    if(!universeMax) universeMax = new double;
    if(!universeMin) universeMin = new double;
    *universeMax = (-1.e304);
    *universeMin = ( 1.e304);
    for(int i = 0; i < x.size(); i++)
    {
        *universeMax = qMax(*universeMax, x.at(i)->getValue());
        *universeMin = qMin(*universeMin, x.at(i)->getValue());
    }
}
double jfuzzyqt::MembershipFunctionGenericSingleton::valueX(int index)const
{
    Q_ASSERT(index < x.size());
    return x.at(index)->getValue();
}