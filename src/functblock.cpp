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
 * \version 1.07
 * \brief FIXME
 */
#include "functblock.h"
#include "defuzzifier/defuzzifiercenterofgravity.h"
#include "defuzzifier/defuzzifiercenterofgravitysingletons.h"
#include <QStringList>

jfuzzyqt::FunctBlock::FunctBlock(QObject* parent) : QObject (parent)
{
}
jfuzzyqt::FunctBlock::FunctBlock(QObject* parent,const QString& name) : QObject (parent)
{
    this->name = name;
}
jfuzzyqt::FunctBlock::FunctBlock(const FunctBlock &fb) : QObject (fb.parent())
{
    name = fb.getName();
    ruleBlocks = fb.getRuleBlocks();
    variables = fb.getVariables();
}
jfuzzyqt::FunctBlock::~FunctBlock()
{

}
const QString& jfuzzyqt::FunctBlock::getName()const
{
    return name;
}
void jfuzzyqt::FunctBlock::setName(const QString& name)
{
    this->name = name;
}

bool jfuzzyqt::FunctBlock::addVariable(const QString& varName, Variable* variable)
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

bool jfuzzyqt::FunctBlock::setVariable(const QString& varName, LinguisticTerm* lt)
{
    QHash<QString, Variable*>::iterator i = variables.find(varName);
    if ( i != variables.end() )
    {
        i.value()->addLinguisticTerm(lt);
        return true;
    }else{
        qWarning() << "[FunctBlock::setVariable]: Variable '" << varName << "' does not exist";
    }
    return false;
}
Variable* jfuzzyqt::FunctBlock::getVariable(const QString& varName)
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
bool jfuzzyqt::FunctBlock::setDefaultValue(const QString& varName,const double value)
{
    QHash<QString, Variable*>::iterator i = variables.find(varName);
    if ( i != variables.end() )
    {
        i.value()->setDefaultValue(value);
        return true;
    }else{
        qWarning() << "[FunctBlock::setVariable]: Variable " << varName << " does not exist";
    }
    return false;
}
bool jfuzzyqt::FunctBlock::setDefuzzifier(const QString& varName, Defuzzifier* d)
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
Defuzzifier* jfuzzyqt::FunctBlock::createDefuzzifier(const QString& defuzzType)
{
    Defuzzifier* defuzzifier = NULL;
    if( defuzzType == "cog" )
    {
        defuzzifier = new DefuzzifierCenterOfGravity();
    }else if( defuzzType == "cogs" ){
        defuzzifier = new DefuzzifierCenterOfGravitySingletons();
    }else if( defuzzType == "cogf" ){
        //defuzzifier = new DefuzzifierCenterOfGravityFunctions(variable);
    }else if( defuzzType == "coa" ){
        //defuzzifier = new DefuzzifierCenterOfArea(variable);
    }else if( defuzzType =="lm" ){
        //defuzzifier = new DefuzzifierLeftMostMax(variable);
    }else if( defuzzType == "rm" ){
        //defuzzifier = new DefuzzifierRightMostMax(variable);
    }else if( defuzzType == "mm" ){
        //defuzzifier = new DefuzzifierMeanMax(variable);
    }
    if(!defuzzifier)
    {
        QString error = "Unknown/Unimplemented Rule defuzzification method ";
        error.append( defuzzType );
        error.append( "\'" );
        qCritical() << error.toLocal8Bit().data();
    }
    return defuzzifier;
}

bool jfuzzyqt::FunctBlock::setValue(const QString& varName, const double& value)
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
void jfuzzyqt::FunctBlock::evaluate()
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

double jfuzzyqt::FunctBlock::getValue(const QString& varName)const
{
    double toReturn = 0.;
    if ( variables.contains( varName ) )
    {
        toReturn = variables.value(varName)->getValue();
    }
    return toReturn;
}

bool jfuzzyqt::FunctBlock::addRuleBlock(RuleBlock* rb)
{
    bool toReturn = false;
    if ( !ruleBlocks.contains(rb->getName()) )
    {
        ruleBlocks.insert( rb->getName(), rb );
        rb->setParent(this);
        toReturn = true;
    }else{
        qWarning() << "[FunctBlock::addRuleBlock]:Duplicated RuleBlock wasn't added"<< rb->getName();
        delete rb;
    }
    return toReturn;
}
QString jfuzzyqt::FunctBlock::toString()const
{
    QString FUNCTION_BLOCK;
    FUNCTION_BLOCK.append(QString("FUNCTION_BLOCK %1\n\n").arg(getName()));
    FUNCTION_BLOCK.append(QString("VAR_INPUT\n"));
    QHashIterator<QString, Variable*> var(variables);
    while ( var.hasNext() ) {
        var.next();
        if(!var.value()->isOutputVariable())
        {
            FUNCTION_BLOCK.append(QString("\t%1 : REAL;\n").arg(var.value()->getName()));
        }
    }
    FUNCTION_BLOCK.append(QString("END_VAR\n\n"));
    FUNCTION_BLOCK.append(QString("VAR_OUTPUT\n"));
    var = QHashIterator<QString, Variable*>(variables);
    while ( var.hasNext() ) {
        var.next();
        if(var.value()->isOutputVariable())
        {
            FUNCTION_BLOCK.append(QString("\t%1 : REAL;\n").arg(var.value()->getName()));
        }
    }
    FUNCTION_BLOCK.append(QString("END_VAR\n\n"));
    var = QHashIterator<QString, Variable*>(variables);
    while ( var.hasNext() ) {
        var.next();
        if(!var.value()->isOutputVariable())
        {
            FUNCTION_BLOCK.append(QString("FUZZIFY %1\n").arg(var.value()->getName()));
            QList<QString> linguisticTermNames = var.value()->getLinguisticTermNames();
            for(QList<QString>::const_iterator lt = linguisticTermNames.begin();
                lt != linguisticTermNames.end(); lt++ )
            {
                FUNCTION_BLOCK.append(QString("\tTERM %1 := %2;\n")
                                      .arg(*lt)
                                      .arg(var.value()->
                                           getLinguisticTerm(*lt)->
                                           getMembershipFunction()->toString()));
            }
            FUNCTION_BLOCK.append(QString("END_FUZZIFY\n\n"));
        }
    }
    var = QHashIterator<QString, Variable*>(variables);
    while ( var.hasNext() ) {
        var.next();
        if(var.value()->isOutputVariable())
        {
            FUNCTION_BLOCK.append(QString("DEFUZZIFY %1\n").arg(var.value()->getName()));
            QList<QString> linguisticTermNames = var.value()->getLinguisticTermNames();
            for(QList<QString>::const_iterator lt = linguisticTermNames.begin();
                lt != linguisticTermNames.end(); lt++ )
            {
                FUNCTION_BLOCK.append(QString("\tTERM %1 := %2;\n")
                                      .arg(*lt)
                                      .arg(var.value()->
                                           getLinguisticTerm(*lt)->
                                           getMembershipFunction()->toString()));
            }
            FUNCTION_BLOCK.append(QString("\tMETHOD : %1;\n").arg(var.value()->getDefuzzifier()->getName()));
            FUNCTION_BLOCK.append(QString("\tDEFAULT := %1;\n").arg(var.value()->getDefaultValue()));
            FUNCTION_BLOCK.append(QString("END_DEFUZZIFY\n\n"));
        }
    }
    QHashIterator<QString, RuleBlock*> rb(ruleBlocks);
    while ( rb.hasNext() ) {
        rb.next();
        FUNCTION_BLOCK.append(rb.value()->toString());
        FUNCTION_BLOCK.append("\n");
    }
    FUNCTION_BLOCK.append(QString("END_FUNCTION_BLOCK\n"));
    return FUNCTION_BLOCK;
}
QHash<QString, RuleBlock*> jfuzzyqt::FunctBlock::getRuleBlocks()const
{
    return ruleBlocks;
}
QHash<QString, Variable*> jfuzzyqt::FunctBlock::getVariables()const
{
    return variables;
}
bool jfuzzyqt::FunctBlock::variableExist(const QString& varName)const
{
    return variables.contains(varName);
}
bool jfuzzyqt::FunctBlock::checkHierarchy()const
{
    for(QHash<QString, RuleBlock*>::const_iterator i = ruleBlocks.begin();
        i != ruleBlocks.end(); i++)
    {
        for(QHash<QString, RuleBlock*>::const_iterator j = ruleBlocks.begin();
            j != ruleBlocks.end(); j++)
        {
            if((*i)!=(*j))
            {
                QSet<QString>inputs  = i.value()->getInputVariables();
                QSet<QString>outputs = j.value()->getOutputVariables();
                QSet<QString>intersects = inputs.intersect(outputs);
                bool intersect = intersects.size();
                if(intersect)
                {
                    i.value()->addDependOfBlock(j.value());
                }
            }
        }
    }
    for(QHash<QString, RuleBlock*>::const_iterator j = ruleBlocks.begin(); j != ruleBlocks.end(); j++)
    {
        if(!j.value()->checkDependences())
        {
            qWarning("[FunctBlock::addRuleBlock]:RuleBlock '%s' wasn't added. Error parsing of hierarchy.",
                     j.value()->getName().toLocal8Bit().data());
            return false;
        }
    }
    return true;
}
QList<Value*> jfuzzyqt::FunctBlock::getOptimizationParameters()const
{
    QList<Value*>toReturn;
    for(QHash<QString, Variable*>::const_iterator var = variables.begin(); var != variables.end(); var++)
    {
        QList<QString> linguisticTermNames = var.value()->getLinguisticTermNames();
        for(QList<QString>::const_iterator lt = linguisticTermNames.begin();
            lt != linguisticTermNames.end(); lt++ )
        {
            OptimizationParameters*op = var.value()->getLinguisticTerm(*lt)->getMembershipFunction();
            for(int i = 0; i < op->size(); i++)
            {
                toReturn += op->getValue(i);
            }
        }
    }
    for(QHash<QString, RuleBlock*>::const_iterator j = ruleBlocks.begin(); j != ruleBlocks.end(); j++)
    {
        toReturn += (*j)->getOptimizationParameters();
    }
    return toReturn;
}
