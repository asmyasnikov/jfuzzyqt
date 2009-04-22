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
 * \file ruleblock.h
 * \class FIXME
 * \author Marco Estanqueiro
 * \author Aleksey Myasnikov
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 0.2
 * \brief FIXME
 */
#ifndef RULEBLOCK_H
#define RULEBLOCK_H

#include "../activation/ruleactivationmethod.h"
#include "../accumulation/ruleaccumulationmethod.h"
#include "rule.h"
#include "../connection/ruleconnectionmethod.h"
#include <QString>
#include <QLinkedList>
#include <QObject>

class RuleBlock : public QObject
{
    Q_OBJECT

public:
    RuleBlock(QObject *parent=NULL);
    RuleBlock(const QString& name);
    RuleBlock(const RuleBlock &rb);
    ~RuleBlock();
    void reset();
    void evaluate();
    const QString& getName()const;
    void debug(const QString& tbs) const;
    void addRuleActivationMethod(RuleActivationMethod* ruleActivationMethod);
    void addRuleAccumulationMethod(RuleAccumulationMethod* ruleAccumulationMethod);
    RuleActivationMethod* getRuleActivationMethod()const;
    RuleAccumulationMethod* getRuleAccumulationMethod()const;
    void addRule(const Rule &fuzzyRule);
    QString toQString()const;
    RuleConnectionMethod* getRuleConnectionMethodAnd()const;
    void setRuleConnectionMethodAnd(RuleConnectionMethod *_and_);
    RuleConnectionMethod* getRuleConnectionMethodOr()const;
    void setRuleConnectionMethodOr(RuleConnectionMethod *_or_);

private:
    QString name;

    ///< Rule accumulation method: How results of the rules are combined to obtain an overall result (e.g. MAX: maximum, BSUM: bounded sum, etc.)
    RuleAccumulationMethod* ruleAccumulationMethod;

    ///< Rule activation (implication) method: How the 'if' activates the 'then' (e.g. MIN: minimum, PROD: product)
    RuleActivationMethod* ruleActivationMethod;

    ///< All the rules
    QLinkedList<Rule> rules;

    RuleConnectionMethod *AND;
    RuleConnectionMethod *OR;
};

#endif // RULEBLOCK_H