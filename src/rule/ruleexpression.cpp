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
 * \file ruleexpression.cpp
 * \class RuleExpression
 * \author Marco Estanqueiro <estanqueiro.marco@gmail.com>
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 1.08
 * \brief FIXME
 */
#include "ruleexpression.h"
#include "../connection/ruleconnectionmethod.h"
#include "ruleterm.h"
#include <QDebug>
#include <QStringList>

jfuzzyqt::RuleExpression::RuleExpression(QObject *parent)
    : QObject(parent)
{
    term1Type = UNDEF;
    term2Type = UNDEF;
    negated = false;
}

jfuzzyqt::RuleExpression::~RuleExpression()
{
}

jfuzzyqt::RuleExpression::term_t jfuzzyqt::RuleExpression::getTerm1Type()const
{
    return term1Type;
}

jfuzzyqt::RuleExpression::term_t jfuzzyqt::RuleExpression::getTerm2Type()const
{
    return term2Type;
}

const RuleConnectionMethod* jfuzzyqt::RuleExpression::getRuleConnectionMethod()const
{
    return ruleConnectionMethod;
}

bool jfuzzyqt::RuleExpression::isNegated()const
{
    return negated;
}

RuleTerm* jfuzzyqt::RuleExpression::getTerm1Rule()const
{
    if ( term1Type==RULETERM )
    {
        return term1.ruleTerm;
    }else{
        qCritical() << "[jfuzzyqt::RuleExpression::getTerm1Rule]:Null term returned";
        return NULL;
    }
}

RuleTerm* jfuzzyqt::RuleExpression::getTerm2Rule()const
{
    if ( term2Type==RULETERM )
    {
        return term2.ruleTerm;
    }else{
        qCritical() << "[jfuzzyqt::RuleExpression::getTerm2Rule]:Null term returned";
        return NULL;
    }
}

RuleExpression* jfuzzyqt::RuleExpression::getTerm1Expression()const
{
    if ( term1Type==RULEEXPRESSION )
    {
        return term1.ruleExpression;
    }else{
        qCritical() << "[jfuzzyqt::RuleExpression::getTerm1Expression]:Null term returned";
        return NULL;
    }
}

RuleExpression* jfuzzyqt::RuleExpression::getTerm2Expression()const
{
    if ( term2Type==RULEEXPRESSION )
    {
        return term2.ruleExpression;
    }else{
        qCritical() << "[jfuzzyqt::RuleExpression::getTerm2Expression]:Null term returned";
        return NULL;
    }
}

void jfuzzyqt::RuleExpression::addTerm1Rule(RuleTerm *ruleTerm)
{
    term1Type = RULETERM;
    term1.ruleTerm = ruleTerm;
    term1.ruleTerm->setParent(this);
}

void jfuzzyqt::RuleExpression::addTerm2Rule(RuleTerm *ruleTerm)
{
    term2Type = RULETERM;
    term2.ruleTerm = ruleTerm;
    term2.ruleTerm->setParent(this);
}

void jfuzzyqt::RuleExpression::addTerm1Expression(RuleExpression *ruleExpression)
{
    term1Type = RULEEXPRESSION;
    term1.ruleExpression = ruleExpression;
    term1.ruleExpression->setParent(this);
}

void jfuzzyqt::RuleExpression::addTerm2Expression(RuleExpression *ruleExpression)
{
    term2Type = RULEEXPRESSION;
    term2.ruleExpression = ruleExpression;
    term2.ruleExpression->setParent(this);
}

void jfuzzyqt::RuleExpression::setRuleConnectionMethod(const RuleConnectionMethod* ruleConnectionMethod)
{
    this->ruleConnectionMethod = ruleConnectionMethod;
}

QString jfuzzyqt::RuleExpression::toString()const
{
    QString EXPRESSION;
    QString LEFT;
    QString RIGHT;
    switch (term1Type)
    {
        case RULETERM:
            if(term1.ruleTerm->isValid())
            {
                LEFT.append(term1.ruleTerm->toString());
            }
            break;
        case RULEEXPRESSION:
            LEFT.append(QString("(%1)").arg(term1.ruleExpression->toString()));
            break;
        case UNDEF:
            break;
    }
    switch (term2Type)
    {
        case RULETERM:
            if(term2.ruleTerm->isValid())
            {
                RIGHT.append(term2.ruleTerm->toString());
            }
            break;
        case RULEEXPRESSION:
            RIGHT.append(QString("(%1)").arg(term2.ruleExpression->toString()));
            break;
        case UNDEF:
            break;
    }
    if((ruleConnectionMethod)&&(LEFT.length() && RIGHT.length()))
    {
        EXPRESSION.append(QString("%1 %2 %3")
                          .arg(LEFT)
                          .arg(ruleConnectionMethod->getName().toUpper())
                          .arg(RIGHT));
    }else if(LEFT.length()){
        EXPRESSION.append(LEFT);
    }else if(RIGHT.length()){
        EXPRESSION.append(RIGHT);
    }
    return EXPRESSION;
}

void jfuzzyqt::RuleExpression::reset()
{
    switch (term1Type)
    {
        case RULETERM:
            if(term1.ruleTerm->isValid())
            {
                term1.ruleTerm->getVariable()->reset();
            }
            break;
        case RULEEXPRESSION:
            term1.ruleExpression->reset();
            break;
        case UNDEF:
            qWarning() << "[jfuzzyqt::RuleExpression::reset]:Error reseting term1";
            break;
    }
    switch (term2Type)
    {
        case RULETERM:
            if(term2.ruleTerm->isValid())
            {
                term2.ruleTerm->getVariable()->reset();
            }
            break;
        case RULEEXPRESSION:
            term2.ruleExpression->reset();
            break;
        case UNDEF:
            qWarning() << "[jfuzzyqt::RuleExpression::reset]:Error reseting term2";
            break;
    }
}

double jfuzzyqt::RuleExpression::evaluate()
{
    // Results for each term
    double resTerm1 = 0.0;
    double resTerm2 = 0.0;

    // Evaluate term1: if it's an expression => recursive
    if( term1Type == RULEEXPRESSION ) resTerm1 = term1.ruleExpression->evaluate();
    else if( term1Type == RULETERM && term1.ruleTerm->isValid() )
    {
        resTerm1 = term1.ruleTerm->getMembership();
    }

    // Evaluate term2: if it's an expression => recursive
    if( term2Type == RULEEXPRESSION ) resTerm2 = term2.ruleExpression->evaluate();
    else if( term2Type == RULETERM && term2.ruleTerm->isValid() )
    {
        resTerm2 = term2.ruleTerm->getMembership();
    }
    double result;
    result = ruleConnectionMethod->connect(resTerm1, resTerm2);
    // Is this clause negated?
    if( negated )
    {
        result = 1 - result;
    }
    return result;
}
QStringList jfuzzyqt::RuleExpression::getVariableList()const
{
    QStringList variableList;
    switch (term1Type)
    {
        case RULETERM:
            if(term1.ruleTerm->isValid())
            {
                variableList << term1.ruleTerm->getVariable()->getName();
            }
            break;
        case RULEEXPRESSION:
            variableList << term1.ruleExpression->getVariableList();
            break;
        case UNDEF:
            qWarning() << "[jfuzzyqt::RuleExpression::reset]:Error reseting term1";
            break;
    }
    switch (term2Type)
    {
        case RULETERM:
            if(term2.ruleTerm->isValid())
            {
                variableList << term2.ruleTerm->getVariable()->getName();
            }
            break;
        case RULEEXPRESSION:
            variableList << term2.ruleExpression->getVariableList();
            break;
        case UNDEF:
            qWarning() << "[jfuzzyqt::RuleExpression::reset]:Error reseting term2";
            break;
    }
    return variableList;
}
