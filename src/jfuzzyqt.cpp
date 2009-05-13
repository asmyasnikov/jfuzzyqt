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
 * \file jfuzzyqt.cpp
 * \class JFuzzyQt
 * \brief Class JFuzzyQt is main class of fuzzy model.
 *
 * Application instructions:
 *
 * 1) Construct JFuzzyQt object:
 *
 *    JFuzzyQt model;
 *
 * 2) Set path of fcl-file:
 *
 *    model.load("./example.fcl");
 *
 * 3) Sets variable values:
 *
 *    model.setVariable("var1", var1);
 *
 * 4) Evalute model:
 *
 *    model.evalute();
 *
 * 5) Getting result:
 *
 *    double result = model.getValue("res")
 * \author Marco Estanqueiro <estanqueiro.marco@gmail.com>
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 0.95
 */
#include "functblock.h"
#include "../include/jfuzzyqt.h"
#include "rule/ruleexpression.h"
#include "fcl/fclparser.h"
#include "connection/ruleconnectionmethod.h"
#include "connection/and/ruleconnectionmethodandmin.h"
#include "connection/or/ruleconnectionmethodormax.h"
#include "fcl/fclruletree.h"
#include "optimization/errorfunction.h"
#include "optimization/optimizationdeltajump.h"
#include "optimization/optimizationgradient.h"
#include "optimization/optimizationpartialderivate.h"
#include <QDebug>
#include <QRegExp>
#include <QFile>
#include <QTextStream>

jfuzzyqt::JFuzzyQt::JFuzzyQt(QObject *parent) : QObject(parent)
{
}

jfuzzyqt::JFuzzyQt::JFuzzyQt(const QString& fileUri, QObject *parent) : QObject(parent)
{
    load(fileUri);
}

jfuzzyqt::JFuzzyQt::~JFuzzyQt()
{
    for(QHash<QString, FunctBlock*>::iterator i = functionBlocks.begin();
        i != functionBlocks.end();
        i++ )
    {
        delete i.value();
    }
}

bool jfuzzyqt::JFuzzyQt::load(const QString& fileUri)
{
    bool toReturn = false;
    QFile file(fileUri);
    if (file.open(QIODevice::ReadOnly))
    {
        QRegExp rxFunctionBlock("function_block\\s+(\\w+)");
        QTextStream in(&file);
        FCLParser fclParser;
        QString line = fclParser.readLine(in);
        while (!line.isNull())
        { ///<File Cycle (only works for one function block
            if (rxFunctionBlock.indexIn(line) > -1) //If Function Block
            {
                FunctBlock* functionBlock = new FunctBlock(this,rxFunctionBlock.cap(1));
                fclParser.loadFunctBlock(in,*functionBlock);
                QHash<QString, Variable*> variables = functionBlock->getVariables();
                for(QHash<QString, Variable*>::const_iterator i = variables.begin(); i != variables.end(); i++)
                {
                    if(!i.value()->getLinguisticTermNames().size())
                    {
                        qWarning("Variable '%s' in function block '%s' not contain terms",
                                 i.key().toLocal8Bit().data(),
                                 rxFunctionBlock.cap(1).toLocal8Bit().data());
                    }
                }
                bool rules = false;
                QHash<QString, RuleBlock*> ruleblocks = functionBlock->getRuleBlocks();
                for(QHash<QString, RuleBlock*>::const_iterator i = ruleblocks.begin(); i != ruleblocks.end(); i++)
                {
                    if(i.value()->getRulesCount())
                    {
                        rules = true;
                        break;
                    }
                }
                if(!rules)
                {
                    qWarning("Rules in function block '%s' was not found",
                             rxFunctionBlock.cap(1).toLocal8Bit().data());
                }
                Q_ASSERT(functionBlock->checkHierarchy());
                addFunctionBlock(functionBlock);
            }///<END If Function Block
            line = fclParser.readLine(in);
        } ///<END File Cycle
        file.close();
        toReturn = true;
    }else{
        qFatal("Unable to open the file '%s'", fileUri.toLocal8Bit().data());
        return false;
    }
    return toReturn;
}

bool jfuzzyqt::JFuzzyQt::addFunctionBlock(FunctBlock* functionBlock)
{
    bool toReturn = false;
    functionBlock->setParent(this);
    if ( !functionBlocks.contains( functionBlock->getName() ))
    {
        functionBlocks.insert(functionBlock->getName(),functionBlock);
        if ( defaultBlockName.isEmpty() )
        {
            defaultBlockName = functionBlock->getName();
        }
        toReturn = true;
    }else{
        qWarning("Function block '%s' already exist",
                 functionBlock->getName().toLocal8Bit().data());
        delete functionBlock;
    }
    return toReturn;
}

/*! \brief Sets var from default functions block inserted
*
*/
void jfuzzyqt::JFuzzyQt::setVariable(const QString& varName, const double& value, const QString& fb)
{
    if( functionBlocks.size() > 0 )
    {
        for(QHash<QString, FunctBlock*>::iterator i = fb.isEmpty() ?
                                                      i = functionBlocks.begin() :
                                                      functionBlocks.find(fb);
            i != functionBlocks.end();
            i++ )
        {
            i.value()->setValue(varName.toLower(),value);
        }
    }else{
        qWarning("[jfuzzyqt::JFuzzyQt::setVariable]:There are no FunctionBlocks");
    }
}

void jfuzzyqt::JFuzzyQt::evaluate(const QString& fb)
{
    if( functionBlocks.size() > 0 )
    {
        for(QHash<QString, FunctBlock*>::iterator i = fb.isEmpty() ?
                                                      i = functionBlocks.begin() :
                                                      functionBlocks.find(fb);
            i != functionBlocks.end();
            i++ )
        {
            i.value()->evaluate();
        }
    }else{
        qWarning("[jfuzzyqt::JFuzzyQt::evaluate]:There are no FunctionBlocks");
    }
}

double jfuzzyqt::JFuzzyQt::getValue(const QString& varName, const QString& fb)const
{
    if( functionBlocks.size() > 0 )
    {
        QHash<QString, FunctBlock*>::const_iterator i = functionBlocks.find(fb.isEmpty() ?
                                                                            defaultBlockName :
                                                                            fb);
        if ( i!=functionBlocks.end() )
        {
            if(i.value()->getVariable(varName.toLower()))
            {
                return i.value()->getValue( varName.toLower() );
            }
        }else{
            qWarning("[jfuzzyqt::JFuzzyQt::getValue]:There are no %s variable in %s function block",
                     varName.toLocal8Bit().data(),
                     fb.toLocal8Bit().data());
        }
    }else{
        qWarning("[jfuzzyqt::JFuzzyQt::getValue]:There are no FunctionBlocks");
    }
    return 0;
}
QStringList jfuzzyqt::JFuzzyQt::functBlocks()const
{
    return functionBlocks.keys();
}
QStringList jfuzzyqt::JFuzzyQt::inputs(const QString& fb)const
{
    QStringList toReturn;
    QHash<QString, FunctBlock*>::const_iterator i = functionBlocks.find(fb.isEmpty() ?
                                                                        defaultBlockName :
                                                                        fb);
    if ( i!=functionBlocks.end() )
    {
        QHash<QString, Variable*> variables = i.value()->getVariables();
        for(QHash<QString, Variable*>::const_iterator j = variables.begin(); j != variables.end(); j++ )
        {
            if(!j.value()->isOutputVariable())
            {
                toReturn.append(j.key());
            }
        }
    }
    return toReturn;
}
QStringList jfuzzyqt::JFuzzyQt::outputs(const QString& fb)const
{
    QStringList toReturn;
    QHash<QString, FunctBlock*>::const_iterator i = functionBlocks.find(fb.isEmpty() ?
                                                                        defaultBlockName :
                                                                        fb);
    if ( i!=functionBlocks.end() )
    {
        QHash<QString, Variable*> variables = i.value()->getVariables();
        for(QHash<QString, Variable*>::const_iterator j = variables.begin(); j != variables.end(); j++ )
        {
            if(j.value()->isOutputVariable())
            {
                toReturn.append(j.key());
            }
        }
    }
    return toReturn;
}
bool jfuzzyqt::JFuzzyQt::save(const QString& fileUri)
{
    bool toReturn = false;
    QFile file(fileUri);
    if(file.open(QIODevice::WriteOnly))
    {
        for(QHash<QString, FunctBlock*>::iterator i = functionBlocks.begin();
            i != functionBlocks.end();
            i++ )
        {
            QString functBlock = i.value()->toString();
            file.write(functBlock.toLocal8Bit(), functBlock.toLocal8Bit().size());
        }
        file.close();
        toReturn = true;
    }else{
        qDebug() << "Error opening file to writing " << fileUri;
    }
    return toReturn;
}
bool jfuzzyqt::JFuzzyQt::optimize(const QString& fileUri, OptimizationMethod method)
{
    bool toReturn = false;
    QList<Value*> optimizationParameters;
    for(QHash<QString, FunctBlock*>::iterator i = functionBlocks.begin();
        i != functionBlocks.end();
        i++ )
    {
        optimizationParameters.append(i.value()->getOptimizationParameters());
    }
    ErrorFunction erf(this, fileUri);
    if(erf.samplesSize())
    {
        qDebug() << "Error before optimization " << erf.evaluate(*this);
        switch(method)
        {
            case DeltaJump :
            {
                OptimizationDeltaJump optimization(this, &erf, optimizationParameters);
                optimization.optimize(true);
                break;
            }
            case Gradient :
            {
                OptimizationGradient optimization(this, &erf, optimizationParameters);
                optimization.optimize(true);
                break;
            }
            case PartialDerivate :
            {
                OptimizationPartialDerivate optimization(this, &erf, optimizationParameters);
                optimization.optimize(true);
                break;
            }
            case InsularGenetica :
            {
                qDebug() << "InsularGenetica method not implacated or need libraries not found";
//                OptimizationInsualrGenetica optimization(this, &erf, optimizationParameters);
//                optimization.optimize(true);
                break;
            }
        }
        qDebug() << "Error after optimization " << erf.evaluate(*this);
        toReturn = true;
    }
    return toReturn;
}
