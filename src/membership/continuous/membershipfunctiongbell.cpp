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
 * \file membershipfunctiongbell.cpp
 * \class MembershipFunctionGauss
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 0.83
 * \brief Implementation GenBell membership function
 */
#include "membershipfunctiongbell.h"
#include <math.h>
#include <QDebug>

jfuzzyqt::MembershipFunctionGBell::MembershipFunctionGBell(QObject* parent, double a, double b, double mean)
    : MembershipFunctionContinuous(parent, FunctionGaussian)
{
    parameters.append(new Value(this, mean));
    parameters.append(new Value(this, a));
    parameters.append(new Value(this, b));
    estimateUniverse();
}

jfuzzyqt::MembershipFunctionGBell::~MembershipFunctionGBell()
{

}

void jfuzzyqt::MembershipFunctionGBell::debug(const QString& tbs)const
{
    QString str = "{ gbell ( ";
    str.append ( QString::number( parameters[0]->getValue() ) );
    str.append(" , ");
    str.append ( QString::number( parameters[1]->getValue() ) );
    str.append(" , ");
    str.append ( QString::number( parameters[2]->getValue() ) );
    str.append(" ) ");
    str.append(" }");
    qDebug() << tbs << str;
}
QString jfuzzyqt::MembershipFunctionGBell::getName() const
{
    return "GBell";
}

double jfuzzyqt::MembershipFunctionGBell::membership(double index) const
{
    double t = qAbs((index - parameters[0]->getValue()) / parameters[1]->getValue());
    t = pow(t, 2.0 * parameters[2]->getValue());
    return 1.0 / (1.0 + t);
}
bool jfuzzyqt::MembershipFunctionGBell::checkParamters(QString&errors)const
{
    bool toReturn = true;
    if( parameters[2]->getValue() < 0.)
    {
        toReturn = false;
        errors.append(QString("Parameter 'b' should be greater than zero : %1\n").arg(parameters[2]->getValue()));
    }
    return toReturn;
}
void jfuzzyqt::MembershipFunctionGBell::estimateUniverse()
{
    if(!universeMax) universeMax = new double;
    if(!universeMin) universeMin = new double;
    double delta = pow(999, 1 / (2 * parameters[2]->getValue())) * parameters[1]->getValue();
    *universeMin = parameters[0]->getValue() - delta;
    *universeMax = parameters[0]->getValue() + delta;
}
