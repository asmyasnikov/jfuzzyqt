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
 * \file ruleterm.cpp
 * \class RuleTerm
 * \author Marco Estanqueiro <estanqueiro.marco@gmail.com>
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 0.78
 * \brief FIXME
 */
#include "ruleterm.h"
#include <QDebug>

RuleTerm::RuleTerm(QObject* parent) : QObject(parent)
{
    variable = NULL;
    termName = "Undefined";
    negated = false;
}
RuleTerm::RuleTerm(QObject* parent, Variable* variable, const QString& term, bool negated)
    : QObject(parent)
{
    this->variable = variable;
    if(this->variable)
    {
        this->variable->setParent(this);
    }
    termName = term;
    negated = negated;
    Q_ASSERT(this->variable);
}
RuleTerm::~RuleTerm()
{
}
bool RuleTerm::isValid() const
{
    return (termName != "Undefined");
}
const MembershipFunction* RuleTerm::getMembershipFunction()
{
    Q_ASSERT(variable);
    return variable->getMembershipFunction(termName);
}
const QString& RuleTerm::getName()const
{
    return termName;
}
void RuleTerm::setName(const QString &name)
{
    termName = name;
}
bool RuleTerm::isNegated() const
{
    return negated;
}
void RuleTerm::setNegated(const bool& value)
{
    negated = value;
}

Variable* RuleTerm::getVariable()const
{
    Q_ASSERT(variable);
    return variable;
}
void RuleTerm::setVariable(Variable* variable)
{
    this->variable = variable;
    if(this->variable)
    {
        this->variable->setParent(this);
    }
    Q_ASSERT(this->variable);
}

QString RuleTerm::toQString()const
{
    QString str = "";
    if ( variable && !variable->getName().isEmpty() )
    {
        str += variable->getName();
    }else{
        str += "Null variable";
    }
    if ( negated )
    {
        str += " is not ";
    }else{
        str += " is ";
    }
    str += getName();
    return str;
}
double RuleTerm::getMembership()const
{
    Q_ASSERT(variable);
    double memb = variable->getMembership(termName);
    if( negated ) memb = 1.0 - memb;
    return memb;
}
