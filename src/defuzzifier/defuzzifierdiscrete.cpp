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
 * \class DefuzzifierDiscrete
 * \author Marco Estanqueiro <estanqueiro.marco@gmail.com>
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 0.83
 * \brief FIXME
 */
#include "defuzzifierdiscrete.h"
#include <QDebug>

jfuzzyqt::DefuzzifierDiscrete::DefuzzifierDiscrete()
    : Defuzzifier()
{
    setDiscrete(true);
}

jfuzzyqt::DefuzzifierDiscrete::~DefuzzifierDiscrete()
{
}

QList<double> jfuzzyqt::DefuzzifierDiscrete::values()const
{
    QList<double> toReturn;
    QList<QString> list = discreteValues.keys();
    foreach (QString str, list){
        toReturn.append(str.toDouble());
    }
    return toReturn;
}

/** Get a point's 'y' value */
double jfuzzyqt::DefuzzifierDiscrete::getDiscreteValue(double x) const
{
    double toReturn = 0;
    if ( discreteValues.contains( QString::number(x) ) )
    {
        toReturn = discreteValues.value(QString::number(x));
    }
    return toReturn;
}

/** Set a point */
void jfuzzyqt::DefuzzifierDiscrete::setPoint(double x, double y)
{
    discreteValues.insert(QString::number(x), y);
}

void jfuzzyqt::DefuzzifierDiscrete::reset()
{
    discreteValues.clear();
}
