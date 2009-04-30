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
 * \author Marco Estanqueiro <estanqueiro.marco@gmail.com>
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 0.83
 * \brief FIXME
 */
#include "../include/jfuzzyqt.h"
#include "rule/ruleexpression.h"
#include "functblock.h"
#include "fcl/fclparser.h"
#include "connection/ruleconnectionmethod.h"
#include "connection/and/ruleconnectionmethodandmin.h"
#include "connection/or/ruleconnectionmethodormax.h"
#include "fcl/fclruletree.h"
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
}

bool jfuzzyqt::JFuzzyQt::load(const QString& fileUri)
{
    bool toReturn = false;
    QFile file(fileUri);
    if (!file.open(QIODevice::ReadOnly))
    {
        QString str = "Unable to open the file (";
        str.append( fileUri );
        str.append( ")" );
        qFatal("%s", str.toLocal8Bit().data());
        return false;
    }
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

void jfuzzyqt::JFuzzyQt::debug() const
{
    for(QHash<QString, FunctBlock*>::const_iterator i = functionBlocks.begin();
        i != functionBlocks.end();
        i++ )
    {
        i.value()->debug("");
    }
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
