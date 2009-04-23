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
 * \version 0.2
 * \brief FIXME
 */
#include "variable.h"
#include "../defuzzifier/defuzzifier.h"
#include <QDebug>
#include <QVariant>

Variable::Variable(QObject* parent)
    : QObject (parent),
      name    (QString::null)
{
    deffuzifier=NULL;
    value=0;
}

Variable::Variable(QObject* parent,const QString& name)
    : QObject (parent),
      name(name)
{
    deffuzifier=NULL;
    value=0;
}

Variable::~Variable()
{
    if (deffuzifier)
    {
        delete deffuzifier;
    }
}

const QString& Variable::getName()const
{
    return name;
}

void Variable::setName(const QString& name)
{
    this->name = name;
}

void Variable::addLinguisticTerm(LinguisticTerm* lt)
{
    lt->setParent(this);
    linguisticTerms.insert(lt->getTermName(), lt);
}

MembershipFunction* Variable::getMembershipFunction(const QString& termName)
{
    return getLinguisticTerm(termName)->getMembershipFunction();
}

Defuzzifier* Variable::getDefuzzifier()const
{
    return deffuzifier;
}

void Variable::setValue(const double& value)
{
    this->value = value;
}

double Variable::getValue()const
{
    return value;
}
double Variable::getAbsoluteMinimum()const
{
    double toReturn = 1.e304;
    Q_ASSERT(linguisticTerms.size());
    for(QHash<QString, LinguisticTerm*>::const_iterator i = linguisticTerms.begin();
        i != linguisticTerms.end(); i++)
    {
        toReturn = qMin(toReturn, i.value()->getMembershipFunction()->getUniverseMin());
    }
    return toReturn;
}
double Variable::getAbsoluteMaximum()const
{
    double toReturn = -1.e304;
    Q_ASSERT(linguisticTerms.size());
    for(QHash<QString, LinguisticTerm*>::const_iterator i = linguisticTerms.begin();
        i != linguisticTerms.end(); i++)
    {
        toReturn = qMax(toReturn, i.value()->getMembershipFunction()->getUniverseMax());
    }
    return toReturn;
}

/** Return 'true' if this is an output variable */
bool Variable::isOutputVariable() const
{
    return deffuzifier;
}

QVariant Variable::defuzzify()
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
LinguisticTerm* Variable::getLinguisticTerm(const QString& termName)
{
    if( !linguisticTerms.contains(termName))
    {
        qCritical("[Variable::getLinguisticTerm]:No such linguistic term: '%s'", termName.toLocal8Bit().data());
        return NULL;
    }
    return linguisticTerms.value(termName);
}

void Variable::setDefaultValue(const double& )
{
}

void Variable::setDefuzzifier(Defuzzifier* deffuzifier)
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

void Variable::debug(const QString& tbs) const
{
    QString nxTbs = tbs;
    nxTbs.append("\t");
    qDebug() << tbs << "Variable " << name.toLocal8Bit().data() << "{";
    if(deffuzifier)
    {
        deffuzifier->debug(nxTbs);
    }else{
        qDebug() << tbs << "No deffuzifier";
    }
    qDebug() << tbs << "Value(" << value << ")";
    QHashIterator<QString, LinguisticTerm*> var(linguisticTerms);
    while ( var.hasNext() ) {
        var.next();
        var.value()->debug(tbs);
    }
    if(linguisticTerms.count()<1)
    {
        qDebug() << tbs << "No Linguitic Terms";
    }
    qDebug() << tbs << "}";
}

void Variable::reset()
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
double Variable::getMembership(const QString& termName)
{
    MembershipFunction* mf = getMembershipFunction(termName);
    if( mf == NULL )
    {
        qCritical() << "[Variable::getMembership]:No membership function";
    }
    return mf->membership(value);
}
