/****************************************************************
Copyright (C) 2009 Marco Estanqueiro
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
 * \file defuzzifiercenterofgravitysingletons.cpp
 * \class FIXME
 * \author Marco Estanqueiro
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 0.2
 * \brief FIXME
 */
#include "defuzzifiercenterofgravitysingletons.h"
#include <QDebug>

DefuzzifierCenterOfGravitySingletons::DefuzzifierCenterOfGravitySingletons()
    : DefuzzifierDiscrete()
{
}

DefuzzifierCenterOfGravitySingletons::~DefuzzifierCenterOfGravitySingletons()
{
}

QString DefuzzifierCenterOfGravitySingletons::getName()const
{
    return "CenterOfGravitySingletons";
}
QVariant DefuzzifierCenterOfGravitySingletons::defuzzify()const
{
    double x, y, sum = 0, sumWeight = 0;
    QList<double> list = values();
    foreach (double xD, list)
    {
        y = getDiscreteValue(xD);
        x = xD;
        sumWeight += x * y;
        sum += y;
    }
    QVariant toReturn;
    if( sum > 0. ){
        toReturn = (sumWeight / sum);
    }
    return toReturn;
}

void DefuzzifierCenterOfGravitySingletons::debug(const QString& tbs) const
{
    qDebug() << tbs << "defuzzifier method = cogs;";
}