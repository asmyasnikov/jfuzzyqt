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
 * \file defuzzifier.cpp
 * \class Defuzzifier
 * \author Marco Estanqueiro <estanqueiro.marco@gmail.com>
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 1.08
 * \brief FIXME
 */
#include "defuzzifier.h"
#include <QDebug>
#include <math.h>

jfuzzyqt::Defuzzifier::Defuzzifier()
{
    min = HUGE_VAL;
    max = -HUGE_VAL;
}
void jfuzzyqt::Defuzzifier::setMin(double min)
{
    this->min = min;
}
void jfuzzyqt::Defuzzifier::setMax(double max)
{
    this->max = max;
}
double jfuzzyqt::Defuzzifier::getMin()const
{
    return min;
}
double jfuzzyqt::Defuzzifier::getMax()const
{
    return max;
}
jfuzzyqt::Defuzzifier::~Defuzzifier()
{
}
bool jfuzzyqt::Defuzzifier::isDiscrete()const
{
    return discrete;
}
void jfuzzyqt::Defuzzifier::setDiscrete(const bool& value)
{
    discrete = value;
}
