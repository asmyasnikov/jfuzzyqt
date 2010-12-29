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
 * \file ruleterm.cpp
 * \class RuleTerm
 * \author Marco Estanqueiro <estanqueiro.marco@gmail.com>
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 1.08
 * \brief FIXME
 */
#include "ruleterm.h"
#include <QDebug>

jfuzzyqt::RuleTerm::RuleTerm(QObject* parent) : QObject(parent)
{
    variable = NULL;
    termName = "Undefined";
    negated = false;
}
jfuzzyqt::RuleTerm::RuleTerm(QObject* parent, Variable* variable, const QString& term, bool negated)
    : QObject(parent)
{
    this->variable = variable;
    this->termName = term;
    this->negated = negated;
    Q_ASSERT(this->variable);
}
jfuzzyqt::RuleTerm::~RuleTerm()
{
}
bool jfuzzyqt::RuleTerm::isValid() const
{
    return (termName != "Undefined");
}
const MembershipFunction* jfuzzyqt::RuleTerm::getMembershipFunction()
{
    Q_ASSERT(variable);
    return variable->getMembershipFunction(termName);
}
const QString& jfuzzyqt::RuleTerm::getName()const
{
    return termName;
}
void jfuzzyqt::RuleTerm::setName(const QString &name)
{
    termName = name;
}
bool jfuzzyqt::RuleTerm::isNegated() const
{
    return negated;
}
void jfuzzyqt::RuleTerm::setNegated(const bool& value)
{
    negated = value;
}

Variable* jfuzzyqt::RuleTerm::getVariable()const
{
    Q_ASSERT(variable);
    return variable;
}
void jfuzzyqt::RuleTerm::setVariable(Variable* variable)
{
    this->variable = variable;
    if(this->variable)
    {
        this->variable->setParent(this);
    }
    Q_ASSERT(this->variable);
}

QString jfuzzyqt::RuleTerm::toString()const
{
    QString RULETERM;
    if ( variable && !variable->getName().isEmpty() )
    {
        RULETERM.append(variable->getName());
    }
    if ( negated )
    {
        RULETERM.append(" IS NOT ");
    }else{
        RULETERM.append(" IS ");
    }
    RULETERM.append(getName());
    return RULETERM;
}
double jfuzzyqt::RuleTerm::getMembership()const
{
    Q_ASSERT(variable);
    double memb = variable->getMembership(termName);
    if( negated ) memb = 1.0 - memb;
    return memb;
}
