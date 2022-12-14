/****************************************************************
Copyright (C) 2009 Marco Estanqueiro, Aleksey Myasnikov
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser GPL as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser GPL for more details.
You should have received a copy of the GNU Lesser GPL
in file LICENSE along with this program.  If not, see
<http://www.gnu.org/licenses/>
****************************************************************/
/*!
 * \file defuzzifiercontinuous.cpp
 * \class DefuzzifierContinuous
 * \author Marco Estanqueiro <estanqueiro.marco@gmail.com>
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 1.08
 * \brief FIXME
 */
#include "defuzzifiercontinuous.h"
#include <QString>
#include <QDebug>

jfuzzyqt::DefuzzifierContinuous::DefuzzifierContinuous()
    : Defuzzifier()
{
    setDiscrete(false);
}

jfuzzyqt::DefuzzifierContinuous::~DefuzzifierContinuous()
{
}
double jfuzzyqt::DefuzzifierContinuous::getStepSize()const
{
    return stepSize;
}
void jfuzzyqt::DefuzzifierContinuous::setMin(double min)
{
    Defuzzifier::setMin(min);
    stepSize = (max-min)/double(DEFAULT_NUMBER_OF_POINTS);
}
void jfuzzyqt::DefuzzifierContinuous::setMax(double max)
{
    Defuzzifier::setMax(max);
    stepSize = (max-min)/double(DEFAULT_NUMBER_OF_POINTS);
}
int jfuzzyqt::DefuzzifierContinuous::getLength()const
{
    return DEFAULT_NUMBER_OF_POINTS;
}
void jfuzzyqt::DefuzzifierContinuous::setValue(double valueX, double valueY)
{
    values[getIndex(valueX)] = valueY;
}
/** Get 'values[]' index */
int jfuzzyqt::DefuzzifierContinuous::getIndex(double d)const
{
    if( (d < min) || (d > max) ){
        QString error = "Value out of range: ";
        error.append (QString::number(d));
        qCritical() << error.toLocal8Bit().data();
    }
    return (int) ((d - min) / double(stepSize));
}
/** Get a value from 'values[]' using a double as index */
double jfuzzyqt::DefuzzifierContinuous::getValue(double x)const
{
    return values[getIndex(x)];
}
void jfuzzyqt::DefuzzifierContinuous::reset()
{
    for(int i = 0; i < DEFAULT_NUMBER_OF_POINTS; i++)
    {
        values[i] = 0.;
    }
}
