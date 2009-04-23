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
 * \file linguisticterm.cpp
 * \class LinguisticTerm
 * \author Marco Estanqueiro <estanqueiro.marco@gmail.com>
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 0.2
 * \brief FIXME
 */
#include "linguisticterm.h"
#include "../membership/value.h"
#include "../membership/membershipfunction.h"
#include "../membership/continuous/membershipfunctionpiecewiselinear.h"
#include "../membership/continuous/membershipfunctiongauss.h"
#include "../membership/continuous/membershipfunctionsigm.h"
#include "../membership/continuous/membershipfunctiontrian.h"
#include "../membership/discrete/membershipfunctionsingleton.h"
#include <QRegExp>
#include <QList>
#include <QDebug>

LinguisticTerm::LinguisticTerm(QObject* parent)
: QObject (parent)
{
    membershipFunction=NULL;
}

LinguisticTerm::LinguisticTerm(QObject* parent, const QString& termName, MembershipFunction* membershipFunction)
: QObject (parent)
{
    this->termName = termName;
    this->membershipFunction = membershipFunction;
}

LinguisticTerm::~LinguisticTerm()
{
    /*
    if( membershipFunction!=NULL )
    {
            qWarning()<<"LinguisticTerm::~LinguisticTerm";
            //delete membershipFunction;
    }*/
}

const QString& LinguisticTerm::getTermName() const
{
    return termName;
}

void LinguisticTerm::setTermName(const QString& name)
{
    termName = name;
}

MembershipFunction* LinguisticTerm::getMembershipFunction()
{
    return membershipFunction;
}
bool LinguisticTerm::loadFrom(const QString& qString)
{
    bool toReturn = false;

    QRegExp rxSingleton("(-?\\d+(\\.\\d+)?)");
    QRegExp rxPoint("\\s*((-?\\d+(.\\d+)*)\\s*,\\s*(-?\\d+(.\\d+)*))");
    if(qString.contains("gauss")){
        int pos = 0;
        double mx, dx;
        if((pos = rxSingleton.indexIn(qString)) != -1)
        {
            mx = rxSingleton.cap(1).toDouble();
        }else{
            qCritical("LinguisticTerm::loadFrom : no matched value of gauss membersip function : %s",
                      qString.toLocal8Bit().data());
        }
        if((pos = rxSingleton.indexIn(qString, pos+rxSingleton.matchedLength())) != -1)
        {
            dx = rxSingleton.cap(1).toDouble();
        }else{
            qCritical("LinguisticTerm::loadFrom : no matched value of gauss membersip function : %s",
                      qString.toLocal8Bit().data());
        }
        if( membershipFunction ) delete membershipFunction;
        membershipFunction = new MembershipFunctionGauss(this, mx, dx);
        toReturn = true;
    }else if(qString.contains("dsigm")){
        qDebug() << "dsigm " << qString;
        qCritical("LinguisticTerm::loadFrom : dsigm membersip function not implemeted : %s",
                  qString.toLocal8Bit().data());
        Q_ASSERT(0);
    }else if(qString.contains("sigm")){
        int pos = 0;
        double d1, d2;
        if((pos = rxSingleton.indexIn(qString)) != -1)
        {
            d1 = rxSingleton.cap(1).toDouble();
        }else{
            qCritical("LinguisticTerm::loadFrom : no matched value of sigm membersip function : %s",
                      qString.toLocal8Bit().data());
        }
        if((pos = rxSingleton.indexIn(qString, pos+rxSingleton.matchedLength())) != -1)
        {
            d2 = rxSingleton.cap(1).toDouble();
        }else{
            qCritical("LinguisticTerm::loadFrom : no matched value of sigm membersip function : %s",
                      qString.toLocal8Bit().data());
        }
        if( membershipFunction ) delete membershipFunction;
        membershipFunction = new MembershipFunctionSigm(this, d1, d2);
        toReturn = true;
    }else if(qString.contains("trian")){
        int pos = 0;
        double d1, d2, d3;
        if((pos = rxSingleton.indexIn(qString)) != -1)
        {
            d1 = rxSingleton.cap(1).toDouble();
        }else{
            qCritical("LinguisticTerm::loadFrom : no matched value of trian membersip function : %s",
                      qString.toLocal8Bit().data());
        }
        if((pos = rxSingleton.indexIn(qString, pos+rxSingleton.matchedLength())) != -1)
        {
            d2 = rxSingleton.cap(1).toDouble();
        }else{
            qCritical("LinguisticTerm::loadFrom : no matched value of trian membersip function : %s",
                      qString.toLocal8Bit().data());
        }
        if((pos = rxSingleton.indexIn(qString, pos+rxSingleton.matchedLength())) != -1)
        {
            d3 = rxSingleton.cap(1).toDouble();
        }else{
            qCritical("LinguisticTerm::loadFrom : no matched value of trian membersip function : %s",
                      qString.toLocal8Bit().data());
        }
        if( membershipFunction ) delete membershipFunction;
        membershipFunction = new MembershipFunctionTrian(this, d1, d2, d3);
        toReturn = true;
    }else if ( rxPoint.indexIn(qString) > -1){///<Point
        QList<double> x;
        QList<double> y;
        int pos = 0;
        while ((pos = rxPoint.indexIn(qString, pos)) != -1)
        {
            x.append( rxPoint.cap(2).toDouble() );
            y.append( rxPoint.cap(4).toDouble() );
            pos += rxPoint.matchedLength();
        }
        if( membershipFunction )
        {
            delete membershipFunction;
        }
        membershipFunction = new MembershipFunctionPieceWiseLinear(this, x, y);
        toReturn = true;
    }else if (rxSingleton.indexIn(qString) > -1){ ///<Singleton
        double singleTonValueX = rxSingleton.cap(1).toDouble() ;
        if( membershipFunction ) delete membershipFunction;
        membershipFunction = new MembershipFunctionSingleton(this, singleTonValueX);
        toReturn = true;
    }else{
        qCritical("LinguisticTerm::loadFrom : unknown linguistic term : %s",
                  qString.toLocal8Bit().data());
    }
    return toReturn;
}
void LinguisticTerm::debug(const QString& tbs) const
{
    QString nxtTbs=tbs;
    nxtTbs.append("\t");
    qDebug() << tbs <<"TERM"<<termName<<"{";
    if(membershipFunction)
    {
        membershipFunction->debug(nxtTbs);
    }
    qDebug() << tbs <<"}";
}
