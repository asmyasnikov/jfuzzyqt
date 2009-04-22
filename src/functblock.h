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
 * \file functblock.h
 * \class FIXME
 * \author Marco Estanqueiro
 * \author Aleksey Myasnikov
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 0.2
 * \brief FIXME
 */
#ifndef FUNCTBLOCK_H
#define FUNCTBLOCK_H

#include <QString>
#include <QHash>
#include <QDebug>
#include <QObject>
#include "rule/variable.h"
#include "rule/ruleblock.h"
#include "defuzzifier/defuzzifier.h"


class FunctBlock : public QObject
{
	Q_OBJECT

public:
    FunctBlock(QObject* parent=NULL);
    FunctBlock(QObject* parent,const QString& name);
    FunctBlock(const FunctBlock &fb);
    ~FunctBlock();

    const QString& getName()const;
    void setName(const QString& name);
    Defuzzifier* createDefuzzifier(const QString& defuzzType);
    bool setValue(const QString& varName, const double& value);
    void evaluate();
    double getValue(const QString& varName)const;
    bool addVariable(const QString& varName, Variable* variable);
    bool setVariable(const QString& varName, LinguisticTerm* lt);
    Variable* getVariable(const QString& varName);
    bool setDefaultValue(const QString& varName,const double value);
    bool setDefuzzifier(const QString& varName, Defuzzifier* d);
    bool addRuleBlock(RuleBlock* rl);
    void debug(const QString& tbs) const;
    QHash<QString, RuleBlock*> getRuleBlocks()const;
    QHash<QString, Variable*> getVariables()const;

    //FunctBlock operator=(const FunctBlock &fb);
private:
    QString name; ///<Function block name
    QHash<QString, RuleBlock*> ruleBlocks; ///<Several RuleBlocks indexed by name
    QHash<QString, Variable*> variables; ///<Every variable is here (key: VariableName)
};

#endif // FUNCTBLOCK_H