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
 * \file defuzzifierdiscrete.cpp
 * \class FIXME
 * \author Marco Estanqueiro
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 0.2
 * \brief FIXME
 */
#include "defuzzifierdiscrete.h"
#include <QDebug>

DefuzzifierDiscrete::DefuzzifierDiscrete()
    : Defuzzifier()
{
    setDiscrete(true);
}

DefuzzifierDiscrete::~DefuzzifierDiscrete()
{
}

QList<double> DefuzzifierDiscrete::values()const
{
    QList<double> toReturn;
    QList<QString> list = discreteValues.keys();
    foreach (QString str, list){
        toReturn.append(str.toDouble());
    }
    return toReturn;
}

/** Get a point's 'y' value */
double DefuzzifierDiscrete::getDiscreteValue(double x) const
{
    double toReturn = 0;
    if ( discreteValues.contains( QString::number(x) ) )
    {
        toReturn = discreteValues.value(QString::number(x));
    }
    return toReturn;
}

/** Set a point */
void DefuzzifierDiscrete::setPoint(double x, double y)
{
    discreteValues.insert(QString::number(x), y);
}

void DefuzzifierDiscrete::reset()
{
    discreteValues.clear();
}
