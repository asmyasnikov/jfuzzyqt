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
 * \class FIXME
 * \author Marco Estanqueiro
 * \author Aleksey Myasnikov
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 0.2
 * \brief FIXME
 */
#include "value.h"
#include <QDebug>

Value::Value(QObject* parent)
    :QObject(parent)
{
    type = UNDEFINED;
    valReal = 0;
}

Value::Value(QObject* parent, const double& value)
    :QObject(parent)
{
    type = REAL;
    valReal = value;
    varRef=NULL;
}

Value::~Value()
{
}

double Value::getValue()const
{
    if( type == UNDEFINED )
    {
        qWarning() << "[Value::getValue]: Value type not defined!";
        return 0;
    }

    switch(type)
    {
        case REAL:
            return valReal;
        case VAR_REFERENCE:
            if( varRef == NULL )
            {
                qWarning() << "[Value::getValue]: Undefined variable reference!";
                return 0;
            }
            return varRef->getValue();
        default:
            qWarning() << "[Value::getValue]: type '" << type << "' not implemented!";
    }
    qWarning() << "[Value::getValue]: shouldnt not happen";
    return 0;
}

void Value::debug(const QString& tbs)const
{
    switch (type)
    {
        case REAL:
            qDebug() << tbs << "valReal:" << QString::number(valReal);
            break;
        case VAR_REFERENCE:
                    qDebug() << tbs << "reference:";
                    break;
        default:
            qDebug() << tbs << "[Value::debug]:UNDEFINED";
            break;
    }
}
