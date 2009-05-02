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
 * \file value.cpp
 * \class Value
 * \author Marco Estanqueiro <estanqueiro.marco@gmail.com>
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 0.95
 * \brief FIXME
 */
#include "value.h"
#include "../rule/variable.h"
#include <QDebug>

jfuzzyqt::Value::Value(QObject* parent)
    :QObject(parent)
{
    type = UNDEFINED;
    valReal = 0;
}

jfuzzyqt::Value::Value(QObject* parent, const double& value)
    :QObject(parent)
{
    type = REAL;
    valReal = value;
    varRef=NULL;
}

jfuzzyqt::Value::~Value()
{
}

double jfuzzyqt::Value::getValue()const
{
    if( type == UNDEFINED )
    {
        qWarning() << "[jfuzzyqt::Value::getValue]: Value type not defined!";
        return 0;
    }

    switch(type)
    {
        case REAL:
            return valReal;
        case VAR_REFERENCE:
            if( varRef == NULL )
            {
                qWarning() << "[jfuzzyqt::Value::getValue]: Undefined variable reference!";
                return 0;
            }
            return varRef->getValue();
        default:
            qWarning() << "[jfuzzyqt::Value::getValue]: type '" << type << "' not implemented!";
    }
    qWarning() << "[jfuzzyqt::Value::getValue]: shouldnt not happen";
    return 0;
}
void jfuzzyqt::Value::setValue(double value)
{
    if(type == REAL)
    {
        valReal = value;
    }
}
