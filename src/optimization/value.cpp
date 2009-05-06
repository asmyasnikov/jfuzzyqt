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
//#include "../membership/membershipfunction.h"
#include <QDebug>

jfuzzyqt::Value::Value(QObject* parent)
    :QObject(parent)
{
    type = UNDEFINED;
    valReal = 0.;
    varRef=NULL;
    min = 0.;
    max = 0.;
    vmin = NULL;
    vmax = NULL;
}
jfuzzyqt::Value::Value(QObject* parent, double value, double min, double max, bool abs)
    :QObject(parent)
{
    type = REAL;
    varRef=NULL;
    valReal = value;
    this->min = min;
    this->max = max;
    this->abs = abs;
    vmin = NULL;
    vmax = NULL;
}
jfuzzyqt::Value::Value(QObject* parent, double value, Value* vmin, Value* vmax, bool abs)
    :QObject(parent)
{
    type = REAL;
    varRef=NULL;
    valReal = value;
    min = value;
    max = value;
    this->vmin = vmin;
    this->vmax = vmax;
    this->abs = abs;
}
jfuzzyqt::Value::Value(QObject* parent, double value, Value* vmin, double max, bool abs)
    :QObject(parent)
{
    type = REAL;
    varRef=NULL;
    valReal = value;
    min = value;
    this->max = max;
    this->vmin = vmin;
    this->abs = abs;
    vmax = NULL;
}
jfuzzyqt::Value::Value(QObject* parent, double value, double min, Value* vmax, bool abs)
    :QObject(parent)
{
    type = REAL;
    varRef=NULL;
    valReal = value;
    this->min = min;
    this->abs = abs;
    max = value;
    vmin = NULL;
    this->vmax = vmax;
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
            if( varRef )
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
bool jfuzzyqt::Value::setValue(double value)
{
    bool toReturn = false;
    if(type == REAL)
    {
        if(varRef) min = varRef->getAbsoluteMinimum();
        if(varRef) max = varRef->getAbsoluteMaximum();
        if(vmin) min = qMax(min, vmin->getValue());
        if(vmax) max = qMin(max, vmax->getValue());
        if(value < min) valReal = min;
        if(value > max) valReal = max;
        if((value >= min) && (value <= max))
        {
            toReturn = true;
            if(parent()->inherits("jfuzzyqt::MembershipFunction"))
            {
                double temp = valReal;
                valReal = value;
                QString errors;
                if(!dynamic_cast<MembershipFunction*>(parent())->checkParameters(errors))
                {
                    toReturn = false;
                }
                valReal = temp;
            }
        }
    }
    if(toReturn)
    {
        valReal = value;
    }
    return toReturn;
}
double jfuzzyqt::Value::getEpsilon()const
{
    if(varRef) min = varRef->getAbsoluteMinimum();
    if(varRef) max = varRef->getAbsoluteMaximum();
    if(vmin) min = qMax(min, vmin->getValue());
    if(vmax) max = qMin(max, vmax->getValue());
    epsilon = qMin((max-min) / (varRef?1000.:100.),100.);
    return epsilon;
}
void jfuzzyqt::Value::setVariableReference(Variable*varRef)
{
    if(abs) this->varRef = varRef;
}
QString jfuzzyqt::Value::getVarName()const
{
    if(dynamic_cast<MembershipFunction*>(parent()))
    {
        return dynamic_cast<MembershipFunction*>(parent())->toString();
    }
    return QString::null;
}
