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
 * \file ruleblock.cpp
 * \class RuleBlock
 * \author Marco Estanqueiro <estanqueiro.marco@gmail.com>
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 0.83
 * \brief FIXME
 */
#include "ruleblock.h"
#include "../connection/ruleconnectionmethod.h"
#include "../connection/and/ruleconnectionmethodandmin.h"
#include "../connection/or/ruleconnectionmethodormax.h"
#include <QDebug>

RuleBlock::RuleBlock(QObject *parent) : QObject (parent)
{
    name = "Unknown";
    ruleActivationMethod=NULL;
    ruleAccumulationMethod = NULL;
    AND=NULL;
    OR=NULL;
}

RuleBlock::RuleBlock(const QString& name) : QObject ()
{
    this->name = name;
    ruleActivationMethod=NULL;
    ruleAccumulationMethod = NULL;
    AND=NULL;
    OR=NULL;
}
RuleBlock::RuleBlock(const RuleBlock &rb) : QObject ()
{
    name = rb.getName();
    ruleActivationMethod = NULL;
    ruleAccumulationMethod = NULL;
    addRuleActivationMethod ( rb.getRuleActivationMethod() );
    addRuleAccumulationMethod ( rb.getRuleAccumulationMethod() );

    AND=NULL;
    OR=NULL;
    setRuleConnectionMethodAnd( rb.getRuleConnectionMethodAnd() );
    setRuleConnectionMethodOr( rb.getRuleConnectionMethodOr() );
}
RuleBlock::~RuleBlock()
{
}
void RuleBlock::reset()
{
    QLinkedList<Rule>::iterator fr = rules.begin();
    int i = 0;
    while (fr != rules.end()) {
        fr->setDegreeOfSupport(0);
        fr->reset();
        fr++;
        i++;
    }
}

/*!
 * \brief Evaluate fuzzy rule set
 */
void RuleBlock::evaluate()
{
    ///< Apply each rule
    QLinkedList<Rule>::iterator i;
    for (i = rules.begin(); i != rules.end(); ++i)
    {
        i->evaluate(ruleActivationMethod, ruleAccumulationMethod);
    }
}
const QString& RuleBlock::getName()const
{
    return name;
}
void RuleBlock::debug(const QString& tbs) const
{
    qDebug() << tbs << toQString();
}
void RuleBlock::addRuleActivationMethod(RuleActivationMethod* ruleActivationMethod)
{
    if (this->ruleActivationMethod!=NULL)
    {
        delete this->ruleActivationMethod;
    }
    this->ruleActivationMethod = ruleActivationMethod;
    this->ruleActivationMethod->setParent(this);
}
void RuleBlock::addRuleAccumulationMethod(RuleAccumulationMethod* ruleAccumulationMethod)
{
    if (this->ruleAccumulationMethod!=NULL)
    {
        delete this->ruleAccumulationMethod;
    }
    this->ruleAccumulationMethod = ruleAccumulationMethod;
    this->ruleAccumulationMethod->setParent(this);

}
RuleActivationMethod* RuleBlock::getRuleActivationMethod()const
{
    return ruleActivationMethod;
}
RuleAccumulationMethod* RuleBlock::getRuleAccumulationMethod()const
{
    return ruleAccumulationMethod;
}
void RuleBlock::addRule(const Rule &fuzzyRule)
{
    rules.append(fuzzyRule);
}
QString RuleBlock::toQString()const
{
    QString tmp;
    tmp += "RuleBlock(";
    tmp += name;
    tmp += ")\n{\n";
    tmp += "ruleAccumulationMethod: ";
    if ( ruleAccumulationMethod != NULL )
    {
        tmp += ruleAccumulationMethod->toQString();
        tmp += "\n";
    }
    else
    {
        tmp += "NULL\n";
    }

    tmp += "ruleActivationMethod: ";
    if ( ruleActivationMethod != NULL )
    {
        tmp += ruleActivationMethod->toQString();
        tmp += "\n";
    }
    else
    {
            tmp += " NULL\n";
    }

    QLinkedList<Rule>::const_iterator i = rules.begin();
    while (i != rules.end()) {
        tmp += i->toQString();
        tmp += "\n";
        i++;
    }
    tmp += "}";
    return tmp;
}

void RuleBlock::setRuleConnectionMethodAnd(RuleConnectionMethod *AND)
{
    if( this->AND != NULL)
    {
        delete (this->AND);
    }
    this->AND = AND;
    this->AND->setParent(this);
}
void RuleBlock::setRuleConnectionMethodOr(RuleConnectionMethod *OR)
{
    if( this->OR ) delete (this->OR);
    this->OR = OR;
    if( this->OR ) this->OR->setParent(this);
}
RuleConnectionMethod* RuleBlock::getRuleConnectionMethodAnd()const
{
    return AND;
}
RuleConnectionMethod* RuleBlock::getRuleConnectionMethodOr()const
{
    return OR;
}
int RuleBlock::getRulesCount()const
{
    return rules.size();
}
