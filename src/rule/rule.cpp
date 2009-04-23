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
 * \file rule.cpp
 * \class Rule
 * \author Marco Estanqueiro <estanqueiro.marco@gmail.com>
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 0.2
 * \brief FIXME
 */
#include "rule.h"
#include <QDebug>

Rule::Rule(QObject *parent)
    : QObject(parent)
{
    name = "undefined";
    weight=1;
}

Rule::Rule(QObject *parent, const QString& name)
    : QObject(parent)
{
    this->name = name;
    weight=1;
}
Rule::Rule(const Rule &rule)
    : QObject(rule.parent())
{
    name = rule.getName();
    addAntecedents(rule.getAntecedents());
    consequents = rule.getConsequents();
    weight= rule.getWeight();
}
Rule::~Rule()
{
}
void Rule::addAntecedents(RuleExpression *antecedents)
{
    this->antecedents = antecedents;
    this->antecedents->setParent(this);
}
void Rule::addConsequent(RuleTerm* rt)
{
    rt->setParent(this);
    consequents.append(rt);
}
const QString& Rule::getName()const
{
    return name;
}
RuleExpression* Rule::getAntecedents()const
{
    return antecedents;
}
const QList<RuleTerm*> Rule::getConsequents()const
{
        return consequents;
}
QString Rule::toQString() const
{
    QString str;
    str += "Rule (";
    str += getName();
    str += ")\n{\n";
    str += "antecedents: ";
    if ( !antecedents )
    {
        str += "NULL\n";
    }else{
        str += antecedents->toQString(); ///< antecedents problem!!
        str += "\n";
    }
    str += "consequents: ";
    for (int i = 0; i < consequents.size(); ++i) {
         str += consequents.at(i)->toQString();
         str += "\n";
    }
    str += "}";
    return str;
}
void Rule::setDegreeOfSupport(const double& degreeOfSupport)
{
    this->degreeOfSupport = degreeOfSupport;
}
void Rule::reset()
{
    for (int i = 0; i < consequents.size(); ++i)
    {
        consequents.at(i)->getVariable()->reset();
    }
    antecedents->reset();
}
void  Rule::evaluate(RuleActivationMethod* act,RuleAccumulationMethod* accu)
{
    double tmp = antecedents->evaluate(); ///< Evaluate antecedents
    degreeOfSupport = tmp;
    ///< Apply weight
    degreeOfSupport *= weight;

    ///< Imply rule consequents: Apply degreeOfSupport to consequent linguisticTerms
    for (int i = 0; i < consequents.size(); ++i) {
        act->imply(consequents.at(i),accu,degreeOfSupport);
    }
}
double Rule::getWeight()const
{
    return weight;
}
