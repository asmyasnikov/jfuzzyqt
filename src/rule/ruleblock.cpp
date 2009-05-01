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
 * \version 0.95
 * \brief FIXME
 */
#include "ruleblock.h"
#include "../connection/ruleconnectionmethod.h"
#include "../connection/and/ruleconnectionmethodandmin.h"
#include "../connection/or/ruleconnectionmethodormax.h"
#include <QDebug>
#include <QStringList>

jfuzzyqt::RuleBlock::RuleBlock(QObject *parent) : QObject (parent)
{
    name = "Unknown";
    ruleActivationMethod=NULL;
    ruleAccumulationMethod = NULL;
    AND=NULL;
    OR=NULL;
    evaluateState = false;
}

jfuzzyqt::RuleBlock::RuleBlock(const QString& name) : QObject ()
{
    this->name = name;
    ruleActivationMethod=NULL;
    ruleAccumulationMethod = NULL;
    AND=NULL;
    OR=NULL;
    evaluateState = false;
}
jfuzzyqt::RuleBlock::RuleBlock(const RuleBlock &rb) : QObject ()
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
    evaluateState = false;
}
jfuzzyqt::RuleBlock::~RuleBlock()
{
}
void jfuzzyqt::RuleBlock::reset()
{
    QLinkedList<Rule>::iterator fr = rules.begin();
    int i = 0;
    while (fr != rules.end()) {
        fr->setDegreeOfSupport(0);
        fr->reset();
        fr++;
        i++;
    }
    evaluateState = false;
}

/*!
 * \brief Evaluate fuzzy rule set
 */
void jfuzzyqt::RuleBlock::evaluate()
{
    if(!evaluateState)
    {
        for(QSet<RuleBlock*>::const_iterator i = dependOfBlocks.begin(); i != dependOfBlocks.end(); i++)
        {
            (*i)->evaluate();
        }
        ///< Apply each rule
        for (QLinkedList<Rule>::iterator i = rules.begin(); i != rules.end(); ++i)
        {
            i->evaluate(ruleActivationMethod, ruleAccumulationMethod);
        }
        evaluateState = true;
    }
}
const QString& jfuzzyqt::RuleBlock::getName()const
{
    return name;
}
void jfuzzyqt::RuleBlock::debug(const QString& tbs) const
{
    qDebug() << tbs << toQString();
}
void jfuzzyqt::RuleBlock::addRuleActivationMethod(RuleActivationMethod* ruleActivationMethod)
{
    if (this->ruleActivationMethod!=NULL)
    {
        delete this->ruleActivationMethod;
    }
    this->ruleActivationMethod = ruleActivationMethod;
    this->ruleActivationMethod->setParent(this);
}
void jfuzzyqt::RuleBlock::addRuleAccumulationMethod(RuleAccumulationMethod* ruleAccumulationMethod)
{
    if (this->ruleAccumulationMethod!=NULL)
    {
        delete this->ruleAccumulationMethod;
    }
    this->ruleAccumulationMethod = ruleAccumulationMethod;
    this->ruleAccumulationMethod->setParent(this);

}
RuleActivationMethod* jfuzzyqt::RuleBlock::getRuleActivationMethod()const
{
    return ruleActivationMethod;
}
RuleAccumulationMethod* jfuzzyqt::RuleBlock::getRuleAccumulationMethod()const
{
    return ruleAccumulationMethod;
}
void jfuzzyqt::RuleBlock::addRule(const Rule &fuzzyRule)
{
    rules.append(fuzzyRule);
}
QString jfuzzyqt::RuleBlock::toQString()const
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

void jfuzzyqt::RuleBlock::setRuleConnectionMethodAnd(RuleConnectionMethod *AND)
{
    if( this->AND != NULL)
    {
        delete (this->AND);
    }
    this->AND = AND;
    this->AND->setParent(this);
}
void jfuzzyqt::RuleBlock::setRuleConnectionMethodOr(RuleConnectionMethod *OR)
{
    if( this->OR ) delete (this->OR);
    this->OR = OR;
    if( this->OR ) this->OR->setParent(this);
}
RuleConnectionMethod* jfuzzyqt::RuleBlock::getRuleConnectionMethodAnd()const
{
    return AND;
}
RuleConnectionMethod* jfuzzyqt::RuleBlock::getRuleConnectionMethodOr()const
{
    return OR;
}
int jfuzzyqt::RuleBlock::getRulesCount()const
{
    return rules.size();
}
QSet<QString> jfuzzyqt::RuleBlock::getInputVariables()const
{
    QStringList variableList;
    for (QLinkedList<Rule>::const_iterator i = rules.begin(); i != rules.end(); ++i)
    {
        variableList << i->getAntecedents()->getVariableList();
    }
    return variableList.toSet();
}
QSet<QString> jfuzzyqt::RuleBlock::getOutputVariables()const
{
    QStringList variableList;
    for (QLinkedList<Rule>::const_iterator i = rules.begin(); i != rules.end(); ++i)
    {
        const QList<RuleTerm*> ruleTerms = i->getConsequents();
        for(QList<RuleTerm*>::const_iterator j = ruleTerms.begin(); j != ruleTerms.end(); j++ )
        {
            variableList << (*j)->getVariable()->getName();
        }
    }
    return variableList.toSet();
}
void jfuzzyqt::RuleBlock::addDependOfBlock(RuleBlock*block)
{
    //Simple check
    Q_ASSERT(block != this);
    dependOfBlocks.insert(block);
}
bool jfuzzyqt::RuleBlock::checkDependences()const
{
    // Check depend from oneself (infinity cycle checking)
    QSet<QString>inputs  = getInputVariables();
    QSet<QString>outputs = getOutputVariables();
    if(QSet<QString>(inputs).intersect(outputs).size())return false;
    QSet<RuleBlock*>blocks = dependOfBlocks;
    int depth = 0;
    while(blocks.size() && (++depth < 512))
    {
        QSet<RuleBlock*>current;
        for(QSet<RuleBlock*>::const_iterator i = blocks.begin(); i != blocks.end(); i++)
        {
            current.unite((*i)->dependOfBlocks);
            inputs.unite((*i)->getInputVariables());
        }
        if(inputs.intersect(outputs).size())return false;
        blocks = current;
    }
    return true;
}
