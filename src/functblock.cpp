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
 * \file functblock.cpp
 * \class FunctBlock
 * \author Marco Estanqueiro <estanqueiro.marco@gmail.com>
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 0.83
 * \brief FIXME
 */
#include "functblock.h"
#include "defuzzifier/defuzzifiercenterofgravity.h"
#include "defuzzifier/defuzzifiercenterofgravitysingletons.h"

FunctBlock::FunctBlock(QObject* parent) : QObject (parent)
{
}
FunctBlock::FunctBlock(QObject* parent,const QString& name) : QObject (parent)
{
    this->name = name;
}
FunctBlock::FunctBlock(const FunctBlock &fb) : QObject (fb.parent())
{
    name = fb.getName();
    ruleBlocks = fb.getRuleBlocks();
    variables = fb.getVariables();
}
FunctBlock::~FunctBlock()
{

}
const QString& FunctBlock::getName()const
{
    return name;
}
void FunctBlock::setName(const QString& name)
{
    this->name = name;
}

bool FunctBlock::addVariable(const QString& varName, Variable* variable)
{
    bool toReturn = false;
    if ( !variables.contains(varName) )
    {
        variables.insert(varName, variable);
        variable->setParent(this);
        toReturn = true;
    }
    return toReturn;
}

bool FunctBlock::setVariable(const QString& varName, LinguisticTerm* lt)
{
    QHash<QString, Variable*>::iterator i = variables.find(varName);
    if ( i != variables.end() )
    {
        i.value()->addLinguisticTerm(lt);
        return true;
    }else
    {
        qWarning() << "[FunctBlock::setVariable]: Variable '" << varName << "' does not exist";
    }
    return false;
}
Variable* FunctBlock::getVariable(const QString& varName)
{
    QHash<QString, Variable*>::iterator i = variables.find(varName);
    if ( i!= variables.end() )
    {
        return i.value();
    }else{
        qWarning() << "[FunctBlock::getVariable]:Unknwon variable";
        return NULL;
    }
}
bool FunctBlock::setDefaultValue(const QString& varName,const double value)
{
    QHash<QString, Variable*>::iterator i = variables.find(varName);
    if ( i != variables.end() )
    {
        i.value()->setDefaultValue(value);
        return true;
    }else
    {
        qWarning() << "[FunctBlock::setVariable]: Variable '" << varName << "' does not exist";
    }
    return false;
}
bool FunctBlock::setDefuzzifier(const QString& varName, Defuzzifier* d)
{
    QHash<QString, Variable*>::iterator i = variables.find(varName);
    if ( i != variables.end() )
    {
        i.value()->setDefuzzifier(d);
        if(i.value()->isOutputVariable())
        {
            d->setMin(i.value()->getAbsoluteMinimum());
            d->setMax(i.value()->getAbsoluteMaximum());
        }
        return true;
    }else{
        qWarning() << "[FunctBlock::setVariable]: Variable '" << varName << "' does not exist";
    }
    return false;
}
Defuzzifier* FunctBlock::createDefuzzifier(const QString& defuzzType)
{
    Defuzzifier* defuzzifier = NULL;
    if( defuzzType == "cog" )
    {
        defuzzifier = new DefuzzifierCenterOfGravity();
    }else if( defuzzType == "cogs" ){
        defuzzifier = new DefuzzifierCenterOfGravitySingletons();
    }
    else if( defuzzType == "cogf" )
    {
        //defuzzifier = new DefuzzifierCenterOfGravityFunctions(variable);
        QString error = "Unknown/Unimplemented Rule defuzzification method '";
        error.append( defuzzType );
        error.append( "\'" );
        qCritical() << error.toLocal8Bit().data();
    }
    else if( defuzzType == "coa" )
    {
        //defuzzifier = new DefuzzifierCenterOfArea(variable);
        QString error = "Unknown/Unimplemented Rule defuzzification method '";
        error.append( defuzzType );
        error.append( "\'" );
        qCritical() << error.toLocal8Bit().data();
    }
    else if( defuzzType =="lm" )
    {
        //defuzzifier = new DefuzzifierLeftMostMax(variable);
        QString error = "Unknown/Unimplemented Rule defuzzification method '";
        error.append( defuzzType );
        error.append( "\'" );
        qCritical() << error.toLocal8Bit().data();
    }
    else if( defuzzType == "rm" )
    {
        //defuzzifier = new DefuzzifierRightMostMax(variable);
        QString error = "Unknown/Unimplemented Rule defuzzification method '";
        error.append( defuzzType );
        error.append( "\'" );
        qCritical() << error.toLocal8Bit().data();
    }
    else if( defuzzType == "mm" )
    {
        //defuzzifier = new DefuzzifierMeanMax(variable);
        QString error = "Unknown/Unimplemented Rule defuzzification method '";
        error.append( defuzzType );
        error.append( "\'" );
        qCritical() << error.toLocal8Bit().data();
    }
    else {
        QString error = "Unknown/Unimplemented Rule defuzzification method ";
        error.append( defuzzType );
        error.append( "\'" );
        qCritical() << error.toLocal8Bit().data();
    }
    return defuzzifier;
}

bool FunctBlock::setValue(const QString& varName, const double& value)
{
    bool toReturn = false;
    QHash<QString, Variable*>::iterator i = variables.find(varName);
    if (i != variables.end())
    {
        i.value()->setValue(value);
    }else{
        qCritical() << "[FunctBlock::setValue]:no variable found";
    }
    return toReturn;
}

/*! \brief Evaluate fuzzy rules in this function block
*/
void FunctBlock::evaluate()
{
    ///<First: Reset defuzzifiers, variables, etc.
    QHashIterator<QString, RuleBlock*> i(ruleBlocks);
    while (i.hasNext()) {
        i.next();
        i.value()->reset();
    }
    ///<Second: Evaluate each RuleBlock
    QHashIterator<QString, RuleBlock*> j(ruleBlocks);
    while (j.hasNext()) {
        j.next();
        j.value()->evaluate();
    }

    ///<Third: Defuzzify each consequent variable
    QHashIterator<QString, Variable*> var(variables);
    while ( var.hasNext() ) {
        var.next();
        if( var.value()->isOutputVariable() )
        {
            var.value()->defuzzify();
        }
    }
}

double FunctBlock::getValue(const QString& varName)const
{
    double toReturn = 0.;
    if ( variables.contains( varName ) )
    {
        toReturn = variables.value(varName)->getValue();
    }
    return toReturn;
}

bool FunctBlock::addRuleBlock(RuleBlock* rl)
{
    bool toReturn = false;
    if ( !ruleBlocks.contains(rl->getName()) )
    {
        ruleBlocks.insert( rl->getName(), rl );
        rl->setParent(this);
        toReturn = true;
    }else{
        qWarning() << "[FunctBlock::addRuleBlock]:Duplicated RuleBlock wasn't added"<< rl->getName();
    }
    return toReturn;
}

void FunctBlock::debug(const QString& tbs)const
{
    QString nxTbs = tbs;
    nxTbs.append("\t");

    qDebug() << tbs << "Debuging" << name;

    qDebug() << tbs << "VARIABLES{";
    QHashIterator<QString, Variable*> var(variables);
    while ( var.hasNext() ) {
        var.next();
        var.value()->debug(nxTbs);
    }
    qDebug() << tbs << "}";

    qDebug() << tbs << "RULE BLOCK{";
    QHashIterator<QString, RuleBlock*> j(ruleBlocks);
    while (j.hasNext()) {
        j.next();
        j.value()->debug(nxTbs);
    }
    qDebug() << tbs << "}";
}

/*FunctBlock FunctBlock::operator=(const FunctBlock &fb)
{
    FunctBlock tmp(fb);
    return tmp;
}*/
QHash<QString, RuleBlock*> FunctBlock::getRuleBlocks()const
{
    return ruleBlocks;
}
QHash<QString, Variable*> FunctBlock::getVariables()const
{
    return variables;
}
