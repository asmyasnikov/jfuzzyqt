/****************************************************************
Copyright (C) 2009 Aleksey Myasnikov
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
 * \file optimizationparameters.cpp
 * \class OptimizationParameters
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \date 2009/04
 * \version 1.08
 * \brief Class OptimizationParameters provide access to values
 */
#include "optimizationparameters.h"

jfuzzyqt::OptimizationParameters::OptimizationParameters(QObject* parent) :
    QObject(parent)
{
}
jfuzzyqt::OptimizationParameters::~OptimizationParameters()
{
    for(int i = 0; i < parameters.size(); i++)
    {
        delete parameters[i];
    }
}

jfuzzyqt::Value* jfuzzyqt::OptimizationParameters::getValue(int index)const
{
    Q_ASSERT(index < parameters.size());
    return parameters.at(index);
}
int jfuzzyqt::OptimizationParameters::size()const
{
    return parameters.size();
}
