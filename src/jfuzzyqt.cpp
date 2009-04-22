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
 * \author Marco Estanqueiro
 * \author Aleksey Myasnikov
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 0.2
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

JFuzzyQt::JFuzzyQt(QObject *parent) : QObject(parent)
{
}

JFuzzyQt::~JFuzzyQt()
{
}

bool JFuzzyQt::load(const QString& fileUri)
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
	while (!line.isNull()) { ///<File Cycle (only works for one function block
		if (rxFunctionBlock.indexIn(line) > -1) //If Function Block
		{
			FunctBlock* functionBlock = new FunctBlock(this,rxFunctionBlock.cap(1));
			fclParser.loadFunctBlock(in,*functionBlock);
			addFunctionBlock(functionBlock);
		}///<END If Function Block
		line = fclParser.readLine(in);
	} ///<END File Cycle
	return toReturn;
}

bool JFuzzyQt::addFunctionBlock(FunctBlock* functionBlock)
{
    bool toReturn = false;
    functionBlock->setParent(this);
    if ( !functionBlocks.contains( functionBlock->getName() ))
    {
        functionBlocks.insert(functionBlock->getName(),functionBlock);
        toReturn = true;
    }
    if ( defaultBlockName == "" )
    {
        defaultBlockName = functionBlock->getName();
    }
    return toReturn;
}

/*! \brief Sets var from default functions block inserted
*
*/
void JFuzzyQt::setVariable(const QString& varName, const double& value)
{
    if( functionBlocks.size() > 0 )
    {
        ///< Only one function block is supported
        QHash<QString, FunctBlock*>::iterator i = functionBlocks.find(defaultBlockName);
        if ( i!=functionBlocks.end() )
        {
            i.value()->setValue(varName.toLower(),value);
        }
    }else{
        qWarning("[JFuzzyQt::setVariable]:There are no FunctionBlocks");
    }
}

void JFuzzyQt::evaluate()
{
    if( functionBlocks.size() > 0 )
    {
        QHash<QString, FunctBlock*>::iterator i = functionBlocks.find(defaultBlockName);
        if ( i!=functionBlocks.end() )
        {
            i.value()->evaluate();
        }
    }else{
        qWarning("[JFuzzyQt::evaluate]:There are no FunctionBlocks");
    }
}

double JFuzzyQt::getValue(const QString& varName)const
{
    if( functionBlocks.size() > 0 )
    {
        QHash<QString, FunctBlock*>::const_iterator i = functionBlocks.find(defaultBlockName);
        if ( i!=functionBlocks.end() )
        {
            if(i.value()->getVariable(varName.toLower()))
            {
                return i.value()->getValue( varName.toLower() );
            }
        }
    }else{
        qWarning("[JFuzzyQt::getValue]:There are no FunctionBlocks");
    }
    return 0;
}

void JFuzzyQt::debug() const
{
	functionBlocks.value(defaultBlockName)->debug("");
}
