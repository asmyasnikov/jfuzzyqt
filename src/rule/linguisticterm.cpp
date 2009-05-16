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
 * \version 0.95
 * \brief FIXME
 */
#include "linguisticterm.h"
#include "../membership/membershipfunction.h"
#include "../membership/continuous/membershipfunctionpiecewiselinear.h"
#include "../membership/continuous/membershipfunctiongauss.h"
#include "../membership/continuous/membershipfunctiongbell.h"
#include "../membership/continuous/membershipfunctionsigm.h"
#include "../membership/continuous/membershipfunctiontrian.h"
#include "../membership/continuous/membershipfunctiontrap.h"
#include "../membership/discrete/membershipfunctionsingleton.h"
#include "../membership/discrete/membershipfunctiongenericsingleton.h"
#include <QRegExp>
#include <QList>
#include <QDebug>

jfuzzyqt::LinguisticTerm::LinguisticTerm(QObject* parent)
: QObject (parent)
{
    membershipFunction=NULL;
}

jfuzzyqt::LinguisticTerm::LinguisticTerm(QObject* parent, const QString& termName, MembershipFunction* membershipFunction)
: QObject (parent)
{
    this->termName = termName;
    this->membershipFunction = membershipFunction;
}

jfuzzyqt::LinguisticTerm::~LinguisticTerm()
{
    /*
    if( membershipFunction!=NULL )
    {
            qWarning()<<"LinguisticTerm::~LinguisticTerm";
            //delete membershipFunction;
    }*/
}

const QString& jfuzzyqt::LinguisticTerm::getTermName() const
{
    return termName;
}

void jfuzzyqt::LinguisticTerm::setTermName(const QString& name)
{
    termName = name;
}

MembershipFunction* jfuzzyqt::LinguisticTerm::getMembershipFunction()
{
    return membershipFunction;
}
bool jfuzzyqt::LinguisticTerm::loadFrom(const QString& qString)
{
    bool toReturn = false;

    QRegExp rxSingleValue("(-?\\d+(\\.\\d+)?)");
    QRegExp rxDoubleValue("\\s*((-?\\d+(.\\d+)*)\\s*,\\s*(-?\\d+(.\\d+)*))");
    QRegExp rxUnknown("(\\w+)\\s+(\\()?\\d+");
    if(qString.contains("gauss")){
        int pos = 0;
        double mx = 0., dx = 0.;
        if((pos = rxSingleValue.indexIn(qString)) != -1)
        {
            mx = rxSingleValue.cap(1).toDouble();
        }else{
            qCritical("LinguisticTerm::loadFrom : no matched value of gauss membersip function : %s",
                      qString.toLocal8Bit().data());
        }
        if((pos = rxSingleValue.indexIn(qString, pos+rxSingleValue.matchedLength())) != -1)
        {
            dx = rxSingleValue.cap(1).toDouble();
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
        double d1 = 0., d2 = 0.;
        if((pos = rxSingleValue.indexIn(qString)) != -1)
        {
            d1 = rxSingleValue.cap(1).toDouble();
        }else{
            qCritical("LinguisticTerm::loadFrom : no matched value of sigm membersip function : %s",
                      qString.toLocal8Bit().data());
        }
        if((pos = rxSingleValue.indexIn(qString, pos+rxSingleValue.matchedLength())) != -1)
        {
            d2 = rxSingleValue.cap(1).toDouble();
        }else{
            qCritical("LinguisticTerm::loadFrom : no matched value of sigm membersip function : %s",
                      qString.toLocal8Bit().data());
        }
        if( membershipFunction ) delete membershipFunction;
        membershipFunction = new MembershipFunctionSigm(this, d1, d2);
        toReturn = true;
    }else if(qString.contains("trian")){
        int pos = 0;
        double d1 = 0., d2 = 0., d3 = 0.;
        if((pos = rxSingleValue.indexIn(qString)) != -1)
        {
            d1 = rxSingleValue.cap(1).toDouble();
        }else{
            qCritical("LinguisticTerm::loadFrom : no matched value of trian membersip function : %s",
                      qString.toLocal8Bit().data());
        }
        if((pos = rxSingleValue.indexIn(qString, pos+rxSingleValue.matchedLength())) != -1)
        {
            d2 = rxSingleValue.cap(1).toDouble();
        }else{
            qCritical("LinguisticTerm::loadFrom : no matched value of trian membersip function : %s",
                      qString.toLocal8Bit().data());
        }
        if((pos = rxSingleValue.indexIn(qString, pos+rxSingleValue.matchedLength())) != -1)
        {
            d3 = rxSingleValue.cap(1).toDouble();
        }else{
            qCritical("LinguisticTerm::loadFrom : no matched value of trian membersip function : %s",
                      qString.toLocal8Bit().data());
        }
        if( membershipFunction ) delete membershipFunction;
        membershipFunction = new MembershipFunctionTrian(this, d1, d2, d3);
        toReturn = true;
    }else if(qString.contains("trape")){
        int pos = 0;
        double d1 = 0., d2 = 0., d3 = 0., d4 = 0.;
        if((pos = rxSingleValue.indexIn(qString)) != -1)
        {
            d1 = rxSingleValue.cap(1).toDouble();
        }else{
            qCritical("LinguisticTerm::loadFrom : no matched value of trape membersip function : %s",
                      qString.toLocal8Bit().data());
        }
        if((pos = rxSingleValue.indexIn(qString, pos+rxSingleValue.matchedLength())) != -1)
        {
            d2 = rxSingleValue.cap(1).toDouble();
        }else{
            qCritical("LinguisticTerm::loadFrom : no matched value of trape membersip function : %s",
                      qString.toLocal8Bit().data());
        }
        if((pos = rxSingleValue.indexIn(qString, pos+rxSingleValue.matchedLength())) != -1)
        {
            d3 = rxSingleValue.cap(1).toDouble();
        }else{
            qCritical("LinguisticTerm::loadFrom : no matched value of trape membersip function : %s",
                      qString.toLocal8Bit().data());
        }
        if((pos = rxSingleValue.indexIn(qString, pos+rxSingleValue.matchedLength())) != -1)
        {
            d4 = rxSingleValue.cap(1).toDouble();
        }else{
            qCritical("LinguisticTerm::loadFrom : no matched value of trape membersip function : %s",
                      qString.toLocal8Bit().data());
        }
        if( membershipFunction ) delete membershipFunction;
        membershipFunction = new MembershipFunctionTrap(this, d1, d2, d3, d4);
        toReturn = true;
    }else if(qString.contains("gbell")){
        int pos = 0;
        double d1 = 0., d2 = 0., d3 = 0.;
        if((pos = rxSingleValue.indexIn(qString)) != -1)
        {
            d1 = rxSingleValue.cap(1).toDouble();
        }else{
            qCritical("LinguisticTerm::loadFrom : no matched value of gbell membersip function : %s",
                      qString.toLocal8Bit().data());
        }
        if((pos = rxSingleValue.indexIn(qString, pos+rxSingleValue.matchedLength())) != -1)
        {
            d2 = rxSingleValue.cap(1).toDouble();
        }else{
            qCritical("LinguisticTerm::loadFrom : no matched value of gbell membersip function : %s",
                      qString.toLocal8Bit().data());
        }
        if((pos = rxSingleValue.indexIn(qString, pos+rxSingleValue.matchedLength())) != -1)
        {
            d3 = rxSingleValue.cap(1).toDouble();
        }else{
            qCritical("LinguisticTerm::loadFrom : no matched value of gbell membersip function : %s",
                      qString.toLocal8Bit().data());
        }
        if( membershipFunction ) delete membershipFunction;
        membershipFunction = new MembershipFunctionGBell(this, d1, d2, d3);
        toReturn = true;
    }else if ( qString.contains("singletons") ){///<SINGLETONS
        QList<double> x;
        QList<double> y;
        int pos = 0;
        while ((pos = rxDoubleValue.indexIn(qString, pos)) != -1)
        {
            x.append( rxDoubleValue.cap(2).toDouble() );
            y.append( rxDoubleValue.cap(4).toDouble() );
            pos += rxDoubleValue.matchedLength();
        }
        if( membershipFunction ) delete membershipFunction;
        membershipFunction = new MembershipFunctionGenericSingleton(this, x, y);
        toReturn = true;
    }else if ( rxUnknown.indexIn(qString) > -1){///<Unknown
            qCritical("LinguisticTerm::loadFrom : unknown membersip function '%s' in term '%s'",
                      qString.toLocal8Bit().data(),
                      termName.toLocal8Bit().data());
    }else if ( rxDoubleValue.indexIn(qString) > -1){///<Point
        QList<double> x;
        QList<double> y;
        int pos = 0;
        while ((pos = rxDoubleValue.indexIn(qString, pos)) != -1)
        {
            x.append( rxDoubleValue.cap(2).toDouble() );
            y.append( rxDoubleValue.cap(4).toDouble() );
            pos += rxDoubleValue.matchedLength();
        }
        if( membershipFunction ) delete membershipFunction;
        membershipFunction = new MembershipFunctionPieceWiseLinear(this, x, y);
        toReturn = true;
    }else if (rxSingleValue.indexIn(qString) > -1){ ///<Singleton
        double singleTonValueX = rxSingleValue.cap(1).toDouble() ;
        if( membershipFunction ) delete membershipFunction;
        membershipFunction = new MembershipFunctionSingleton(this, singleTonValueX);
        toReturn = true;
    }else{
        qCritical("LinguisticTerm::loadFrom : unknown term '%s'",
                  termName.toLocal8Bit().data());
    }
    QString errors;
    if(membershipFunction)
    {
        if(!membershipFunction->checkParameters(errors))
        {
            toReturn = false;
            qCritical("LinguisticTerm::loadFrom : linguistic term '%s' is invalid : %s",
                      qString.toLocal8Bit().data(),
                      errors.toLocal8Bit().data());
        }else{
            membershipFunction->estimateUniverse();
        }
    }
    return toReturn;
}
