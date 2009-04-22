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
 * \file variable.h
 * \class Variable
 * \author Marco Estanqueiro
 * \author Aleksey Myasnikov
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 0.2
 * \brief FIXME
 */
#ifndef VARIABLE_H
#define VARIABLE_H

#include "linguisticterm.h"
#include "../membership/membershipfunction.h"
#include <QObject>
#include <QString>
#include <QHash>
#include <QVariant>

namespace jfuzzyqt
{

class Defuzzifier;
class LinguisticTerm;
class MembershipFunction;

class Variable : public QObject
{
    Q_OBJECT

public:
    Variable(QObject* parent=NULL);
    Variable(QObject* parent,const QString& name);
    ~Variable();

    const QString& getName()const;
    void setName(const QString& name);
    void addLinguisticTerm(LinguisticTerm* lt);
    MembershipFunction* getMembershipFunction(const QString& termName);
    Defuzzifier* getDefuzzifier()const;
    void setValue(const double& value);
    double getValue()const;
    double getAbsoluteMinimum()const;
    double getAbsoluteMaximum()const;
    bool isOutputVariable() const;
    QVariant defuzzify();
    LinguisticTerm* getLinguisticTerm(const QString& termName);
    void setDefaultValue(const double& value);
    void setDefuzzifier(Defuzzifier* deffuzifier);
    void debug(const QString& tbs) const;
    void reset();
    double getMembership(const QString& termName);

private:
    QString name;
    double value;
    QVariant defaultValue;
    Defuzzifier* deffuzifier;
    QHash<QString, LinguisticTerm*> linguisticTerms;///<Terms for this variable
    QVariant latestDefuzzifiedValue;///<Latest defuzzified value

};

};
using namespace jfuzzyqt;

#endif // VARIABLE_H
