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
 * \file defuzzifiercenterofgravity.cpp
 * \class DefuzzifierCenterOfGravity
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 0.82
 * \brief FIXME
 */
#include "defuzzifiercenterofgravity.h"
#include <QDebug>

DefuzzifierCenterOfGravity::DefuzzifierCenterOfGravity()
    : DefuzzifierContinuous()
{
}

DefuzzifierCenterOfGravity::~DefuzzifierCenterOfGravity()
{
}

QString DefuzzifierCenterOfGravity::getName()const
{
    return "CenterOfGravity";
}
QVariant DefuzzifierCenterOfGravity::defuzzify()const
{
    double x = min, y, sum = 0., sumWeight = 0.;
    for( int i = 0; i < DEFAULT_NUMBER_OF_POINTS; i++, x += stepSize )
    {
        y = values[i];
        sumWeight += x * y;
        sum += y;
    }
    QVariant toReturn;
    if( sum > 0. ){
        toReturn = (sumWeight / sum);
    }
    return toReturn;
}

void DefuzzifierCenterOfGravity::debug(const QString& tbs) const
{
    qDebug() << tbs << "defuzzifier method = cog;";
}
