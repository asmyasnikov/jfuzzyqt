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
 * \version 0.95
 * \brief FIXME
 */
#include "rule.h"
#include "../optimization/value.h"
#include <QDebug>

jfuzzyqt::Rule::Rule(QObject *parent)
    : OptimizationParameters(parent)
{
    name = "undefined";
    parameters.append(new Value(this, 1.0));
}

jfuzzyqt::Rule::Rule(QObject *parent, const QString& name)
    : OptimizationParameters(parent)
{
    this->name = name;
    parameters.append(new Value(this, 1.0));
}
jfuzzyqt::Rule::Rule(const Rule &rule)
    : OptimizationParameters(rule.parent())
{
    name = rule.getName();
    addAntecedents(rule.getAntecedents());
    consequents = rule.getConsequents();
    parameters.append(new Value(this, rule.getWeight()));
}
jfuzzyqt::Rule::~Rule()
{
}
void jfuzzyqt::Rule::addAntecedents(RuleExpression *antecedents)
{
    this->antecedents = antecedents;
    if(this->antecedents) this->antecedents->setParent(this);
}
void jfuzzyqt::Rule::addConsequent(RuleTerm* rt)
{
    for (int i = 0; i < consequents.size(); ++i)
    {
        if((consequents.at(i)->getVariable()->getName() == rt->getVariable()->getName())&&
           (consequents.at(i)->getName() == rt->getName()))
        {
            delete rt;
            return;
        }
    }
    rt->setParent(this);
    consequents.append(rt);
}
const QString& jfuzzyqt::Rule::getName()const
{
    return name;
}
RuleExpression* jfuzzyqt::Rule::getAntecedents()const
{
    return antecedents;
}
const QList<RuleTerm*> jfuzzyqt::Rule::getConsequents()const
{
    return consequents;
}
QString jfuzzyqt::Rule::toQString() const
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
        str += antecedents ?
               antecedents->toQString() :
               QString::null; ///< antecedents problem!!
        str += "\n";
    }
    str += "consequents: ";
    for (int i = 0; i < consequents.size(); ++i) {
         str += consequents.at(i)->toQString();
         str += "\n";
    }
    str += "weight: ";
    str += QString::number(parameters.at(0)->getValue(), 'f', 3);
    str += "\n";
    str += "}";
    return str;
}
void jfuzzyqt::Rule::setDegreeOfSupport(const double& degreeOfSupport)
{
    this->degreeOfSupport = degreeOfSupport;
}
void jfuzzyqt::Rule::reset()
{
    for (int i = 0; i < consequents.size(); ++i)
    {
        consequents.at(i)->getVariable()->reset();
    }
    if(antecedents) antecedents->reset();
}
void  jfuzzyqt::Rule::evaluate(RuleActivationMethod* act,RuleAccumulationMethod* accu)
{
    Q_ASSERT(antecedents);
    Q_ASSERT(consequents.size());
    degreeOfSupport = antecedents->evaluate(); ///< Evaluate antecedents
    ///< Apply weight
    degreeOfSupport *= parameters.at(0)->getValue();
    ///< Imply rule consequents: Apply degreeOfSupport to consequent linguisticTerms
    for (int i = 0; i < consequents.size(); ++i) {
        act->imply(consequents.at(i),accu,degreeOfSupport);
    }
}
double jfuzzyqt::Rule::getWeight()const
{
    return parameters.at(0)->getValue();
}
void jfuzzyqt::Rule::setWeight(double weight)
{
    Q_ASSERT((weight >= 0.) && (weight <= 1.0));
    parameters.at(0)->setValue(weight);
}
