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
 * \file variable.cpp
 * \class Variable
 * \author Marco Estanqueiro <estanqueiro.marco@gmail.com>
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 0.95
 * \brief FIXME
 */
#include "variable.h"
#include "../defuzzifier/defuzzifier.h"
#include <QDebug>
#include <QVariant>
#include <math.h>

jfuzzyqt::Variable::Variable(QObject* parent)
    : QObject (parent),
      name    (QString::null)
{
    deffuzifier=NULL;
    value=0;
}

jfuzzyqt::Variable::Variable(QObject* parent,const QString& name)
    : QObject (parent),
      name(name)
{
    deffuzifier=NULL;
    value=0;
}

jfuzzyqt::Variable::~Variable()
{
    if (deffuzifier)
    {
        delete deffuzifier;
    }
}

const QString& jfuzzyqt::Variable::getName()const
{
    return name;
}

void jfuzzyqt::Variable::setName(const QString& name)
{
    this->name = name;
}

void jfuzzyqt::Variable::addLinguisticTerm(LinguisticTerm* lt)
{
    Q_ASSERT(!linguisticTermExist(lt->getTermName()));
    lt->setParent(this);
    OptimizationParameters*op = lt->getMembershipFunction();
    if(op)
    {
        for(int i = 0; i < op->size(); i++)
        {
            op->getValue(i)->setVariableReference(this);
        }
    }
    linguisticTerms.insert(lt->getTermName(), lt);
}

MembershipFunction* jfuzzyqt::Variable::getMembershipFunction(const QString& termName)
{
    return getLinguisticTerm(termName)->getMembershipFunction();
}

Defuzzifier* jfuzzyqt::Variable::getDefuzzifier()const
{
    return deffuzifier;
}

void jfuzzyqt::Variable::setValue(const double& value)
{
    this->value = value;
}

double jfuzzyqt::Variable::getValue()const
{
    return value;
}
double jfuzzyqt::Variable::getAbsoluteMinimum()const
{
    if(linguisticTerms.size())
    {
        double toReturn = HUGE_VAL;
        for(QHash<QString, LinguisticTerm*>::const_iterator i = linguisticTerms.begin();
            i != linguisticTerms.end(); i++)
        {
            toReturn = qMin(toReturn, i.value()->getMembershipFunction()->getUniverseMin());
        }
        return toReturn;
    }else{
        return -HUGE_VAL;
    }
}
double jfuzzyqt::Variable::getAbsoluteMaximum()const
{
    if(linguisticTerms.size())
    {
        double toReturn = -HUGE_VAL;
        for(QHash<QString, LinguisticTerm*>::const_iterator i = linguisticTerms.begin();
            i != linguisticTerms.end(); i++)
        {
            toReturn = qMax(toReturn, i.value()->getMembershipFunction()->getUniverseMax());
        }
        return toReturn;
    }else{
        return HUGE_VAL;
    }
}

/** Return 'true' if this is an output variable */
bool jfuzzyqt::Variable::isOutputVariable() const
{
    return deffuzifier;
}

QVariant jfuzzyqt::Variable::defuzzify()
{
    if(deffuzifier)
    {
        QVariant ldv = deffuzifier->defuzzify();
        if( ldv.isValid() )
        {
            latestDefuzzifiedValue = ldv.toDouble();
            value = latestDefuzzifiedValue.toDouble();
        }
    }
    return latestDefuzzifiedValue;
}

/*!
\brief Get 'termName' linguistic term
*/
LinguisticTerm* jfuzzyqt::Variable::getLinguisticTerm(const QString& termName)
{
    if( !linguisticTerms.contains(termName))
    {
        qCritical("[jfuzzyqt::Variable::getLinguisticTerm]:No such linguistic term: '%s'", termName.toLocal8Bit().data());
        return NULL;
    }
    return linguisticTerms.value(termName);
}

void jfuzzyqt::Variable::setDefaultValue(const double& value)
{
    defaultValue = value;
}
double jfuzzyqt::Variable::getDefaultValue()const
{
    return defaultValue.toDouble();
}
void jfuzzyqt::Variable::setDefuzzifier(Defuzzifier* deffuzifier)
{
    if (this->deffuzifier)
    {
        delete (this->deffuzifier);
    }
    this->deffuzifier = deffuzifier;
    if (this->deffuzifier)
    {
        this->deffuzifier->setParent(this);
    }
}

void jfuzzyqt::Variable::reset()
{
    if (deffuzifier)
    {
        deffuzifier->reset();
        ///<Set default value for output variables (if any default value was defined)
        if( defaultValue.isValid() )
        {
            value = defaultValue.toDouble();
        }
    }
    latestDefuzzifiedValue = defaultValue;
}

/** Evaluate 'termName' membershipfunction at 'value' */
double jfuzzyqt::Variable::getMembership(const QString& termName)
{
    MembershipFunction* mf = getMembershipFunction(termName);
    if( mf == NULL )
    {
        qCritical() << "[jfuzzyqt::Variable::getMembership]:No membership function";
    }
    return mf->membership(value);
}
QList<QString> jfuzzyqt::Variable::getLinguisticTermNames()const
{
    return linguisticTerms.keys();
}
bool jfuzzyqt::Variable::linguisticTermExist(const QString& termName)const
{
    return linguisticTerms.contains(termName);
}
